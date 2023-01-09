#include "Chunk.h"

float Chunk::brightness = 0.2f;

/// <summary>
/// ����������� �����
/// </summary>
Chunk::Chunk()
{
	pos = Vector3Int(0, 0, 0); // ������� �������

	Init(); // ����� �������������
}
/// <summary>
/// ���������� �����
/// </summary>
Chunk::~Chunk()
{
	//cout << sizeof(this) << endl;

	SaveChunk();					// ���������� �����
	delete[] Vertices, UVs, Colors; // �������� ������������ ��������
	world = nullptr;				// ��������� ������ �� ���
	data.Clear();					// ������� ������ ����
	uv_data.Clear();				// ������� ������ UV-�����
}
/// <summary>
/// ����������� �����
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <param name="world"> ��������� �� ��������� ����</param>
Chunk::Chunk(int x, int y, int z, World* world)
{
	pos = Vector3Int(x, y, z);	// �������
	this->world = world;		// ��������� �� ���

	Init();	// ����� �������������
}
/// <summary>
/// ��������� ID ����� �� �����������
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <returns>ID �����</returns>
block_id Chunk::GetBlockID(int x, int y, int z)
{
	if (InRange(x, y, z)) // ���� ������ �����
		return blocks[x][y][z]; // ������� ID �����

	if (z + pos.z < 0 || z + pos.z >= ChunkSize * world->WorldHeight)
		return 0; // ���� �� ��������� ���� �� ������, ������� ID �������
	// ���� � �������� �����
	if (InLightRange(ChunkSize + x, ChunkSize + y, ChunkSize + z))
	{
		// ������� ���������
		int _x = (ChunkSize + x) / ChunkSize;
		int _y = (ChunkSize + y) / ChunkSize;
		int _z = (ChunkSize + z) / ChunkSize;

		Chunk* chunk = chunks[_x + _y * 3 + _z * 9]; // ����������� �����

		if (chunk) // ���� ����������
		{
			// ������ ���������
			_x = pos.x - chunk->pos.x + x;
			_y = pos.y - chunk->pos.y + y;
			_z = pos.z - chunk->pos.z + z;

			if (InRange(_x, _y, _z)) // ���� � �������� �����
				return chunk->blocks[_x][_y][_z]; // ������� ID �����
		}

		return -1; // ������� ID ����������� �������
	}
	else // ����� �������� �������� ID ����� ������ ���� �� ������ ������
		return world->GetBlockID(x + pos.x, y + pos.y, z + pos.z);
}
/// <summary>
/// ������� ������ ����
/// </summary>
void Chunk::ClearCash()
{
	// �������� ��������
	delete[] Vertices;
	delete[] UVs;
	delete[] Colors;
	// ������� ������
	data.Clear();
	uv_data.Clear();
}
/// <summary>
/// ������������� �����
/// </summary>
void Chunk::Init()
{
	// ������������� ��������
	Vertices = new GLfloat;
	UVs = new GLfloat;
	Colors = new GLfloat;

	for (int i = 0; i < ChunkSize; i++)
		for (int j = 0; j < ChunkSize; j++)
			for (int k = 0; k < ChunkSize; k++)
				blocks[i][j][k] = Block::air->id; // ���������� �������� �� ���������

	for (int i = 0; i < 27; i++)
		chunks[i] = nullptr; // �� ��������� ��������� �� ����� ������
}
/// <summary>
/// ��������� �����
/// </summary>
void Chunk::Generate()
{
	if (!LoadChunk()) // ���� ���� �� ����� ����������, ���������� ���
		world->Generate(this);
}
/// <summary>
/// ��������� ������ �� ��������� ����� �� ��� ID
/// </summary>
/// <param name="ID"> ����� </param>
/// <returns> ��������� �� ��������� �����</returns>
inline Block* Chunk::GetBlock(block_id ID)
{
	return Block::GetBlock(ID);
}
/// <summary>
/// ������������ ������ ����
/// </summary>
/// <param name="data"> ��������� �� ������ ����</param>
/// <param name="uv"> ��������� �� ������ ������ UV</param>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <param name="layer"> ���� </param>
void Chunk::GetMeshData(VertexData* data, UVData* uv, int x, int y, int z, int layer)
{
	//if (InRange(x, y, z)) // ���� � �������� �����
	{
		Block* block = GetBlock(GetBlockID(x, y, z));		// �������� ��������� �����
		if (block->GetRenderLayer() == layer)				// ���� � ����� ������� ���� ����������
			block->GetMeshData(data, uv, x, y, z, this);	// ��������� � ������ ���� ������ �����
	}
}
/// <summary>
/// ��������� ������ �� ��������� ����� �� �����������
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <returns>��������� �����</returns>
inline Block* Chunk::GetBlock(int x, int y, int z)
{
	block_id id = GetBlockID(x, y, z); // ��������� ID �����
	return Block::GetBlock(id);
}
/// <summary>
/// �������� �� ��������� � ������� ����� �� ������ ���������
/// </summary>
/// <param name="x"> �������� �����</param>
/// <returns>�������������� ����� � �������, ������� ������� �����</returns>
inline bool Chunk::InRange(int x)
{
	return x >= 0 && x < ChunkSize;
}
/// <summary>
/// �������� �� ��������� � ������� ����� �� ��� ����������
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <returns>�������������� ����� � ����� ������� �����</returns>
inline bool Chunk::InRange(int x, int y, int z)
{
	return InRange(x) && InRange(y) && InRange(z); // ���� � �������� �� ���� ����������
}
/// <summary>
/// �������� �� ��������� � ������� ����� �� ��� ���������� ��� �����
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <returns>�������������� ����� � �������� ������� �����</returns>
bool Chunk::InLightRange(int x, int y, int z)
{
	return (x >= 0 && x < ChunkSize * 3) && (y >= 0 && y < ChunkSize * 3) && (z >= 0 && z < ChunkSize * 3);
}
/// <summary>
/// ���������� ��������� �����
/// </summary>
void Chunk::UpdateMesh() // ���������� ����
{
	lock_guard<mutex> guard(mtx); // ������ �� ����������� �������

	UpdateLight();

	ticks = 0; // ���������� ������� �����
	world->chunksUpdateing++; // ������������� ���������� ������ �� ����������

	ClearCash(); // ������� ������ ������

	for (int x = 0; x < ChunkSize; x++)
		for (int y = 0; y < ChunkSize; y++)
			for (int z = 0; z < ChunkSize; z++)
				GetMeshData(&data, &uv_data, x, y, z, 0); // ��������� ������ ������

	// ��������������� �������� � �������
	Vertices = data.ToArray();
	UVs = uv_data.ToArray();
	Colors = data.ColorsToArray();
}
/// <summary>
/// ���������� ��������� �����
/// </summary>
void Chunk::Update()
{
	int b_count = 0; // �������, ��� ����������� ������������ ����

	for (int x = 0; x < ChunkSize; x++)
	{
		for (int y = 0; y < ChunkSize; y++)
		{
			bool detected = false; // ���� ����������� �����

			for (int z = 0; z < ChunkSize; z++)
			{
				if (!detected) // ���� �� ���������
					if (!GetBlock(x, y, z)->Transparent()) // ���� �� ����������
						detected = true; // ���������
			}

			if (detected) // ���� ���������
				b_count++; // ������������� ����������
		}
	}

	is_solid = b_count >= ChunkSize * ChunkSize; // ��������, ���� ����������� ������ ��� ����� �������
}
/// <summary>
/// ��������� �����
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <param name="block"> ID �����</param>
inline void Chunk::SetBlock(int x, int y, int z, block_id block)
{
	if (InRange(x, y, z)) // ���� � ������ �����
		blocks[x][y][z] = block;
	else // ����� �������� ����� � ���
		world->SetBlock(x + pos.x, y + pos.y, z + pos.z, block);
}
/// <summary>
/// ��������� �����
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <param name="block"> ��������� �� ��������� �����</param>
void Chunk::SetBlock(int x, int y, int z, Block* block) //
{
	SetBlock(x, y, z, block->id); // ���������� ����
}
/// <summary>
/// ���������� �����
/// </summary>
void Chunk::SaveChunk()
{
	if (!modified) // ���� ���� �� ���������, �� ��������� ���
		return;

	ofstream stream; // ������ ������ ������

	stream.open(save_folder + World::name + "/" + to_string(pos.x) + " " + to_string(pos.y) + " " + to_string(pos.z) + ".dat", ios::binary);

	for (int x = 0; x < Chunk::ChunkSize; x++) {
		for (int y = 0; y < Chunk::ChunkSize; y++) {
			for (int z = 0; z < Chunk::ChunkSize; z++)
			{
				stream << blocks[x][y][z] << " "; // ���������� ��� ����� � �����
			}
		}
	}
	stream.close(); // ������� �����

}
/// <summary>
/// �������� �����
/// </summary>
/// <returns>������� � ����� ����������</returns>
bool Chunk::LoadChunk()
{
	ifstream stream; // ������ ������ ������
	stream.open(save_folder + World::name + "/" + to_string(pos.x) + " " + to_string(pos.y) + " " + to_string(pos.z) + ".dat", ios::binary);

	if (stream.is_open())
	{
		for (int x = 0; x < Chunk::ChunkSize; x++) {
			for (int y = 0; y < Chunk::ChunkSize; y++) {
				for (int z = 0; z < Chunk::ChunkSize; z++)
				{
					stream >> blocks[x][y][z]; // ��������� ��� ����� �� �����
				}
			}
		}
		stream.close(); // ������� �����
		return true;
	}
	return false;
}
/// <summary>
/// ��������� ����� �����
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <returns>������, ���������� RGB ������ �����</returns>
Vector3 Chunk::GetLigthColor(int x, int y, int z)
{
	float l = (GetLight(x, y, z) / float(MaxLight)) * (1 - brightness) + brightness; // �������� �������
	return Vector3(l, l, l); // �������� �����
}
/// <summary>
/// ���������� �����������
/// </summary>
void Chunk::UpdateMem()
{
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
			{
				// ������ ���������
				int X = (x - 1) * ChunkSize;
				int Y = (y - 1) * ChunkSize;
				int Z = (z - 1) * ChunkSize;
				// ��������� ��������� �� ����
				chunks[x + y * 3 + z * 9] =
					world->GetChunk(pos.x + X, pos.y + Y, pos.z + Z);
			}
}
/// <summary>
/// ���������� �����
/// </summary>
void Chunk::UpdateLight()
{
	for (int x = 0; x < ChunkSize * 3; x++)
		for (int y = 0; y < ChunkSize * 3; y++)
			for (int z = 0; z < ChunkSize * 3; z++)
				light_map[x][y][z] = 0; // ������� ����� �����

	for (int x = 0; x < ChunkSize; x++)
		for (int y = 0; y < ChunkSize; y++)
			for (int z = 0; z < ChunkSize; z++)
			{
				buffer_light_map[x][y][z] = 0; // ������� ����� ������ �����

				char light = GetBlock(x, y, z)->Luminosity(); // ���������� �����

				if (light) // ���� � ����� ���������� �� 0
					light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize] = light + 1; // �������� ���������� + 1
			}


	Chunk* chunk = chunks[22]; // ������� ����

	if (World::is_day) // ���� ����
		for (int x = 0; x < ChunkSize; x++)
			for (int y = 0; y < ChunkSize; y++)
			{
				sky_light[x][y] = true; // ����� ����������� ���������
				for (int z = ChunkSize - 1; z >= 0; z--)
				{
					// ���� ���� ���������� � ������ ��� ����, ��������� ������������ ���������
					if ((!chunk || chunk->sky_light[x][y]) && GetBlock(x, y, z)->Transparent())
						light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize] = MaxLight;
					else // ����� �������� �� ����� ���� � ������������� ���
					{
						sky_light[x][y] = false;
						break;
					}
				}
			}

	for (int i = 0; i < 27; i++) // ���� �������� ������
	{
		if (i == 13) // 13 - ���� ����
			continue;

		if (chunks[i]) // ���� i-��� ���� ����
		{
			// ������� ���������
			int sx = pos.x - chunks[i]->pos.x;
			int sy = pos.y - chunks[i]->pos.y;
			int sz = pos.z - chunks[i]->pos.z;

			for (int x = 0; x < ChunkSize; x++)
				for (int y = 0; y < ChunkSize; y++)
					for (int z = 0; z < ChunkSize; z++)
					{
						// �������� ����� � �������� ����� � ������� ����� �����
						char l = chunks[i]->CheckLight(x + sx, y + sy, z + sz);

						if (l > buffer_light_map[x][y][z]) // ���� �������� ������ ����� ��������������
							buffer_light_map[x][y][z] = l; // ���������� ����� �������� ����� ������
					}
		}
	}

	for (int l = MaxLight + 1; l > 0; l--) // ���� ������ �����
		for (int x = 0; x < ChunkSize * 3; x++)
			for (int y = 0; y < ChunkSize * 3; y++)
				for (int z = 0; z < ChunkSize * 3; z++)
				{
					if (light_map[x][y][z] == l) // ���� ������� � ����� ����� ������� �������, �������������� ����
					{
						// ������ ��������������� �����
						SetLight(x + 1 - ChunkSize, y - ChunkSize, z - ChunkSize, light_map[x][y][z] - 1);
						SetLight(x - 1 - ChunkSize, y - ChunkSize, z - ChunkSize, light_map[x][y][z] - 1);
						SetLight(x - ChunkSize, y + 1 - ChunkSize, z - ChunkSize, light_map[x][y][z] - 1);
						SetLight(x - ChunkSize, y - 1 - ChunkSize, z - ChunkSize, light_map[x][y][z] - 1);
						SetLight(x - ChunkSize, y - ChunkSize, z + 1 - ChunkSize, light_map[x][y][z] - 1);
						SetLight(x - ChunkSize, y - ChunkSize, z - 1 - ChunkSize, light_map[x][y][z] - 1);
					}
				}


}
/// <summary>
/// ��������� �������� �����
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <param name="l"></param>
inline void Chunk::SetLight(int x, int y, int z, char l)
{
	if (light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize] < l && GetBlock(x, y, z)->Transparent())
	{
		if (InRange(x + ChunkSize, y + ChunkSize, z + ChunkSize)) // ���� � ��������
		{
			// ���� ���������� �������� ������ � ���� ����������
			if (buffer_light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize] < l)
				light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize] = l; // ���������� ����� ��������
		}
		else if (InLightRange(x + ChunkSize, y + ChunkSize, z + ChunkSize)) // ���� � �������� 
		{
			light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize] = l; // ���������� ����� ��������
		}
	}
}
/// <summary>
/// �������� �����
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <returns>�������� �����</returns>
inline char Chunk::GetLight(int x, int y, int z)
{
	if (InRange(x, y, z)) // ���� � ��������
	{
		// �������� ����� ������ ����� � ������ ������ �����
		return max(light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize], buffer_light_map[x][y][z]);
	}
	if (InRange(x) && InRange(y)) // ��� ����� �� ��������� ���� �� ��� ��������
	{
		if (pos.z + z < 0 || pos.z + z >= world->WorldHeight * ChunkSize)
		{
			// �������� ����� � �����
			char light = light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize];

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					if (i == 1 && j == 1) // ���� ���� 
						continue;

					Chunk* chunk = chunks[i + j * 3 + 9]; // ���� �� �������� ����

					if (chunk) // ���� ����������
					{
						// ������� ��������� � ���������� �������� ������
						int _x = x + (2 - i) * ChunkSize;
						int _y = y + (2 - j) * ChunkSize;
						int _z = z + ChunkSize;
						// ��������� �������� ����� �� ��������� �����
						char l = chunk->light_map[_x][_y][_z];

						if (l > light) // ���� ����� �������� ����� ������
							light = l; // ���������� ����� ��������
					}
				}
			return light; // ����������� �������� �����
		}
	}
	// ���� �� ������� �����, ������� ����� ����� ������ ����
	return world->GetLight(x + pos.x, y + pos.y, z + pos.z);
}
/// <summary>
/// �������� ����� �� ���������
/// </summary>
/// <param name="x"> �������� �����</param>
/// <param name="y"> �������� �����</param>
/// <param name="z"> ��������� �����</param>
/// <returns>�������� �����</returns>
inline int Chunk::CheckLight(int x, int y, int z)
{
	if (InRange(x, y, z)) // ���� � ������ �����
		return max(light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize], buffer_light_map[x][y][z]);
	if (InLightRange(x + ChunkSize, y + ChunkSize, z + ChunkSize)) // ���� � �������� ������� �����
		return light_map[x + ChunkSize][y + ChunkSize][z + ChunkSize];
	return 0;
}
/// <summary>
/// ���������
/// </summary>
void Chunk::Modify()
{
	for (int i = 0; i < 27; i++)
		if (chunks[i])
			chunks[i]->modified = true;
}
/// <summary>
/// ��������� �����
/// </summary>
void Chunk::Render(unsigned int texture)
{
	if (data.face_count == 0) // ���� ��� ������ � �����, �� �� ���������� ��� ����
		return;

	static float s = Chunk::ChunkSize * 0.5f; // �������� ������� �����
	static float shift = Chunk::ChunkSize * 0.5f - 0.5f; // ��������

	glBindTexture(GL_TEXTURE_2D, texture); // �������� �������� � ���� ���������������
	// ��������� ���������� � �������� ��� ��������� ����
	glTexCoordPointer(2, GL_FLOAT, 0, UVs);
	glVertexPointer(3, GL_FLOAT, 0, Vertices);
	glColorPointer(3, GL_FLOAT, 0, Colors);
	//17�404
	glDrawArrays(GL_QUADS, 0, data.face_count * 4); // ��������� ������

	glBindTexture(GL_TEXTURE_2D, 0);				// ������� �������� �� ���� ���������������

	if (Debug::bounds) // ���� ������� ����� ������ ������
		Debug::DrawBox({ shift, shift, shift }, { s, s, s }, { .9f, .9f, .9f });

	// �������������� ����������
	if (ticks <= timeout && ticks > -1)
		ticks++;

	if (ticks > timeout)
	{
		UpdateMem();
		UpdateMesh();
		ticks = -1;
	}
}