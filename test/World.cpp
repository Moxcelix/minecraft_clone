#include "World.h"
#include<iostream>
#include<fstream>
#include<Windows.h>

Terrain terrain; // ��������� ����������
int World::render_distance = 8; // ��������� ���������� �� ���������
int World::seed = 0; // ����� ���������
bool World::is_day = true; // ����
string World::name = "my world"; // ��� ����
World::Settings World::settings = World::Settings(); // ��������� ���������� ����
/// <summary>
/// �����������
/// </summary>
/// <param name="player"></param>
World::World(Player* player)
{
	this->player = player;
	player->world = this;

	Create();
}
/// <summary>
/// �������� ����
/// </summary>
void World::Create()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));	// ������������� ������� ��������� �����
	ifstream istream;	// ����� ������
	istream.open(save_folder + name + "/world.bin"); // �������� ������

	if (istream.is_open()) // ���� ���� ����
	{
		Debug::Log("world \"" + name + "\" opened");
		istream >> World::seed; // ����� ��������� ����

		float x, y, z, xRot, zRot;
		istream >> x >> y >> z >> xRot >> zRot; // ��������� ������

		for (int i = 0; i < 4; i++)
			istream >> settings.params[i]; // �������� i

		istream.close(); // �������� ������

		player->Init(x, y, z, xRot, zRot); // ������������� ������
	}
	else // �����
	{
		Debug::Log("world \"" + name + "\" created");
		World::seed = rand(); // ��������� ������ ����
		player->Init(player->start_pos.x, player->start_pos.y, player->start_pos.z, 0, 90); // ������������� ������
	}
	// ������������� ��������
	chunksLoaded = 0;
	RenderQueue = new PosQueue();
	CreateQueue = new PosQueue();
	UpdateQueue = new PosQueue();
	DeleteQueue = new queue<int>();
	GlobalUpdateQueue = new queue<Vector3Int>();
	terrain = Terrain(World::seed, this);
}
/// <summary>
/// ���������� ����
/// </summary>
World::~World()
{
	ofstream stream; // ����� ������
	stream.open(save_folder + name + "/world.bin"); // ���� ������
	if (stream.is_open()) // ���� ���������� �������
	{
		stream << World::seed << endl; // ����� ���������
		player->Save(stream); // ���������� ���������� ������
		for (int i = 0; i < 4; i++)
			stream << settings.params[i] << endl; // ���������� ��������� i
		stream.close(); // �������� ������
	}
	GlobalBuffer.clear(); // ������� ����������� ������
	// �������� ��������
	delete RenderQueue;
	delete CreateQueue;
	delete UpdateQueue;
	delete GlobalUpdateQueue;

	// �������� ������
	for (int i = 0; i < chunksLoaded; i++)
		delete Chunks[i];
}

