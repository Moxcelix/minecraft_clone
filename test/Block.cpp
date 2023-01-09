#include "Block.h"
struct Chunk; // ��������� �����
vector<Block*> Block::BlockList = vector<Block*>(); // ������������� ������ ������
Block** Block::blocks = new Block * (); // ������ ������
/// <summary>
/// ����������� �����
/// </summary>
Block::Block()
{

}
/// <summary>
/// ���������� ������ ����
/// </summary>
/// <param name="data"></param>
/// <param name="uv"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="chunk"></param>
void Block::GetMeshData(VertexData* data, UVData* uv, int x, int y, int z, Chunk* chunk)
{
	// ���������� ������ ���� � ������������ � ������������� � �����
	if (chunk->GetBlock(x, y, z + 1)->GetLayer() != GetLayer()
		&& chunk->GetBlock(x, y, z + 1) != null)
	{
		Vector3 color = Vector3::clrm(chunk->GetLigthColor(x, y, z + 1), Color(Direction::Up));
		ColorSquad squad{ color };
		data->FaceUp(x, y, z, squad); // ���������� ������ ����� �����

		float i = TileCoord(Direction::Up).x; // ��������� �������� �������� � ������
		float j = TileCoord(Direction::Up).y; // ��������� �������� �������� � ������

		uv->AddUV(i, j); // ���������� UV-��������� ����� �����
	}
	// ��������� ����� - ����������
	if (chunk->GetBlock(x, y, z - 1)->GetLayer() != GetLayer()
		&& chunk->GetBlock(x, y, z - 1) != null)
	{
		Vector3 color = Vector3::clrm(chunk->GetLigthColor(x, y, z - 1), Color(Direction::Down));
		ColorSquad squad{ color };
		data->FaceDown(x, y, z, squad);

		float i = TileCoord(Direction::Down).x;
		float j = TileCoord(Direction::Down).y;

		uv->AddUV(i, j);
	}
	if (chunk->GetBlock(x, y + 1, z)->GetLayer() != GetLayer()
		&& chunk->GetBlock(x, y + 1, z) != null)
	{
		Vector3 color = Vector3::clrm(chunk->GetLigthColor(x, y + 1, z), Color(Direction::Front));
		ColorSquad squad{ color };
		data->FaceFront(x, y, z, squad);

		float i = TileCoord(Direction::Front).x;
		float j = TileCoord(Direction::Front).y;

		uv->AddUV(i, j);
	}
	if (chunk->GetBlock(x, y - 1, z)->GetLayer() != GetLayer()
		&& chunk->GetBlock(x, y - 1, z) != null)
	{
		Vector3 color = Vector3::clrm(chunk->GetLigthColor(x, y - 1, z), Color(Direction::Back));
		ColorSquad squad{ color };
		data->FaceBack(x, y, z, squad);

		float i = TileCoord(Direction::Back).x;
		float j = TileCoord(Direction::Back).y;

		uv->AddUV(i, j);
	}
	if (chunk->GetBlock(x + 1, y, z)->GetLayer() != GetLayer()
		&& chunk->GetBlock(x + 1, y, z) != null)
	{
		Vector3 color = Vector3::clrm(chunk->GetLigthColor(x + 1, y, z), Color(Direction::Right));
		ColorSquad squad{ color };
		data->FaceRight(x, y, z, squad);

		float i = TileCoord(Direction::Right).x;
		float j = TileCoord(Direction::Right).y;

		uv->AddUV(i, j);
	}
	if (chunk->GetBlock(x - 1, y, z)->GetLayer() != GetLayer()
		&& chunk->GetBlock(x - 1, y, z) != null)
	{
		Vector3 color = Vector3::clrm(chunk->GetLigthColor(x - 1, y, z), Color(Direction::Left));
		ColorSquad squad{ color };
		data->FaceLeft(x, y, z, squad);

		float i = TileCoord(Direction::Left).x;
		float j = TileCoord(Direction::Left).y;

		uv->AddUV(i, j);
	}
}
/// <summary>
/// ������� �����
/// </summary>
/// <returns></returns>
Bound Block::GetBounds() 
{
	return Bound();
}
/// <summary>
/// ��������
/// </summary>
/// <returns>�������� �����</returns>
bool Block::Solid()
{
	return true;
}
/// <summary>
/// ������������ ����� ��� �����
/// </summary>
/// <returns>������������ �����</returns>
bool Block::Transparent()
{
	return false;
}
/// <summary>
/// ���������� �����
/// </summary>
/// <returns>������� ����������</returns>
char Block::Luminosity()
{
	return 0;
}
/// <summary>
/// ���� ����� �����
/// </summary>
/// <param name="direction"></param>
/// <returns>������ � RGB ��������</returns>
Vector3 Block::Color(Direction direction)
{
	return Vector3(1, 1, 1);
}
/// <summary>
/// ���������� ������� ������ ����� 
/// </summary>
/// <param name="direction"></param>
/// <returns>������</returns>
Vector2 Block::TileCoord(Direction direction)
{
	return Vector2(0, 0);
}
/// <summary>
/// ���� �����
/// </summary>
/// <returns>���� �����</returns>
Block::BlockLayer Block::GetLayer()
{
	return BlockLayer::OTHER;
}
/// <summary>
/// �������������
/// </summary>
void Block::Init()
{
	int size = BlockList.size(); // ������ ������ ������

	blocks = new Block * [size]; // ������������� ������� ���������� ������ 

	// ������������� �� ID
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (BlockList[j]->id == i)
				blocks[i] = BlockList[j];

	BlockList.clear();
}
/// <summary>
/// ����������� �����
/// </summary>
/// <param name="id"></param>
/// <param name="name"></param>
Block::Block(short int id, string name)
{
	this->id = id;				// ID �����
	this->name = name;			// ��� �����
	BlockList.push_back(this);	// ���������� ������ � ������ ������
}
/// <summary>
/// ���� ����������
/// </summary>
/// <returns>����� ����</returns>
char Block::GetRenderLayer()
{
	return 0;
}

