#pragma once
#include "World.h"
#include "Debug.h"
#include <iostream>
#include <vector>

#define RB_CHECK_LOAD_STATE		0b0001	// ��������� �������������� ����������
#define RB_USE_COLLISION		0b0010	// ������������� ��������
#define RB_SPLIT_HEIGHT			0b0100	// ���������� �� ������ �����
#define RB_COLLISION_MAP		0b1000	// ������� ����� ��������

using namespace std;

class World;
class Player;
/// <summary>
/// ����� ����� ������� ����
/// </summary>
class RigidBox
{
private:
	static vector<Vector3Int> positions; // ������ ������� ����� ��������

	float eps = 0.01f;
	float w = 0;				// �������� ������
	float h0 = 0;				// ������ ����� ���-�����
	float h1 = 0;				// ������� ����� ���-�����
	float half = 0.5f;			// ��������
	float salf = 0.499f;		// ��������

	void SetCollisionMap(); // �������� ����� ��������
	static void AddPos(Vector3Int pos); // ���������� ����� � ����� ��������
public:
	int flags = 0;		// ����� ����������

	float width;		// ������ �����
	float height;		// ������ �����
	float g;			// ��������� ���������� �������
	float phys_mod = 0.0001f; // ��������� ��� ������

	bool grounded = false; // �������������

	Vector3 pos;	// �������
	World* world;	// ��������� �� ���

	RigidBox();		// ������������ � ����������� � ���
	RigidBox(World* world, float width, float height, float g = 9.8f, Vector3 pos = {0,0,0}, int flags = 0);

	void Render();									// ���������
	void Move(float dx, float dy, float dz);		// ��������
	void Collision(float dx, float dy, float dz);	// ��������
	bool Readiness(int x, int y, int z);			// ���������� ���������� 

	static void ClearCollisionMap();				// ������� ����� ��������
	static bool IsLocked(Vector3Int);				// ����������������� �����
	static bool IsLocked(Vector3);					// ����������������� �����
};