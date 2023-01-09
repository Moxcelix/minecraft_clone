#pragma once
#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>
#include"UVData.h"
#include"Vector2.h"
#include"Block.h"
#include"UIObjects.h"


#define UI_DRAW_CROSS			0b0001	// ��������� ��������
#define UI_DRAW_BACK_GROUND		0b0010	// ��������� ����

using namespace std;

struct Text;
struct Plane;
struct UIElement;
/// <summary>
/// ����� ����������������� ����������
/// </summary>
class UI
{
private:
	int IDCounter = 0; // ������� ID
	int flags = 0;	// ����� ���������
	int winWidth = 1, winHeight = 1;	// �������� ����
	int debug_line_counter = 0;			// ������� ���������� ����� �������
public:
	/// <summary>
	/// ������������ �����
	/// </summary>
	enum class Corner
	{
		left_up,
		left,
		left_down,
		up,
		middle,
		down,
		right_up,
		right,
		right_down
	};

	unsigned int font;					// �������� ������

	vector<Text> texts;				// ������ �������
	vector<Text> static_texts;		// ������ ��������� �������
	vector<Plane> static_planes;	// ������ ��������� �������
	vector<Plane> planes;			// ������ �������

	Cross cross;
	BackGround bg;

	void PrintText(Corner corner, float size, int x, int y, string str, float r, float g, float b); // ����� ������ �� �����
	void PrintText(Text t);			// ����� ������ �� �����
	void PrintStatic();				// ������ ��������� ��������
	void Render();					// ��������� ���������
	void PrintDebug(string str, float r, float g, float b); // ����� �� ����� ����������� ������
	void PrintPlane(Plane p);		// ����� �� ����� ������
	void RemoveStaticText(Text t);	// �������� ���������� ������
	void RemoveStaticText();		// �������� ��������� �������
	void SetSize(int w, int h);		// ��������� �������� ����
	void Clear();					// �������
	void SetFlags(int flags);		// ��������� ������

	Vector2 GetCorner(Corner corner, float xScale, float yScale, int xShift = 0, int yShift = 0); // ���� �������� 
	Text AddStaticText(Corner corner, float size, int x, int y, string str, float r, float g, float b); // ���������� ���������� ������ 
	Plane AddStaticPlane(Corner corner, float size, int x, int y, int w, int h, ColorSquad colors); // ���������� ��������� ������
};
/// <summary>
/// UI �������
/// </summary>
struct UIElement 
{
	int ID;				// ID

	int x, y;			// ����������
	float r, g, b;		// ����
	float size;			// ������

	float* vertices;	// ������ ������
	float* colors;		// ������ ������
	float* uvs;			// ������ UV ���������

	UVData* uvs_data;	// UV ������ 
	UI::Corner corner;	// ���� ��������

	// ������ ������ ��������
	float rect[12] =
	{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0
	};

	bool operator==(UIElement val)
	{
		return ID == val.ID;
	}
};
/// <summary>
/// ��������� ������
/// </summary>
struct Plane : UIElement
{
	int w, h;			// ��������
	ColorSquad squad;	// ����� �����

	/// <summary>
	/// �����������
	/// </summary>
	Plane(int x, int y, int w, int h, float size, ColorSquad squad, UI::Corner corner)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->size = size;
		this->squad = squad;
		this->corner = corner;
	}
};
/// <summary>
/// ��������� ������
/// </summary>
struct Text : UIElement
{
	string text; // �����

	float width = 6. / 128., height = .0625f;	// ������ ������
	float iwidth = 6, iheight = 8;				// ������ ������ � ��������
	int wCount = 21, hCount = 16;				// ���������� ����� � �������� � ������

	// ������ ������ �����
	float quad[12] =
	{
		iwidth, 0, 0,
		0, 0, 0,
		0, iheight, 0,
		iwidth, iheight, 0
	};

	/// <summary>
	/// �����������
	/// </summary>
	Text(int x, int y, float size, float r, float g, float b, string text, UI::Corner corner)
	{
		this->x = x;
		this->y = y;
		this->size = size;
		this->r = r;
		this->g = g;
		this->b = b;
		this->text = text;
		this->corner = corner;
	}
};

