#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _USE_MATH_DEFINES
#include <iostream>
#include <functional>
#include <experimental/filesystem>
#include <cmath>
#include "Modifier.h"
#include "VertexData.h"
#include "Inventory.h"
#include "Vector2.h"
#include "Player.h"
#include "Ray.h"
#include "Phantom.h"
#include "Particles.h"
#include "UI.h"
#include "KeyConfig.h"


struct Modifier;

using namespace std;
/// <summary>
/// ����� �������
/// </summary>
class Client
{
public:
	struct Page; // ��������� ��������� �������� ���� 

	void Pause(bool active);					// ���������� ����
	void ToSettings();							// ������� � �������� ��������
	void ToMenu();								// ������� � ������� �������� ����
	void ToAgree();								// ������� � �������� ��������
	void ToNewWorld();							// ������� � �������� �������� ������ ����
	void ToRenderDistance();					// ������� � ���������� ��������� ����������
	void ButtonUp();							// ������ �����
	void ButtonDown();							// ������ �����
	
	void SetBlock(int x, int y, int z, int id); // ��������� �����
	void SetBlock(Vector3 pos, int id);			// ��������� �����
	void SetBlock();							// ��������� �����
	void DestroyBlock(int x, int y, int z);		// ���������� �����
	void DestroyBlock(Vector3 pos);				// ���������� �����
	void DestroyBlock();						// ���������� �����
	void CopyBlock();							// ����������� �����

	void Resize();								// ��������� �������� ����
	void MoveCamera(double delta_time);			// �������� ������
	void UpdatePhantomPos();					// ���������� ������� �������
	void CameraUpdate();						// ���������� ������
	void NewWorld();							// �������� ������ ����
	void SetRenderDistance(int d);				// ��������� ��������� ����������

	void Init();								// �������������
	void Update(float deltaTime);				// ���������� 
	void Clear();								// �������
	void Render();								// ���������
	void RenderUI();							// ��������� UI
	void DrawMenu();							// ��������� ����

	GLFWwindow* window;			// ��������� �� �������� ����
	UI ui, Menu, Settings;		// ���������� ����������������� ����������
	Player player;				// ��������� ������
	World* world;				// ��������� �� ��������� ����
	Page* page;					// ��������� �� ������� �������� ����
	Vector2Int MenuPos;			// ������� � ����
	Phantom phantom;			// ������ (�����)
	Inventory inventory;		// ���������
	World::Settings gen_params;	// ��������� ���������
	Modifier* modifier;			// �����������
	KeyConfig key_config;		// ������������ ��������

	vector<Particles*> particles;

	bool pause = false; // ���� �����
	bool enter = false; // ���� �������������
	bool close = false; // ���� ��������

	double mouse_pos_x, mouse_pos_y; // ����������� ��������� �������
	unsigned int main_texture; // ���������� �����

	struct Button // ������ � ����
	{
		string name;				// ��������� ������
		std::function<void()> func; // ������ �� ���������
		Button() :name("?"), func([] {}) {}
		Button(string name, std::function<void()> func) :name(name), func(func)
		{
		}
		virtual void DoFunc() // ����� ���������� �������
		{
			func();
		}
	};

	Button btn_settings{ "���������", [&] {ToSettings(); } };			// ������ ��������
	Button btn_new_world{ "������� ����� ���", [&] {ToNewWorld(); } };	// ������ �������� ����
	Button btn_continue{ "���������� ����", [&] {Pause(false); } };		// ������ ����������� ����
	Button btn_close{ "����� �� ����", [&] {close = true; } };			// ������ ������ �� ����
	Button btn_render_distance{ "��������� ����������", [&] {ToRenderDistance(); } }; // ������ ��������� ����������
	Button btn_day{ "������� ����� �����", [&]()						// ������ ����� ������� �����
	{
		World::is_day = !World::is_day;
		world->UpdateWorldLighting();
	}, };
	Button btn_back{ "�����", [&] {ToMenu(); } };					// ������ �������� � ����
	Button btn_small{ "���������", [&] {SetRenderDistance(4); } };	// ������ ��������� ��������� ��������� ����������
	Button btn_medium{ "�������", [&] {SetRenderDistance(6); } };	// ������ ��������� ������� ��������� ����������
	Button btn_large{ "�������", [&] {SetRenderDistance(8); } };	// ������ ��������� ������� ��������� ����������
	Button btn_confirm{ "����������", [&] {NewWorld(); } };			// ������ �����������
	Button btn_cancel{ "��������", [&] {ToMenu(); } };				// ������ ������
	Button btn_create{ "�������", [&] {ToAgree(); } };				// ������ �������� ����

	struct Switcher : Button // ������-������������� 
	{
		string name;	// ��������� �������������
		bool* value;	// ������ �� ������������� ��������
		/// <summary>
		/// �����������
		/// </summary>
		Switcher(string name, bool* value) :name(name), value(value)
		{
			Button::name = name + (*value ? " On" : " Off");
		}
		/// <summary>
		/// ������������ �������� 
		/// </summary>
		virtual void DoFunc()
		{
			*value = !(*value);
			Button::name = name + (*value ? " On" : " Off");
		}
	};

	Switcher swt_mountains{ "����", &gen_params.params[0] };	// ����������� ���
	Switcher swt_plains{ "�������", &gen_params.params[1] };	// ����������� ������
	Switcher swt_trees{ "�������", &gen_params.params[2] };		// ����������� ��������
	Switcher swt_grass{ "�����", &gen_params.params[3] };		// ����������� �����
	/// <summary>
	/// ��������� �������� ����
	/// </summary>
	struct Page
	{
		int count;			// ���������� ����������
		string name;		// ��������� ��������
		Button** buttons;	// ������ ������
		float* indents;		// ������ �������� �� ��������� 
	};
	// �������� ����
	Page page_menu{ 4, "����", new Button * [] {&btn_settings,& btn_new_world,& btn_continue,& btn_close}, new float[] {0, 0, 0, 0} };
	Page page_settings{ 3, "���������", new Button * [] {&btn_render_distance,& btn_day,& btn_back}, new float[] {0, 0, 20} };
	Page page_render_distance{ 4, "��������� ����������", new Button * [] {&btn_small,& btn_medium,& btn_large,& btn_back}, new float[] {0, 0, 0, 20} };
	Page page_agree{ 2, "������� ��� ����� ������", new Button * [] {&btn_confirm,& btn_cancel}, new float[] {0,0} };
	Page page_new_world{ 6, "��������� ������ ����", new Button * [] {&swt_mountains,& swt_plains,& swt_trees,& swt_grass,& btn_create,& btn_back},new float[] {0, 0, 0, 0, 20, 0} };
};