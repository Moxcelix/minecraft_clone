#pragma once

#include<queue>
#include<stack>
#include <thread>

#include "Terrain.h"
#include "Player.h"
#include "Debug.h"
#include "PosQueue.h"

using namespace std;
class Terrain;
class Player;
struct Chunk;
/// <summary>
/// ����� ����
/// </summary>
class World
{
public:	
	/// <summary>
	/// ��������� ����������
	/// </summary>
	static struct Settings 
	{
		const static int count = 4;
		bool params[count]{true, true, true, true};

		void Clear() 
		{
			for (int i = 0; i < count; i++)
				params[i] = true;
		}
	}settings;
	/// <summary>
	/// ��������� ��������� �����
	/// </summary>
	struct BlockPos
	{
		int x, y, z;
		short int block;
	};

	static bool is_day; // ���� ���
	const static int MaxChunksCount = 512 * 8; // ������������ ���������� ������
	const static int WorldHeight = 16; // ������������ ������ ����

	PosQueue *RenderQueue; // ������� ����������� ����������
	PosQueue *UpdateQueue; // ������� ����������
	queue<int> *DeleteQueue; // ������� �� ��������
	queue<Vector3Int> *GlobalUpdateQueue; // ������� �� ���������� ����������
	PosQueue *CreateQueue; // ������� �� ��������
	Player* player; // ��������� �� ������
	vector<BlockPos> GlobalBuffer; // ���������� ����� ������
	vector<int> toRemove;; // ������� ������� ������ �� ��������
	Chunk* Chunks[MaxChunksCount]; // ������ ������

	inline Chunk* GetChunk(int x, int y, int z); // �������� ����

	static int seed; // ����� ���������
	static int render_distance; // ��������� ����������
	static string name; // ��� ����
	int chunksUpdateing = 0; // ����������� ������������� ������ 
	int chunksLoaded = 0; // ���������� ����������� ������
	 
	Block* GetBlock(int x, int y, int z); // ��������� �� ����
	Block* GetBlock(Vector3 pos); // ��������� �� ����

	bool CreateChunk(int x, int y, int z); // �������� �����
	short int GetBlockID(int x, int y, int z); // ID �����
	short int GetBlockID(Vector3 pos); // ID �����
	void UpdateIfExcist(int x, int y, int z); // �������� ����, ���� ����������
	void RenderIfExcist(int x, int y, int z); // ���������� ����, ���� ����������
	void AddToRender(int x, int y, int z); // �������� � ������� ��������� ���������
	void AddToUpdate(int x, int y, int z); // �������� � ������� ����������
	void AddToCreate(int x, int y, int z); // ���������� ����� � ������� ��������
	void AddToRender(Chunk* chunk); // �������� ���� � ������� ��������� ���������
	void AddToUpdate(Chunk* chunk); // �������� ���� � ������� ���������� 
	void Update(); // ����������
	void UpdateWorldLighting(); // ���������� ����������� ���������
	void Generate(Chunk* chunk); // ��������� �����
	void SetBlock(int x, int y, int z, short int block, bool update = false); // ��������� �����
	void SetBlock(Vector3 pos, short int block, bool update = false); // ��������� �����
	void Render(unsigned int texture); // ������ ����
	void Clear(); // ������� ����
	void Create(); // �������� ����
	void DeleteChunk(int index); // �������� �����
	void RationalizeBuffer(); // �������������� ������ ������
	void RemoveCash(); // �������� ���� ������
	void UpdateAtPoint(int x, int y, int z); // �������� ����� � �����
	void AddToUpdateAtPoint(int x, int y, int z); // �������� � ������� ���������� � �����
	void UpdateIfEqual(int value1, int value2, int x, int y, int z); // ���������� ��� �������
	void Explode(int x, int y, int z); // ��������� ����������
	void Explode(Vector3 pos); // ��������� ����������
	void AddToUpdateColumn(int x, int y, int z); // �������� � ������� ������� ������
	void SetBufferBlock(int x, int y, int z, short block); // �������� ���� � ������
	char GetLight(int x, int y, int z); // �������� ����� �� ������������
	World(Player* player); // �����������
	~World(); // ����������
};