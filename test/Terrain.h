#pragma once
#include "World.h"
#include "PerlinNoise.h"
#include "Typedefs.h"
#include <cmath>

class World;
class Block;
struct Chunk;
/// <summary>
/// ����� ���������� �����������
/// </summary>
class Terrain
{
public:
	int seed = 0; // ����� ��������� 
	block_id* ground_mas = new block_id[] {4,2}; // ������ ������ �����������
	int ground_length = 2; // ����� ������� ������ �����������
	int ground_height = 10; // ����������� ������
	int land_height = 120; // ������������ ������ ���

	PerlinNoise perlinNoise; // ������ ����� �������
	World* world;

	inline float linear(float x, float x0, float x1, float y0, float y1); // �������� ������������
	inline float pick(float x, float x0, float x1); // ������� ������������
	inline void SetGround(Chunk* chunk, int x, int y, int z); // ��������� ���� �����������
	int GetTerrainNoise(int x, int y, int z); // ������ ���� �������
	int GetNoise(int x, int y, int z, float scale = 0.05f, int size = 2); // ��������� ����� �������
	void Generate(Chunk* chunk); // ��������� �����
	inline void SetBlock(Chunk* chunk, int x, int y, int z, block_id block); // ��������� �����
	inline void SetBlock(Chunk* chunk, int x, int y, int z, Block* block); // ��������� �����
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="seed"></param>
	Terrain(int seed, World* world) 
	{
		this->seed = seed;
		this->world = world;
		perlinNoise = PerlinNoise(seed);
	}
	Terrain()
	{
	}
	void SetTree(Chunk* chunk, int x, int y, int z, int height, block_id block, block_id leaves); // �������� ������
};

