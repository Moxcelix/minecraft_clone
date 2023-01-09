#pragma once
#include"World.h"
/// <summary>
/// ����� ����
/// </summary>
class Ray
{
private:
	float eps = 0.01f;	// ��������

	World* world;		// ��������� �� ���
	Vector3 start;		// ������� ������
	Vector3 direction;	// ����������� ����
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="world"></param>
	/// <param name="start"></param>
	/// <param name="direction"></param>
	Ray(World* world, Vector3 start, Vector3 direction) 
	{
		this->world = world;
		this->start = start;
		this->direction = direction;
	}
	bool Trace(float far, float& length, Vector3 &delpos, Vector3 &addpos); // ����������� ����
};

