#pragma once
#include"Vector3.h"
#include<mutex>
#include<iostream>

using namespace std;
/// <summary>
/// ����� ������� �������
/// </summary>
class PosQueue
{
private:
	mutex mtx;
	const static int MaxCount = 512; // ������������� ���������� ��������� � �������
	Vector3Int* elements[MaxCount]; // ������ ���������� �� ��������
	int elementsAdded = 0; // ���������� ����������� ���������
public:	
	void add(Vector3Int*); // ���������� ��������
	void pop_back(); // �������� ���������� ��������
	void pop_front(); // �������� ������� ��������
	void clear(); // ������� ������� 
	Vector3Int* front(); // ������ �������
	Vector3Int* back(); // ��������� �������
	int contains(Vector3Int*); // �������� �� ������� �������� � �������
	int size(); // ������ �������
};

