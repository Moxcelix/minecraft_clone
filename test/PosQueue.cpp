#include "PosQueue.h"
#include<iostream>
/// <summary>
/// ���������� �������� � �������
/// </summary>
/// <param name="element"></param>
void PosQueue::add(Vector3Int* element)
{
	lock_guard<mutex> guard(mtx);

	//if (int l = contains(element))
	//{
	//	/*delete elements[l - 1];

	//	for (int i = l; i < elementsAdded; i++)
	//	{
	//		elements[i - 1] = elements[i];
	//	}

	//	elements[elementsAdded - 1] = element;*/

	//	return;
	//}

	if (elementsAdded < MaxCount) // ���� ��������� ������ ������������� ��������
	{
		elements[elementsAdded] = element; // ���������� ��������
		elementsAdded++;	// ������������� ���-�� ����������� ���������
	}
	else
		delete element; // ������� ���������
}
/// <summary>
/// �������� �� ������� �������� � �������
/// </summary>
/// <param name="element"></param>
/// <returns>������ �������� + 1</returns>
int PosQueue::contains(Vector3Int* element)
{
	for (int i = 0; i < elementsAdded; i++)
	{
		if (*elements[i] == *element) // ���� i-��� ������� ����� ��������
			return i + 1; // ������� ������ + 1
	}
	return 0;
}
/// <summary>
/// ������� �������
/// </summary>
void PosQueue::clear()
{
	lock_guard<mutex> guard(mtx);

	for (int i = 0; i < elementsAdded; i++)
		delete elements[i]; // ������� i-��� �������
	elementsAdded = 0;		// ���-�� ����������� ��������� ����� ����
}
/// <summary>
/// �������� ���������� ��������
/// </summary>
void PosQueue::pop_back()
{
	lock_guard<mutex> guard(mtx);

	if (elementsAdded == 0) // ���� ���-�� ����� 0
		return;				// �������

	elementsAdded--;				// ������������� ���-�� 
	delete elements[elementsAdded];	// �������� ��������
}
/// <summary>
/// �������� ������� ��������
/// </summary>
void PosQueue::pop_front()
{
	lock_guard<mutex> guard(mtx);

	if (elementsAdded == 0) // ���� ���-�� ����� 0
		return;				// �������

	delete elements[0];		// ������� ������
	// �������� ���������
	for (int i = 1; i < elementsAdded; i++)
	{
		elements[i - 1] = elements[i];
	}

	elementsAdded--; // ������������� ���-��
}
/// <summary>
/// ��������� �������
/// </summary>
/// <returns>��������� �������</returns>
Vector3Int* PosQueue::back()
{
	return elements[elementsAdded - 1];
}
/// <summary>
/// ������ �������
/// </summary>
/// <returns>������ �������</returns>
Vector3Int* PosQueue::front()
{
	return elements[0];
}
/// <summary>
/// ������ �������
/// </summary>
/// <returns>���������� ���������</returns>
int PosQueue::size()
{
	return elementsAdded; // ������� ���-�� ���������
}