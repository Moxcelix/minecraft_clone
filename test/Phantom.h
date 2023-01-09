#pragma once
#include<GLFW/glfw3.h>
#include"World.h"
class World;
/// <summary>
/// ����� �������
/// </summary>
class Phantom
{
private:
	float f = 0.01f, d = -0.01f;
public:
	bool up = false;	// ���� ����� ������
	bool down = false;	// ���� ����� �����
	bool right = false;	// ���� ����� ������
	bool left = false;	// ���� ����� �����
	bool front = false; // ���� ����� �������
	bool back = false;	// ���� ����� �����

	void Render(int x, int y, int z, World* world); // ���������
};

