#pragma once
#include "VertexData.h"
#include "UVData.h"
#include "Block.h"
#include "World.h"
#include "Vector3.h"
#include "Typedefs.h"

#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<mutex>

using namespace std;

class Block;
class World;
class Terrain;
/// <summary>
/// ��������� �����
/// </summary>
struct Chunk
{
public:
	Chunk(); // ����������� �����
	~Chunk(); // ���������� �����
	Chunk(int x, int y, int z, World* world); // ����������� �����

	const static int ChunkSize = 8; // ������ �����
	const static int MaxLight = 8;	// ������������ �������� �����

	Vector3Int pos;				// ������� �����
	World* world;				// ������ �� ���
	Chunk* chunks[27];			// ������ �������� ������

	bool modified = false;		// ���� ����������� �����
	bool is_solid = false;		// ���� ����� ����������� (��� �����)
	static float brightness;	// �������

	block_id GetBlockID(int x, int y, int z); // ��������� ID ����� �� �����������
	inline Block* GetBlock(int x, int y, int z); // ��������� ������ �� ���� �� �����������
	inline Block* GetBlock(block_id ID); // ��������� ������ �� ���� �� ID
	inline bool InRange(int x); // �������� �� ��������� � ����� ����� �� ������ ���������
	inline bool InRange(int x, int y, int z); // �������� �� ��������� � ����� ����� �� ��� ����������

	bool InLightRange(int x, int y, int z); // �������� �� ��������� � ����� ����� �� ��� ���������� ��� �����
	void Generate(); // ��������� �����
	void GetMeshData(VertexData* data, UVData* uv, int x, int y, int z, int layer = 0); // ������������ ������ ����
	void Render(unsigned int texture); // ��������� �����
	void UpdateMesh(); // ���������� ����
	void Update(); // ����������
	void UpdateMem(); // ���������� �����������
	void Init(); // ������������� �����
	void SetBlock(int x, int y, int z, block_id block);	// ��������� ����� �� ����������� � ID
	void SetBlock(int x, int y, int z, Block* block);	// ��������� ����� �� ����������� � ������
	void Modify(); // ��������� �����
	void SaveChunk(); // ���������� �����
	bool LoadChunk();  // �������� �����
	inline void SetLight(int x, int y, int z, char l); // ��������� ����� 
	void UpdateLight(); // ���������� ����� �����
	inline char GetLight(int x, int y, int z); // �������� ����� �� ������������
	inline int CheckLight(int x, int y, int z); // �������� �������� ����� �� ������������
	Vector3 GetLigthColor(int x, int y, int z); // ���� ����� �� �����������

	
private:
	GLfloat* Vertices;	// ������������ ������ ��������� ������
	VertexData data;	// ������ ������
	UVData uv_data;		// ������ UV-�����
	mutex mtx;			// �������

	float* Colors;		// ������������� ������ ������� ������ ������
	float* UVs;			// ������������ ������ UV-��������� ����������� ������

	block_id blocks[ChunkSize][ChunkSize][ChunkSize];				// ��������� ������-����� ������
	bool sky_light[ChunkSize][ChunkSize];							// ��������� ������-����� ��������� �����
	char light_map[ChunkSize * 3][ChunkSize * 3][ChunkSize * 3];	// ����� �������� �����
	char buffer_light_map[ChunkSize][ChunkSize][ChunkSize];			// ������ �������� ����� �������� ������
	
	int ticks = 0;		// ����
	int timeout = 4;	// ������� ���������� ����������

	void ClearCash();	// ������� ������
	
};
