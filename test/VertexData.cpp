#include "VertexData.h"
#include <iostream>
/// <summary>
/// �����������
/// </summary>
VertexData::VertexData()
{

}
/// <summary>
/// ����������
/// </summary>
VertexData::~VertexData()
{
	Clear();
	if (inied)
		delete[] result;
}
/// <summary>
/// ������� ������
/// </summary>
void VertexData::Clear()
{
	Vertices.clear();
	Colors.clear();
	face_count = 0;
}
/// <summary>
/// �������������� � ������
/// </summary>
/// <returns></returns>
float* VertexData::ToArray()
{
	inied = true;

	int size = Vertices.size();

	result = new GLfloat[size];

	for (int i = 0; i < size; i++)
		result[i] = Vertices[i];

	return result;
}
/// <summary>
/// ������� �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void VertexData::FaceUp(int x, int y, int z)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_up[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 12; i++)
		Colors.push_back(1);
}
/// <summary>
/// ������ �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void VertexData::FaceDown(int x, int y, int z)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_down[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 12; i++)
		Colors.push_back(0.7f);
}
/// <summary>
/// ������ �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void VertexData::FaceRight(int x, int y, int z)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_right[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 12; i++)
		Colors.push_back(0.9f);
}
/// <summary>
/// ����� �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void VertexData::FaceLeft(int x, int y, int z)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_left[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 12; i++)
		Colors.push_back(0.9f);
}
/// <summary>
/// �������� �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void VertexData::FaceFront(int x, int y, int z)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_front[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 12; i++)
		Colors.push_back(0.8f);
}
/// <summary>
/// ������ �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void VertexData::FaceBack(int x, int y, int z)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_back[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 12; i++)
		Colors.push_back(0.8f);
}
/// <summary>
/// ������� �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="colors"></param>
void VertexData::FaceUp(int x, int y, int z, ColorSquad colors)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_up[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}

	for (int i = 0; i < 4; i++)
	{
		Colors.push_back(colors.colors[i].x * UP_MULT);
		Colors.push_back(colors.colors[i].y * UP_MULT);
		Colors.push_back(colors.colors[i].z * UP_MULT);
	}
}
/// <summary>
/// ������ �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="colors"></param>
void VertexData::FaceDown(int x, int y, int z, ColorSquad colors)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_down[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 4; i++)
	{
		Colors.push_back(colors.colors[i].x * DOWN_MULT);
		Colors.push_back(colors.colors[i].y * DOWN_MULT);
		Colors.push_back(colors.colors[i].z * DOWN_MULT);
	}
}
/// <summary>
/// ������ �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="colors"></param>
void VertexData::FaceRight(int x, int y, int z, ColorSquad colors)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_right[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 4; i++)
	{
		Colors.push_back(colors.colors[i].x * X_MULT);
		Colors.push_back(colors.colors[i].y * X_MULT);
		Colors.push_back(colors.colors[i].z * X_MULT);
	}
}
/// <summary>
/// ����� �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="colors"></param>
void VertexData::FaceLeft(int x, int y, int z, ColorSquad colors)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_left[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 4; i++)
	{
		Colors.push_back(colors.colors[i].x * X_MULT);
		Colors.push_back(colors.colors[i].y * X_MULT);
		Colors.push_back(colors.colors[i].z * X_MULT);
	}
}
/// <summary>
/// �������� �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="colors"></param>
void VertexData::FaceFront(int x, int y, int z, ColorSquad colors)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_front[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 4; i++)
	{
		Colors.push_back(colors.colors[i].x * Y_MULT);
		Colors.push_back(colors.colors[i].y * Y_MULT);
		Colors.push_back(colors.colors[i].z * Y_MULT);
	}
}
/// <summary>
/// ������ �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="colors"></param>
void VertexData::FaceBack(int x, int y, int z, ColorSquad colors)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_back[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 4; i++)
	{
		Colors.push_back(colors.colors[i].x * Y_MULT);
		Colors.push_back(colors.colors[i].y * Y_MULT);
		Colors.push_back(colors.colors[i].z * Y_MULT);
	}
}

