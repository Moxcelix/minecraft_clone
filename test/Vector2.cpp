#include "Vector2.h"
#include <cmath>
/// <summary>
/// �����������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
Vector2::Vector2(float x, float y) 
{
	this->x = x;
	this->y = y;
}
/// <summary>
/// �������� ��������
/// </summary>
/// <param name="val"></param>
/// <returns>������ �����</returns>
Vector2 Vector2::operator+ (Vector2 val)
{
	return Vector2(x + val.x, y + val.y); 
}
/// <summary>
/// �������� ���������
/// </summary>
/// <param name="val"></param>
/// <returns>������ ��������</returns>
Vector2 Vector2::operator- (Vector2 val)
{ 
	return Vector2(x - val.x, y - val.y);
}
/// <summary>
/// �������� ���������
/// </summary>
/// <param name="val"></param>
/// <returns>��������� ������������</returns>
Vector2 Vector2::operator* (float val)
{
	return Vector2(x * val, y * val);
}
/// <summary>
/// ����� �������
/// </summary>
/// <returns>����� �������</returns>
float Vector2::Module() 
{
	return sqrtf(x * x + y * y);
}

bool Vector2::operator== (Vector2 val) { return x == val.x && y == val.y; }		// �������� ���������
bool Vector2::operator< (Vector2 val) { return Module() < val.Module(); }		// �������� ������
bool Vector2::operator> (Vector2 val) { return Module() > val.Module(); }		// �������� ������
bool Vector2::operator<= (Vector2 val) { return Module() <= val.Module(); }		// �������� ������ ��� �����
bool Vector2::operator>= (Vector2 val) { return Module() >= val.Module(); }		// �������� ������ ��� �����
/// <summary>
/// �����������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
Vector2Int::Vector2Int(int x, int y)
{
	this->x = x;
	this->y = y;
}
/// <summary>
/// �������� ��������
/// </summary>
/// <param name="val"></param>
/// <returns>������ �����</returns>
Vector2Int Vector2Int::operator+ (Vector2Int val)
{
	return Vector2Int(x + val.x, y + val.y);
}
/// <summary>
/// �������� ���������
/// </summary>
/// <param name="val"></param>
/// <returns>������ ��������</returns>
Vector2Int Vector2Int::operator- (Vector2Int val)
{
	return Vector2Int(x - val.x, y - val.y);
}
/// <summary>
/// �������� ���������
/// </summary>
/// <param name="val"></param>
/// <returns>��������� ������������</returns>
Vector2Int Vector2Int::operator* (float val)
{
	return Vector2Int(x * val, y * val);
}
/// <summary>
/// ����� �������
/// </summary>
/// <returns>����� �������</returns>
float Vector2Int::Module()
{
	return sqrtf(x * x + y * y);
}

bool Vector2Int::operator== (Vector2Int val) { return x == val.x && y == val.y; }	// �������� ���������
bool Vector2Int::operator< (Vector2Int val) { return Module() < val.Module(); }		// �������� ������
bool Vector2Int::operator> (Vector2Int val) { return Module() > val.Module(); }		// �������� ������
bool Vector2Int::operator<= (Vector2Int val) { return Module() <= val.Module(); }	// �������� ������ ��� �����
bool Vector2Int::operator>= (Vector2Int val) { return Module() >= val.Module(); }	// �������� ������ ��� �����