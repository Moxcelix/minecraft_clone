#include "Inventory.h"
/// <summary>
/// ��������� ���������
/// </summary>
void Inventory::DrawInventory()
{
	int size = 30; // ���������� ����� �����

	for (int i = 0; i < count; i++)
	{
		// ���� �������� �� ��������� - ������-�����
		float r = 0.9;
		float g = 0.9;
		float b = 0.9;

		if (i == current) // ���� ���������� ����� - �������
			b = 0, g = 0, r = 1;

		//����� �� ����� ������ ������
		ui.PrintText(UI::Corner::right, 3, 0, (i - count / 2)*size, Block::GetBlock(data[i])->name + " <", r, g, b);
	}
	ui.Render(); // ����������� ���������������� ���������� ��������� 
}
/// <summary>
/// ����������� ���������
/// </summary>
void Inventory::Update()
{
	current_block = data[current]; // ������� ���� 
}
/// <summary>
/// ���������� ����� � ���������
/// </summary>
/// <param name="id"></param>
void Inventory::AddBlock(int id)
{
	for (int i = 0; i < count; i++) // �������� ������� ����� � ���������
	{
		if (data[i] == id) // ���� ���� ����, ������ ��� ���� ��������
		{
			current = i; 
			break;
		}
	}
	data[current] = id; // ���� ���, ��������� ��� � �������� ����
}
/// <summary>
/// ������������� ��������� 
/// </summary>
void Inventory::Init()
{
	data[0] = Block::stone->id;
	data[1] = Block::cobblestone->id;
	data[2] = Block::oak->id;
	data[3] = Block::glass->id;
	data[4] = Block::dirt->id;
	data[5] = Block::planks->id;
	data[6] = Block::grass->id;
	data[7] = Block::sand->id;
	data[8] = Block::wool->id;
	data[9] = Block::tnt->id;
	data[10] = Block::obsidian->id;
	data[11] = Block::glowstone->id;
	data[12] = Block::mossy_cobblestone->id;
	data[13] = Block::bricks->id;
}