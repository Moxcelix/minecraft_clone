#pragma once
/// <summary>
/// ����� ���������� �������
/// </summary>
class Vector3
{
public:
	float x, y, z; // ����������
	Vector3(float x, float y, float z); // �����������
	Vector3(); // �����������
	Vector3 operator+ (Vector3 val); // �������� ��������
	Vector3 operator- (Vector3 val); // �������� ���������
	Vector3 operator* (float val);  // ��������� �� �����
	bool operator== (Vector3 val); // �������� ���������
	bool operator< (Vector3 val);  // �������� ������
	bool operator> (Vector3 val);  // �������� ������
	bool operator<= (Vector3 val); // �������� ������ ��� �����
	bool operator>= (Vector3 val); // �������� ������ ��� �����
	float Module(); // ����� �������

	static Vector3 clrm(Vector3 a, Vector3 b); // ��������� �����
};

struct Vector3Int 
{
public:
	int x, y, z; // ����������
	Vector3Int(int x, int y, int z); // �����������
	Vector3Int(); // �����������
	~Vector3Int(); // ����������
	int GetHashCode() // ��� ���
	{
		int hash = 47;
		hash = hash * 227 + x;
		hash = hash * 227 + y;
		hash = hash * 227 + z;
		return hash;
	}
	Vector3Int operator+ (Vector3Int val); // �������� ��������
	Vector3Int operator- (Vector3Int val); // �������� ���������
	Vector3Int operator* (float val); // ��������� �� �����
	bool operator< (Vector3Int val);  // �������� ������
	bool operator> (Vector3Int val);  // �������� ������
	bool operator<= (Vector3Int val); // �������� ������ ��� �����
	bool operator>= (Vector3Int val); // �������� ������ ��� �����
	bool operator== (Vector3Int val); // �������� ���������
	static float Distance(Vector3Int a, Vector3Int b); // ����������
	float Module(); // ����� �������
};