/// <summary>
/// ����� � ������
/// </summary>
/// <returns></returns>
float* VertexData::ColorsToArray()
{
	int size = Colors.size();
	result = new GLfloat[size];

	for (int i = 0; i < size; i++)
	{
		result[i] = Colors[i];
	}

	return result;
}
/// <summary>
/// ������������ �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="colors"></param>
void VertexData::FaceCrossRFLB(int x, int y, int z, ColorSquad colors)
{
	face_count += 2;
	for (int i = 0; i < 24; i++)
	{
		float coord = face_crossRFLB[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 8; i++)
	{
		Colors.push_back(colors.colors[i % 4].x * UP_MULT);
		Colors.push_back(colors.colors[i % 4].y * UP_MULT);
		Colors.push_back(colors.colors[i % 4].z * UP_MULT);
	}
}
/// <summary>
/// ������������ �����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="colors"></param>
void VertexData::FaceCrossRBLF(int x, int y, int z, ColorSquad colors)
{
	face_count += 2;
	for (int i = 0; i < 24; i++)
	{
		float coord = face_crossRBLF[i];
		if (i % 3 == 0)
			coord += x;
		if (i % 3 == 1)
			coord += y;
		if (i % 3 == 2)
			coord += z;
		Vertices.push_back(coord);
	}
	for (int i = 0; i < 8; i++)
	{
		Colors.push_back(colors.colors[i % 4].x * UP_MULT);
		Colors.push_back(colors.colors[i % 4].y * UP_MULT);
		Colors.push_back(colors.colors[i % 4].z * UP_MULT);
	}
}
void VertexData::FaceParticle(int x, int y, int z, float scale, ColorSquad colors)
{
	face_count++;
	for (int i = 0; i < 12; i++)
	{
		float coord = face_up[i] * scale;

		if (i % 3 == 0) 
			coord += x;
		if (i % 3 == 1) 
			coord += y;
		if (i % 3 == 2) 
			coord += z;

		Vertices.push_back(coord);
	}
	for (int i = 0; i < 4; i++)
	{
		Colors.push_back(colors.colors[i % 4].x * UP_MULT);
		Colors.push_back(colors.colors[i % 4].y * UP_MULT);
		Colors.push_back(colors.colors[i % 4].z * UP_MULT);
	}
}
/// <summary>
/// ��������� ����
/// </summary>
/// <param name="layer"></param>
void VertexData::SetLayer(int layer)
{
	//Layer.push_back(layer);
}

const float VertexData::face_up[12]
{
	-0.5, -0.5, 0.5,
	-0.5, 0.5, 0.5,
	0.5, 0.5, 0.5,
	0.5, -0.5, 0.5
};
// ������� ������ �����
const float VertexData::face_down[12]
{
	0.5, 0.5, -0.5,
	-0.5, 0.5, -0.5,
	-0.5, -0.5, -0.5,
	0.5, -0.5, -0.5
};
// ������� ������ �����
const float VertexData::face_right[12]
{
	0.5, 0.5, -0.5,
	0.5, -0.5, -0.5,
	0.5, -0.5, 0.5,
	0.5, 0.5, 0.5
};
// ������� ����� �����
const float VertexData::face_left[12]
{
	-0.5, -0.5, -0.5,
	-0.5, 0.5, -0.5,
	-0.5, 0.5, 0.5,
	-0.5, -0.5, 0.5
};
// ������� �������� �����
const float VertexData::face_front[12]
{
	-0.5, 0.5, -0.5,
	0.5, 0.5, -0.5,
	0.5, 0.5, 0.5,
	-0.5, 0.5, 0.5
};
// ������� ������ �����
const float VertexData::face_back[12]
{
	0.5, -0.5, -0.5,
	-0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5,
	0.5, -0.5, 0.5
};
// ������� ������������ �����
const float VertexData::face_crossRFLB[24]
{
	0.5, 0.5, -0.5,
	-0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5,
	0.5, 0.5, 0.5,
	-0.5, -0.5, -0.5,
	.5, 0.5, -0.5,
	0.5, 0.5, 0.5,
	-0.5, -0.5, 0.5
};
// ������� ������������ �����
const float VertexData::face_crossRBLF[24]
{
	0.5, -0.5, -0.5,
	-0.5, 0.5, -0.5,
	-0.5, 0.5, 0.5,
	0.5, -0.5, 0.5,
	-0.5, 0.5, -0.5,
	0.5, -0.5, -0.5,
	0.5, -0.5, 0.5,
	-0.5, 0.5, 0.5
};