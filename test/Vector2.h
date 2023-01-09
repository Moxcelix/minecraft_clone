#pragma once
/// <summary>
/// ����� ���������� �������
/// </summary>
class Vector2
{
public:
	float x, y; // ����������
	Vector2() :x(0), y(0) {} // �����������
	Vector2(float x, float y); // �����������
	Vector2 operator+ (Vector2 val); // �������� ��������
	Vector2 operator- (Vector2 val); // �������� ���������
	Vector2 operator* (float val);  // ��������� �� �����
	bool operator== (Vector2 val); // �������� ���������
	bool operator< (Vector2 val); // �������� ������
	bool operator> (Vector2 val); // �������� ������
	bool operator<= (Vector2 val); // �������� ������ ��� �����
	bool operator>= (Vector2 val); // �������� ������ ��� �����
	float Module(); // ����� �������
};

class Vector2Int
{
public:
	int x, y; // ����������
	Vector2Int() :x(0), y(0) {} // �����������
	Vector2Int(int x, int y); // �����������
	Vector2Int operator+ (Vector2Int val); // �������� ��������
	Vector2Int operator- (Vector2Int val); // �������� ���������
	Vector2Int operator* (float val);  // ��������� �� �����
	bool operator== (Vector2Int val); // �������� ���������
	bool operator< (Vector2Int val); // �������� ������
	bool operator> (Vector2Int val); // �������� ������
	bool operator<= (Vector2Int val); // �������� ������ ��� �����
	bool operator>= (Vector2Int val); // �������� ������ ��� �����
	float Module(); // ����� �������
};