//�����

/// <summary>
///  ���� �������
/// </summary>
class BlockAir : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockAir(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// �������� 
	/// </summary>
	/// <returns>��������</returns>
	virtual bool Solid()  // ��������
	{
		return false;
	}
	/// <summary>
	/// ������ ����
	/// </summary>
	virtual void GetMeshData(VertexData* data, UVData* uv, int x, int y, int z, Chunk* chunk)
	{
		// ���� ������� �� �������� ����������
	}
	/// <summary>
	/// ����
	/// </summary>
	/// <returns>����</returns>
	virtual BlockLayer GetLayer()
	{
		return BlockLayer::AIR; // ���� �������
	}
	/// <summary>
	/// ������������
	/// </summary>
	/// <returns>������������</returns>
	virtual bool Transparent()
	{
		return true; // ����������
	}
};
/// <summary>
/// ���� ����� � ������ 
/// </summary>
class BlockGrass : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockGrass(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		switch (direction)
		{
		case Direction::Up:		// ������� �����
			return Vector2(0, 15);
		case Direction::Down:	// ������ �����
			return Vector2(2, 15);

		}
		// ��������� �����
		return Vector2(3, 15);
	}
	/// <summary>
	/// ���� 
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>���� �����</returns>
	virtual Vector3 Color(Direction direction) // ������� ����� ����� ������������ � ������
	{
		if (direction == Direction::Up)
			return Vector3(0.56, 0.81, 0.3);
		return Vector3(1, 1, 1);
	}

};
/// <summary>
/// ���� �����
/// </summary>
class BlockStone : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockStone(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(1, 15);

	}
};
/// <summary>
/// ���� �����
/// </summary>
class BlockDirt : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockDirt(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(2, 15);
	}
};
/// <summary>
/// ���� ����
/// </summary>
class BlockOak : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockOak(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		switch (direction)
		{
		case Direction::Up:
		case Direction::Down:
			return Vector2(5, 14);

		}
		return Vector2(4, 14);
	}

};
/// <summary>
/// ���� ���������
/// </summary>
class BlockCobblestone : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockCobblestone(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(0, 14);
	}
};
/// <summary>
/// ���� ��������� ���������
/// </summary>
class BlockMossyCobblestone : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockMossyCobblestone(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(4, 13);
	}
};
/// <summary>
/// ���� ������
/// </summary>
class BlockLeaves : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockLeaves(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ������ ����
	/// </summary>
	virtual void GetMeshData(VertexData* data, UVData* uv, int x, int y, int z, Chunk* chunk)
	{
		// ������� �����
		Vector3 color = Vector3::clrm(chunk->GetLigthColor(x, y, z + 1), Color(Direction::Up));
		ColorSquad squad{ color };
		data->FaceUp(x, y, z, squad); // ���������� ������ ����� �����

		float i = TileCoord(Direction::Up).x; // ��������� �������� �������� � ������
		float j = TileCoord(Direction::Up).y; // ��������� �������� �������� � ������

		uv->AddUV(i, j); // ���������� UV-��������� ����� �����

		// ������ �����
		color = Vector3::clrm(chunk->GetLigthColor(x, y, z - 1), Color(Direction::Down));
		squad = ColorSquad{ color };
		data->FaceDown(x, y, z, squad);

		i = TileCoord(Direction::Down).x;
		j = TileCoord(Direction::Down).y;

		uv->AddUV(i, j);

		// �������� �����
		color = Vector3::clrm(chunk->GetLigthColor(x, y + 1, z), Color(Direction::Front));
		squad = ColorSquad{ color };
		data->FaceFront(x, y, z, squad);

		i = TileCoord(Direction::Front).x;
		j = TileCoord(Direction::Front).y;

		uv->AddUV(i, j);

		// ������ �����
		color = Vector3::clrm(chunk->GetLigthColor(x, y - 1, z), Color(Direction::Back));
		squad = ColorSquad{ color };
		data->FaceBack(x, y, z, squad);

		i = TileCoord(Direction::Back).x;
		j = TileCoord(Direction::Back).y;

		uv->AddUV(i, j);

		// ������ �����
		color = Vector3::clrm(chunk->GetLigthColor(x + 1, y, z), Color(Direction::Right));
		squad = ColorSquad{ color };
		data->FaceRight(x, y, z, squad);

		i = TileCoord(Direction::Right).x;
		j = TileCoord(Direction::Right).y;

		uv->AddUV(i, j);
		
		// ����� �����
		color = Vector3::clrm(chunk->GetLigthColor(x - 1, y, z), Color(Direction::Left));
		squad = ColorSquad{ color };
		data->FaceLeft(x, y, z, squad);

		i = TileCoord(Direction::Left).x;
		j = TileCoord(Direction::Left).y;

		uv->AddUV(i, j);
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(4, 12);
	}
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>���� �����</returns>
	virtual Vector3 Color(Direction direction)
	{
		return Vector3(0.4, 0.75, 0.25); // ��� ����� ������������ � ������
	}
	/// <summary>
	/// ����
	/// </summary>
	/// <returns>����</returns>
	virtual BlockLayer GetLayer()
	{
		return BlockLayer::LEAVES; // ���� ������
	}
};
/// <summary>
/// ���� ������
/// </summary>
class BlockBirchLeaves : public BlockLeaves
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockBirchLeaves(int id, string name) : BlockLeaves(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(4, 12);
	}
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>���� �����</returns>
	virtual Vector3 Color(Direction direction)
	{
		return Vector3(0.5, 0.7, 0.33); // ��� ����� ������������ � ������
	}
};
/// <summary>
/// ���� ������
/// </summary>
class BlockGlass : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockGlass(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(1, 12);
	}
	/// <summary>
	/// ����
	/// </summary>
	/// <returns>����</returns>
	virtual BlockLayer GetLayer()
	{
		return BlockLayer::GLASS; // ���� ������
	}
	/// <summary>
	/// ������������
	/// </summary>
	/// <returns>������������</returns>
	virtual bool Transparent()
	{
		return true;
	}
};
/// <summary>
/// ����������� ���� �������
/// </summary>
class BlockNull : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockNull(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ������ ����
	/// </summary>
	virtual void GetMeshData(VertexData* data, UVData* uv, int x, int y, int z, Chunk* chunk)
	{

	}
	/// <summary>
	/// ����
	/// </summary>
	/// <returns>����</returns>
	virtual BlockLayer GetLayer()
	{
		return BlockLayer::VOID; // ���� �������
	}
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>��������</returns>
	virtual bool Solid()
	{
		return false;
	}
};
/// <summary>
/// ���� ����� 
/// </summary>
class BlockBirch : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockBirch(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		switch (direction)
		{
		case Direction::Up:
		case Direction::Down:
			return Vector2(5, 14);

		}
		return Vector2(5, 8);
	}

};
/// <summary>
/// ���� ������� ����� 
/// </summary>
class BlockTallGrass : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockTallGrass(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(7, 13);
	}
	/// <summary>
	/// ��������
	/// </summary>
	/// <returns>��������</returns>
	virtual bool Solid() 
	{
		return false;
	}

	/// <summary>
	/// ������ ����
	/// </summary>
	virtual void GetMeshData(VertexData* data, UVData* uv, int x, int y, int z, Chunk* chunk)
	{
		// �������� �� ���������� ���������
		float i = TileCoord(Direction::Up).x; // �������� ��������
		float j = TileCoord(Direction::Up).y; // �������� ��������

		// ����
		Vector3 color = Vector3::clrm(chunk->GetLigthColor(x, y, z), Color(Direction::Up));
		ColorSquad squad{ color };
		
		data->FaceCrossRFLB(x, y, z, squad); // ������ ������������ �����
		data->FaceCrossRBLF(x, y, z, squad); // ������ ������������ �����
		// ���������� UV ��������
		uv->AddUV(i, j);
		uv->AddUV(i, j);
		uv->AddUV(i, j);
		uv->AddUV(i, j);
	}
	/// <summary>
	/// ������������
	/// </summary>
	/// <returns>������������</returns>
	virtual bool Transparent()
	{
		return true;
	}
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>���� �����</returns>
	virtual Vector3 Color(Direction direction)
	{
		return grass->Color(Direction::Up);
	}
	/// <summary>
	/// ����
	/// </summary>
	/// <returns>����</returns>
	virtual BlockLayer GetLayer()
	{
		return BlockLayer::HERB; // ���� ��� ������-�������� ��������
	}
	/// <summary>
	/// �������
	/// </summary>
	/// <returns></returns>
	virtual Bound GetBounds() 
	{
		return Bound(.7f, .7f, .7f);
	}
};
/// <summary>
/// ���� ����
/// </summary>
class BlockPoppy : public BlockTallGrass
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockPoppy(int id, string name) : BlockTallGrass(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(12, 15);
	}
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>���� �����</returns>
	virtual Vector3 Color(Direction direction)
	{
		return Vector3(1, 1, 1);
	}
	/// <summary>
	/// �������
	/// </summary>
	/// <returns></returns>
	virtual Bound GetBounds()
	{
		return Bound(.4f, .4f, .6f);
	}
};
/// <summary>
/// ���� ����������
/// </summary>
class BlockDandelion : public BlockPoppy
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockDandelion(int id, string name) : BlockPoppy(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(13, 15);
	}
};
/// <summary>
/// ���� �����
/// </summary>
class BlockPlanks : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockPlanks(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(4, 15);
	}
};
/// <summary>
/// ���� ����� 
/// </summary>
class BlockSand : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockSand(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(2, 14);
	}
};
/// <summary>
/// ���� ������
/// </summary>
class BlockWool : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockWool(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(0, 11);
	}
};
/// <summary>
/// ���� ��� 
/// </summary>
class BlockTNT : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockTNT(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	virtual Vector2 TileCoord(Direction direction)
	{
		switch (direction)
		{
		case Direction::Up:
			return Vector2(9, 15);
		case Direction::Down:
			return Vector2(10, 15);

		}
		return Vector2(8, 15);
	}
};
/// <summary>
/// ���� ���������
/// </summary>
class BlockObsidian : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockObsidian(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(7, 4);
	}
};
/// <summary>
/// ���� ���������
/// </summary>
class BlockBricks : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockBricks(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(7, 15);
	}
};
/// <summary>
/// ���� �������� ������
/// </summary>
class BlockBedrock : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockBedrock(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns>������</returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(1, 14);
	}
};
/// <summary>
/// ���� ��������� 
/// </summary>
class BlockGlowstone : public Block
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="id"></param>
	/// <param name="name"></param>
	BlockGlowstone(int id, string name) : Block(id, name)
	{
	}
	/// <summary>
	/// ���������� ��������
	/// </summary>
	/// <param name="direction"></param>
	/// <returns></returns>
	virtual Vector2 TileCoord(Direction direction)
	{
		return Vector2(9, 9);
	}
	/// <summary>
	/// ����������
	/// </summary>
	/// <returns>�������</returns>
	virtual char Luminosity()
	{
		return Chunk::MaxLight;
	}
};
// ������ �� ��������� ���������� ������
Block* Block::null = new BlockNull(-1, "none");
Block* Block::air = new BlockAir(0, "air");
Block* Block::stone = new BlockStone(1, "stone");
Block* Block::dirt = new BlockDirt(2, "dirt");
Block* Block::cobblestone = new BlockCobblestone(3, "cobblestone");
Block* Block::grass = new BlockGrass(4, "grass");
Block* Block::oak = new BlockOak(5, "oak");
Block* Block::glass = new BlockGlass(6, "glass");
Block* Block::leaves = new BlockLeaves(7, "leaves");
Block* Block::birch = new BlockBirch(8, "birch");
Block* Block::tall_grass = new BlockTallGrass(9, "tall_grass");
Block* Block::poppy = new BlockPoppy(10, "poppy");
Block* Block::dandelion = new BlockDandelion(11, "dandelion");
Block* Block::planks = new BlockPlanks(12, "planks");
Block* Block::sand = new BlockSand(13, "sand");
Block* Block::wool = new BlockWool(14, "wool");
Block* Block::tnt = new BlockTNT(15, "tnt");
Block* Block::obsidian = new BlockObsidian(16, "obsidian");
Block* Block::glowstone = new BlockGlowstone(17, "glowstone");
Block* Block::birch_leaves = new BlockBirchLeaves(18, "birch_leaves");
Block* Block::bedrock = new BlockBedrock(19, "bedrock");
Block* Block::mossy_cobblestone = new BlockMossyCobblestone(20, "mossy_cobblestone");
Block* Block::bricks = new BlockBricks(21, "bricks");