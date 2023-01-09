#pragma once
#include "VertexData.h"
#include "UVData.h"
#include "Chunk.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Bound.h"
#include "Typedefs.h"
#include<iostream>
#include<vector>

using std::string;
using std::vector;
struct Chunk;
/// <summary>
/// ����� �����
/// </summary>
class Block 
{
public:
	Block(short int id, string name); // ����������� �����
	block_id id = 0; // ID ����� 
	string name = "?"; // ��� �����
	Block(); // ����������� �����
	// ������ �� ��������� ���������� ������
	static Block* air;					// ������
	static Block* grass;				// ���
	static Block* stone;				// ������
	static Block* oak;					// ���
	static Block* birch;				// �����
	static Block* leaves;				// ������
	static Block* dirt;					// �����
	static Block* cobblestone;			// ��������
	static Block* glass;				// ������
	static Block* tall_grass;			// ������� �����
	static Block* poppy;				// ���
	static Block* dandelion;			// ���������
	static Block* planks;				// �����
	static Block* sand;					// �����
	static Block* wool;					// ������
	static Block* tnt;					// ���
	static Block* obsidian;				// ��������
	static Block* glowstone;			// �����������
	static Block* birch_leaves;			// ������ �����
	static Block* bedrock;				// �������� ������
	static Block* mossy_cobblestone;	// �������� ��������
	static Block* bricks;				// �������
	static Block* null;					// �������
	
	static Block** blocks;				// ������ ������

	operator int() const // �������� ����������
	{
		return id;
	}

	static vector<Block*> BlockList; // ������ ������
	/// <summary>
	///  ��������� ������ �� ���� �� ��� ID
	/// </summary>
	/// <param name="ID"></param>
	/// <returns></returns>
	static constexpr inline Block* GetBlock(short int ID)
	{
		if (ID == -1)
			return null;

		return blocks[ID];
	}
	static void Init(); // ������������� 
	/// <summary>
	/// ������������ �����������
	/// </summary>
	enum class Direction : int
	{
		Up = 0,
		Down = 1,
		Right = 2,
		Left = 3,
		Front = 4,
		Back = 5
	};
	/// <summary>
	/// ������������ ���� ������
	/// </summary>
	enum class BlockLayer
	{
		AIR,
		GLASS,
		VOID,
		HERB,
		LEAVES,
		OTHER
	};

	virtual void GetMeshData(VertexData* data, UVData* uv, int x, int y, int z, Chunk* chunk); // ��������� ������ ���� �����
	inline virtual BlockLayer GetLayer(); // ���� �����
	inline virtual Vector2 TileCoord(Direction direction); // ���������� ������� ������ �����
	inline virtual Vector3 Color(Direction direction); // ����� ������
	inline virtual char GetRenderLayer(); // ��������� ���� ����������
	inline virtual bool Transparent(); // ������������ ��� �����
	inline virtual char Luminosity(); // ������������ ��� �����
	inline virtual bool Solid(); // ��������
	inline virtual Bound GetBounds(); // ������� �����
};

