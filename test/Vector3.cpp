#include "Vector3.h"
#include <cmath>
/// <summary>
/// �����������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
/// <summary>
/// �����������
/// </summary>
Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
/// <summary>
/// �������� ������
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3::operator< (Vector3 val)
{
	return Module() < val.Module();
}
/// <summary>
/// �������� ������
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3::operator> (Vector3 val)
{
	return Module() > val.Module();
}
/// <summary>
/// �������� ������ ��� �����
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3::operator<= (Vector3 val)
{
	return Module() <= val.Module();
}
/// <summary>
/// �������� ������ ��� �����
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3::operator>= (Vector3 val)
{
	return Module() >= val.Module();
}
/// <summary>
/// ��������� �����
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>������ �����</returns>
Vector3 Vector3::clrm(Vector3 a, Vector3 b) 
{
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}
/// <summary>
/// �����������
/// </summary>
Vector3Int::~Vector3Int()
{
	
}
/// <summary>
/// �������� ��������
/// </summary>
/// <param name="val"></param>
/// <returns>������ �����</returns>
Vector3 Vector3::operator+ (Vector3 val)
{
	return Vector3(x + val.x, y + val.y, z + val.z);
}
/// <summary>
/// �������� ���������
/// </summary>
/// <param name="val"></param>
/// <returns>������ ��������</returns>
Vector3 Vector3::operator- (Vector3 val)
{
	return Vector3(x - val.x, y - val.y, z - val.z);
}
/// <summary>
/// �������� ��������� �� �����
/// </summary>
/// <param name="val"></param>
/// <returns>������ ������������ �� �����</returns>
Vector3 Vector3::operator* (float val)
{
	return Vector3(x * val, y * val, z * val);
}
/// <summary>
/// �������� ���������
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3::operator== (Vector3 val)
{
	return x == val.x && y == val.y && z == val.z;
}
/// <summary>
/// ����� �������
/// </summary>
/// <returns></returns>
float Vector3::Module()
{
	return sqrtf(x * x + y * y + z * z);
}
/// <summary>
/// �����������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
Vector3Int::Vector3Int(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
/// <summary>
/// �����������
/// </summary>
Vector3Int::Vector3Int()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
/// <summary>
/// �������� ���������
/// </summary>
/// <param name="val"></param>
/// <returns>������ �����</returns>
Vector3Int Vector3Int::operator+ (Vector3Int val)
{
	return Vector3Int(x + val.x, y + val.y, z + val.z);
}
/// <summary>
/// �������� ���������
/// </summary>
/// <param name="val"></param>
/// <returns>������ �������� </returns>
Vector3Int Vector3Int::operator- (Vector3Int val)
{
	return Vector3Int(x - val.x, y - val.y, z - val.z);
}
/// <summary>
/// �������� ��������� �� �����
/// </summary>
/// <param name="val"></param>
/// <returns>������ ������������ �� �����</returns>
Vector3Int Vector3Int::operator* (float val)
{
	return Vector3Int(x * val, y * val, z * val);
}
/// <summary>
/// �������� ���������
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3Int::operator== (Vector3Int val)
{
	return x == val.x && y == val.y && z == val.z;
}
/// <summary>
/// ����� �������
/// </summary>
/// <returns></returns>
float Vector3Int::Module()
{
	return sqrtf(x * x + y * y + z * z);
}
/// <summary>
/// ���������� ����� �������
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
float Vector3Int::Distance(Vector3Int a, Vector3Int b) 
{
	return (a - b).Module();
}
/// <summary>
/// �������� ������
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3Int::operator< (Vector3Int val) 
{
	return Module() < val.Module();
}
/// <summary>
/// �������� ������
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3Int::operator> (Vector3Int val)
{
	return Module() > val.Module();
}
/// <summary>
/// �������� ������ ��� �����
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3Int::operator<= (Vector3Int val)
{
	return Module() <= val.Module();
}
/// <summary>
/// �������� ������ ��� �����
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool Vector3Int::operator>= (Vector3Int val)
{
	return Module() >= val.Module();
}