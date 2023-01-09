#pragma once
#include <iostream>
#include <vector>
using std::vector;
/// <summary>
/// ����� UV ������
/// </summary>
class UVData
{
private:
	bool inied = false; // ���� �������������
public:
	UVData(); // �����������
	~UVData(); // ����������
	static float stface[8]; // ���������� �����
	vector<float> UVs; // ������ UV
	float* ToArray(); // �������������� � ������
	void AddFace(); // ���������� ������� �����
	void AddUV(float coords[], int length); // ���������� UV
	void AddUV(float x, float y); // ���������� UV
	void AddUV(float x, float y, float dx, float dy); // ���������� UV
	void Clear(); // ������� ����� UV
	float xUVSize = 0.0625f; // UV ������� �� �
	float yUVSize = 0.0625f; // UV ������� �� Y
	float* result; // ������ ����������
};

