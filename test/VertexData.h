#pragma once
#include <iostream>
#include <vector>
#include "Vector3.h"
#include <GLFW/glfw3.h>

#define UP_MULT 1
#define DOWN_MULT 0.5
#define Y_MULT 0.67
#define X_MULT 0.83

using std::vector;
/// <summary>
/// ����� ������
/// </summary>
struct ColorSquad
{
	Vector3 colors[4]; // ������ ������
	float alpha[4]{ 1,1,1,1 }; // ������ �������� �����-������
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="color"></param>
	ColorSquad(Vector3 color)
	{
		for (int i = 0; i < 4; i++)
			colors[i] = color;
	}
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="color"></param>
	ColorSquad()
	{
		for (int i = 0; i < 4; i++)
			colors[i] = {0,0,0};
	}
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="colors"></param>
	ColorSquad(Vector3 colors[4])
	{
		for (int i = 0; i < 4; i++)
			this->colors[i] = colors[i];
	}
};
/// <summary>
/// ����� ������ ������
/// </summary>
class VertexData
{
private:
	bool inied = false; // ���� �������������

	const static float face_up[12];			// ������� ������� �����
	const static float face_down[12];		// ������� ������ �����
	const static float face_right[12];		// ������� ������ �����
	const static float face_left[12];		// ������� ����� �����
	const static float face_front[12];		// ������� �������� �����
	const static float face_back[12];		// ������� ������ �����
	const static float face_crossRFLB[24];	// ������� ������������ �����
	const static float face_crossRBLF[24];	// ������� ������������ �����

public:
	vector<GLfloat> Vertices; // ������ ������
	vector<float> Colors; // ������ ������

	int face_count = 0; // ���������� ������
	VertexData(); // �����������
	~VertexData(); // ����������

	float* ToArray(); // �������������� � ������
	float* ColorsToArray(); // ����� � ������

	GLfloat* result; // ������ ����������

	void FaceUp(int x, int y, int z);		// ������� �����
	void FaceDown(int x, int y, int z);		// ������ �����
	void FaceRight(int x, int y, int z);	// ������ �����
	void FaceLeft(int x, int y, int z);		// ����� �����
	void FaceFront(int x, int y, int z);	// �������� �����
	void FaceBack(int x, int y, int z);		// ������ �����

	void FaceUp(int x, int y, int z, ColorSquad colors);		// ������� �����
	void FaceDown(int x, int y, int z, ColorSquad colors);		// ������ �����
	void FaceRight(int x, int y, int z, ColorSquad colors);		// ������ �����
	void FaceLeft(int x, int y, int z, ColorSquad colors);		// ����� �����
	void FaceFront(int x, int y, int z, ColorSquad colors);		// �������� �����
	void FaceBack(int x, int y, int z, ColorSquad colors);		// ������ �����

	void FaceParticle(int x, int y, int z, float scale, ColorSquad colors);		// �����

	void FaceCrossRFLB(int x, int y, int z, ColorSquad colors); // ������������ �����
	void FaceCrossRBLF(int x, int y, int z, ColorSquad colors); // ������������ �����

	void SetLayer(int layer);  // ��������� ����

	void Clear(); // ������� ������
};