/// <summary>
/// ���������� ����������� ���������
/// </summary>
void World::UpdateWorldLighting()
{
	Debug::Log("global lighting update");

	for (int j = 0; j < 2; j++)
		for (int i = 0; i < chunksLoaded; i++)
		{
			Chunk* chunk = Chunks[i];
			if (!chunk || GetChunk(chunk->pos.x, chunk->pos.y, chunk->pos.z + Chunk::ChunkSize))
				continue;

			for (int k = chunk->pos.z; k >= 0; k -= Chunk::ChunkSize)
			{
				GlobalUpdateQueue->push({ chunk->pos.x, chunk->pos.y, k });

				Chunk* c = GetChunk(chunk->pos.x, chunk->pos.y, k);

				if (c && c->is_solid)
					break;
			}
		}
}
/// <summary>
/// ������� ����
/// </summary>
void World::Clear()
{
	GlobalBuffer.clear();
	RenderQueue->clear();
	CreateQueue->clear();
	for (int i = 0; i < chunksLoaded; i++)
		delete Chunks[i];
	chunksLoaded = 0;
}
/// <summary>
/// ���������� ����� � ������� ��������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::AddToCreate(int x, int y, int z)
{
	if (z < 0 || z >= WorldHeight * Chunk::ChunkSize)
		return;

	//chunk* c = GetChunk(x, y, z)

	if (Chunk* c = GetChunk(x, y, z)) 
	{
		return;
	}

	if (x < 0)
		x -= Chunk::ChunkSize - 1;
	if (y < 0)
		y -= Chunk::ChunkSize - 1;

	x = (x / Chunk::ChunkSize) * Chunk::ChunkSize;
	y = (y / Chunk::ChunkSize) * Chunk::ChunkSize;
	z = (z / Chunk::ChunkSize) * Chunk::ChunkSize;

	CreateQueue->add(new Vector3Int(x, y, z));
}
/// <summary>
/// �������� �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns></returns>
bool World::CreateChunk(int x, int y, int z)
{
	if (chunksLoaded >= MaxChunksCount)
		return true;

	Chunk* chunk = GetChunk(x, y, z);

	if (chunk)
		return false;

	if (Debug::active)
		Debug::log << "chunk {" << x << ", " << y << ", " << z << "} created" << endl;

	float d = Vector3Int::Distance(player->IntPosition, Vector3Int(x, y, z));

	if (d > render_distance * Chunk::ChunkSize)
		return false;

	Chunks[chunksLoaded] = new Chunk(x, y, z, this);
	Chunks[chunksLoaded]->UpdateMem();
	Chunks[chunksLoaded]->Generate();
	Chunks[chunksLoaded]->Update();
	Chunks[chunksLoaded]->UpdateMesh();

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			for (int k = -1; k <= 1; k++)
			{
				if (i == 0 && j == 0 && k == 0)
					continue;

				int X = i * Chunk::ChunkSize + x;
				int Y = j * Chunk::ChunkSize + y;
				int Z = k * Chunk::ChunkSize + z;

				RenderIfExcist(X, Y, Z);
			}

	chunksLoaded++;

	return true;
}
/// <summary>
/// ������ ����
/// </summary>
void World::Render(unsigned int texture)
{
	for (int i = 0; i < chunksLoaded; i++)
	{
		if (!Chunks[i]) // ���� ����� ���, ����������
			continue;

		Vector3Int pos = Chunks[i]->pos; // ������� i-���� �����
		glTranslatef(pos.x, pos.y, pos.z); // ����������� ��������� �� ����������
		Chunks[i]->Render(texture); // ������ �����
		glTranslatef(-pos.x, -pos.y, -pos.z); // ������� ����������� 
	}
}
/// <summary>
/// ID �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns>ID ����� </returns>
short int World::GetBlockID(int x, int y, int z)
{
	Chunk* chunk = GetChunk(x, y, z); // ������ ����� �� �����������
	if (chunk) // ���� ���� ����
	{
		return chunk->GetBlockID(
			x - chunk->pos.x,
			y - chunk->pos.y,
			z - chunk->pos.z);
	}

	if (z < 0 || z >= WorldHeight * Chunk::ChunkSize)
		return 0; // ID �������

	return -1; // ID �������
}
/// <summary>
/// ID �����
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
short int World::GetBlockID(Vector3 pos)
{
	return GetBlockID(pos.x, pos.y, pos.z);
}
/// <summary>
/// ��������� �� ����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns>��������� �� ���� </returns>
Block* World::GetBlock(int x, int y, int z)
{
	return Block::GetBlock(GetBlockID(x, y, z));
}
/// <summary>
/// ��������� �� ����
/// </summary>
/// <param name="pos"></param>
/// <returns>��������� �� ���� </returns>
Block* World::GetBlock(Vector3 pos)
{
	return Block::GetBlock(GetBlockID(pos.x, pos.y, pos.z));
}
/// <summary>
/// �������� ����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns>��������� �� ����</returns>
Chunk* World::GetChunk(int x, int y, int z)
{
	if (x < 0)
		x -= Chunk::ChunkSize - 1;
	if (y < 0)
		y -= Chunk::ChunkSize - 1;

	if (z < 0 || z >= WorldHeight * Chunk::ChunkSize)
		return nullptr;

	x = (x / Chunk::ChunkSize) * Chunk::ChunkSize;
	y = (y / Chunk::ChunkSize) * Chunk::ChunkSize;
	z = (z / Chunk::ChunkSize) * Chunk::ChunkSize;

	for (int i = 0; i < chunksLoaded; i++)
	{
		Chunk* c = Chunks[i];

		if (c && c->pos.x == x && c->pos.y == y && c->pos.z == z)
		{
			return c;
		}
	}

	return nullptr;
}
/// <summary>
/// ��������� ���������� 
/// </summary>
/// <param name="pos"></param>
void World::Explode(Vector3 pos)
{
	Explode(pos.x, pos.y, pos.z);
}
/// <summary>
/// ��������� ����������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::Explode(int x, int y, int z)
{
	int r = rand() % 3 + 3;

	for (int i = -r; i <= r; i++)
		for (int j = -r; j <= r; j++)
			for (int k = -r; k <= r; k++)
			{
				int R = r + rand() % 2;
				if (i * i + j * j + k * k <= R * R)
				{
					int id = GetBlockID(x + i, y + j, z + k);

					if (id == Block::bedrock->id)
						continue;

					SetBlock(x + i, y + j, z + k, 0, false);

					if (id == Block::tnt->id)
						Explode(x + i, y + j, z + k);

					Chunk* chunk = GetChunk(x + i, y + j, z + k);

					if (chunk)
						chunk->Modify();
				}
			}

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			for (int k = -1; k <= 1; k++)
			{
				int X = i * Chunk::ChunkSize + x;
				int Y = j * Chunk::ChunkSize + y;
				int Z = k * Chunk::ChunkSize + z;

				Chunk* chunk = GetChunk(X, Y, Z);

				if (chunk)
					chunk->UpdateMesh(), chunk->Update();
			}

	AddToUpdateColumn(x, y, z);
}
/// <summary>
/// �������� ����� � �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::UpdateAtPoint(int x, int y, int z)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			for (int k = -1; k <= 1; k++)
			{
				if (i == 0 && j == 0 && k == 0)
					continue;

				int X = i * Chunk::ChunkSize + x;
				int Y = j * Chunk::ChunkSize + y;
				int Z = k * Chunk::ChunkSize + z;

				UpdateIfExcist(X, Y, Z);
			}
}
/// <summary>
/// �������� � ������� ���������� � �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::AddToUpdateAtPoint(int x, int y, int z)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			for (int k = -1; k <= 1; k++)
			{
				if (i == 0 && j == 0 && k == 0)
					continue;

				int X = i * Chunk::ChunkSize + x;
				int Y = j * Chunk::ChunkSize + y;
				int Z = k * Chunk::ChunkSize + z;

				AddToUpdate(X, Y, Z);
			}
}
/// <summary>
/// ���������� ����, ���� ����������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::RenderIfExcist(int x, int y, int z)
{
	Chunk* chunk = GetChunk(x, y, z);

	if (chunk)
		AddToRender(chunk);
}
/// <summary>
/// �������� ����, ���� ����������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::UpdateIfExcist(int x, int y, int z)
{
	Chunk* chunk = GetChunk(x, y, z);

	if (chunk)
	{
		AddToUpdate(chunk);
	}
}
/// <summary>
/// �������� � ������� ��������� ���������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::AddToRender(int x, int y, int z)
{
	RenderQueue->add(new Vector3Int(x, y, z));
}
/// <summary>
/// �������� � ������� ����������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::AddToUpdate(int x, int y, int z)
{
	UpdateQueue->add(new Vector3Int(x, y, z));
}
/// <summary>
/// �������� ���� � ������� ��������� ���������
/// </summary>
/// <param name="chunk"></param>
void World::AddToRender(Chunk* chunk)
{
	AddToRender(chunk->pos.x, chunk->pos.y, chunk->pos.z);
}
/// <summary>
/// �������� ���� � ������� ����������
/// </summary>
/// <param name="chunk"></param>
void World::AddToUpdate(Chunk* chunk)
{
	AddToUpdate(chunk->pos.x, chunk->pos.y, chunk->pos.z);
}
/// <summary>
/// �������� �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns>�������� �����</returns>
char World::GetLight(int x, int y, int z)
{
	Chunk* chunk = GetChunk(x, y, z);

	if (chunk)
		return chunk->GetLight(x - chunk->pos.x, y - chunk->pos.y, z - chunk->pos.z);

	return 0;
}
/// <summary>
/// �������� � ������� ������� ������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::AddToUpdateColumn(int x, int y, int z)
{
	int s = Chunk::ChunkSize;

	z = (z / s) * s;

	for (int k = z + s; k >= 0; k -= s)
	{
		Chunk* chunk = GetChunk(x, y, k);

		if (!chunk)
			break;

		for (int i = -s; i <= s; i += s)
			for (int j = -s; j <= s; j += s)
				AddToUpdate(x + i, y + j, k);

		if (chunk->is_solid)
			break;
	}
}
/// <summary>
/// ����������
/// </summary>
void World::Update()
{
	// �������� ������
	for (int i = 0; i < chunksLoaded && i < 8; i++)
	{
		float d = Vector3Int::Distance(player->IntPosition, Chunks[i]->pos);

		if (d > render_distance * Chunk::ChunkSize)
		{
			DeleteChunk(i);
		}
	}

	
	// ����� ���������� ���������� ������
	thread t([&] {
		for (int i = 0; i < render_chunk_throughput; i++)
			if (RenderQueue->size())
			{
				Vector3Int* pos = RenderQueue->back();

				if (UpdateQueue->contains(pos))
				{
					RenderQueue->pop_back();
					continue;
				}

				Chunk* chunk = GetChunk(pos->x, pos->y, pos->z);
				if (chunk)
				{
					chunk->UpdateMem();
					chunk->UpdateMesh();
				}
				RenderQueue->pop_back();
			}
		});

	// ���������� ����������� ���������
	for (int i = 0; i < render_chunk_throughput * 2; i++)
		if (GlobalUpdateQueue->size())
		{
			Vector3Int pos = GlobalUpdateQueue->front();
			Chunk* chunk = GetChunk(pos.x, pos.y, pos.z);

			if (chunk)
				chunk->UpdateMesh();

			GlobalUpdateQueue->pop();
		}

	// �������� ������
	for (int i = 0; i < create_chunk_throughput; i++)
	{
		while (CreateQueue->size())
		{
			Vector3Int* pos = CreateQueue->back();
			bool done = CreateChunk(pos->x, pos->y, pos->z);
			CreateQueue->pop_back();

			if (done)
				break;
		}
	}
	// ���������� ������
	for (int i = 0; i < update_chunk_throughput; i++)
		if (UpdateQueue->size())
		{
			Vector3Int* pos = UpdateQueue->front();

			Chunk* chunk = GetChunk(pos->x, pos->y, pos->z);
			if (chunk)
			{
				chunk->UpdateMesh();
			}
			UpdateQueue->pop_front();
		}
	t.join(); // ������������� �������

	RationalizeBuffer(); // �������������� ������ ������
	RemoveCash(); // ������� ����	
}
/// <summary>
/// �������� �����
/// </summary>
/// <param name="index"></param>
void World::DeleteChunk(int index)
{
	float d = Vector3Int::Distance(player->IntPosition, Chunks[index]->pos);

	if (d <= render_distance * Chunk::ChunkSize) // ���� ���� �� ��� �������� ��������
		return;

	int x = Chunks[index]->pos.x;
	int y = Chunks[index]->pos.y;
	int z = Chunks[index]->pos.z;

	if (Debug::active)
		Debug::log << "chunk {" << x << ", " << y << ", " << z << "} deleted" << endl;

	delete Chunks[index]; // ����� �����������
	Chunks[index] = nullptr; // ��������� ���������
	chunksLoaded--; // ���������� ���������� ����������� ������

	if (chunksLoaded > 0) // ����� ������ � �������
	{
		for (int i = index; i < chunksLoaded; i++)
		{
			Chunks[i] = Chunks[i + 1];
		}

		Chunks[chunksLoaded] = nullptr;
	}
	// ���������� ����������� ������
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			for (int k = -1; k <= 1; k++)
			{
				if (i == 0 && j == 0 && k == 0)
					continue;

				int X = i * Chunk::ChunkSize + x;
				int Y = j * Chunk::ChunkSize + y;
				int Z = k * Chunk::ChunkSize + z;

				Chunk* chunk = GetChunk(X, Y, Z);

				if (chunk)
					chunk->UpdateMem();
			}

}
/// <summary>
/// ���������� ��� �������
/// </summary>
/// <param name="value1"></param>
/// <param name="value2"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void World::UpdateIfEqual(int value1, int value2, int x, int y, int z)
{
	if (value1 == value2)
	{
		Chunk* chunk = GetChunk(x, y, z);

		if (chunk)
		{
			chunk->UpdateMesh();
		}
	}
}
/// <summary>
/// �������� ���� ������
/// </summary>
void World::RemoveCash()
{
	int l = GlobalBuffer.size();
	sort(toRemove.begin(), toRemove.end(), greater<int>());
	for (int i = 0; i < toRemove.size(); i++)
	{
		if (toRemove[i] < l)
			GlobalBuffer.erase(GlobalBuffer.begin() + toRemove[i]);
	}
	toRemove.clear();
}
/// <summary>
/// �������������� ������ ������
/// </summary>
void World::RationalizeBuffer()
{
	for (int i = 0; i < GlobalBuffer.size(); i++)
		if (player->GetDistance(GlobalBuffer[i].x, GlobalBuffer[i].y, GlobalBuffer[i].z) > (render_distance + 1.1) * Chunk::ChunkSize)
		{
			toRemove.push_back(i);
		}
}
/// <summary>
/// ��������� �����
/// </summary>
/// <param name="pos"></param>
/// <param name="block"></param>
/// <param name="update"></param>
void World::SetBlock(Vector3 pos, short int block, bool update)
{
	SetBlock(pos.x, pos.y, pos.z, block, update);
}
/// <summary>
/// ��������� �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="block"></param>
/// <param name="update"></param>
void World::SetBlock(int x, int y, int z, short int block, bool update)
{
	Chunk* chunk = GetChunk(x, y, z);

	if (chunk)
	{
		chunk->SetBlock(x - chunk->pos.x, y - chunk->pos.y, z - chunk->pos.z, block);
		if (update)
		{
			chunk->UpdateMesh();
			chunk->Modify();
			chunk->Update();

			// ���������� ���������� �������� ������, ���� ���� �� �������
			UpdateIfEqual(x - chunk->pos.x, 0, x - 1, y, z);
			UpdateIfEqual(x - chunk->pos.x, Chunk::ChunkSize - 1, x + 1, y, z);
			UpdateIfEqual(y - chunk->pos.y, 0, x, y - 1, z);
			UpdateIfEqual(y - chunk->pos.y, Chunk::ChunkSize - 1, x, y + 1, z);
			UpdateIfEqual(z - chunk->pos.z, 0, x, y, z - 1);
			UpdateIfEqual(z - chunk->pos.z, Chunk::ChunkSize - 1, x, y, z + 1);

			UpdateAtPoint(x, y, z);
			AddToUpdateColumn(x, y, z);
			AddToUpdate(chunk);
		}
	}
	else // ���� ����� ��� ���, ��������� ���� � �����
		SetBufferBlock(x, y, z, block);

}
/// <summary>
/// ���������� ���� � ������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="block"></param>
void World::SetBufferBlock(int x, int y, int z, short block) 
{
	Chunk* chunk = GetChunk(x, y, z);

	if (chunk)
	{
		chunk->SetBlock(x - chunk->pos.x, y - chunk->pos.y, z - chunk->pos.z, block);
		return;
	}

	BlockPos block_pos = { x ,y, z ,block };
	BlockPos* finded;

	if (find_if(GlobalBuffer.begin(), GlobalBuffer.end(),
		[&](BlockPos p) -> bool
		{
			if (p.x == block_pos.x && p.y == block_pos.y && p.z == block_pos.z)
			{
				finded = &p;
				return true;
			}
			return false;
		}) == GlobalBuffer.end())
	{
		GlobalBuffer.push_back(block_pos);
	}
	else
	{
		finded->block = block;
	}
}
/// <summary>
/// ���������
/// </summary>
/// <param name="chunk"></param>
void World::Generate(Chunk* chunk)
{
	terrain.Generate(chunk);
}