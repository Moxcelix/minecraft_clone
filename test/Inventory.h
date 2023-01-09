#pragma once
#include "UI.h"
#include <iostream>

using namespace std;
/// <summary>
/// ����� ���������
/// </summary>
class Inventory
{
public:
	const static int count = 14;	// ���������� ���������
	int data[count];				// ������ ���������
	UI ui;							// ���������������� ���������
	int current = 0;				// ������� �������
	short int current_block = 0;	// ID �������� �����
	void DrawInventory();			// ���������
	void Init();					// �������������
	void Update();					// ����������
	void AddBlock(int id);			// ���������� �����
};

