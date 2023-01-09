#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include"Settings.h"
#include"World.h"
#include"Chunk.h"
#include"RigidBox.h"
#include"DeltaTime.h"

#include<vector>
#include<fstream>

using namespace std;
class World;
class RigidBox;
/// <summary>
/// ����� ������
/// </summary>
class Player
{
private:
	int length;

	float walk_speed = 0.005f;
	float run_speed = 0.01;
	float lift_speed = 0.01;
	float fly_mult = 1.5f;
public:
	/// <summary>
	/// ��������� ������
	/// </summary>
	struct Camera
	{
		float x, y, z;		// ����������
		float xRot, zRot;	// ���� ��������
	} camera = { 0, 0, head_height, 0, 0 }; // ���������

	/// <summary>
	/// ��������� ��������
	/// </summary>
	struct MovementDirection
	{
	private:
		bool move = false;
		float velocity = 0;
		float mult = 100;
	public:
		/// <summary>
		/// ����� ���������
		/// </summary>
		/// <param name="state"></param>
		void Move(bool state = true)
		{
			move = state;
		}
		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="a"></param>
		/// <param name="max_speed"></param>
		void Move(float a, float max_speed)
		{
			if (move)
				velocity += a;
			else
				velocity -= a * velocity * mult;

			if (velocity < 0)
				velocity = 0;

			if (velocity > max_speed)
				velocity = max_speed;
		}
		/// <summary>
		/// ������ ���������
		/// </summary>
		/// <returns></returns>
		bool GetMove() 
		{
			return move;
		}
		/// <summary>
		/// ������ ��������
		/// </summary>
		/// <returns></returns>
		float GetVelocity()
		{
			return velocity;
		}
	};

	Player(World* world);	// �����������
	Player();				// �����������

	RigidBox* body;			// ���������� ���� ���������
	DeltaTime delta_time;	// ����� ������ �������

	Vector3 look_pos;	// �������, ���� ������� �����
	Vector3 add_pos;	// �������, ���� ����� ���������� ����
	Vector3 pos;		// ������� ������

	MovementDirection forward;		// �������� �����	
	MovementDirection back;			// �������� �����
	MovementDirection right;		// �������� ������
	MovementDirection left;			// �������� �����
	MovementDirection up;			// �������� �����
	MovementDirection down;			// �������� ����

	bool looking = false;			// ���� ����������� �� ����
	bool sprint = false;			// ���� ����
	bool fly = false;				// ���� �����
	bool can_move = true;			// ���� ��������

	float rot, velocity, speed;
	
	float phasa = 0; // ���� ����������� ������
	float head_height = 1.7;
	float HeadBobMagnitude = 0.1;	// ������ � �������� ����������� ������
	float width = 0.8f;				// ������ ���������
	float height = 1.8f;			// ������ ���������
	float jump_speed = 0.015f;		// ��������� ������
	float current_friction = 1;		// ����������� ������
	float acceleration = 0.0001;	// ��������� ������

	double angle = 0; // ����

	void RotateCamera(float alpha, float beta); // ������� ������
	void MoveUpdate();	// ���������� ��������
	void Update(); // ����������
	void LoadTerrain(World* world); // ��������� ����������
	void GenereateSphere(); // ��������� ����� ���������
	void Save(ofstream& stream); // ���������� ���������� ������
	void Init(float x, float y, float z, float xRot, float zRot); // �������������

	float GetVelocity(); // ��������� ��������
	float GetDistance(float x, float y, float z); // ���������� �� �����

	Vector3 start_pos = { 0, 0, 64 };	// ��������� �������
	vector<Vector3Int*>sphere;			// ������ ��������� ����� ���������
	Vector3Int IntPosition;				// ������ ��������� � ����� �����������
	Vector3Int ChunkPosition;			// ������ �������� �������
	World* world;						// ��������� �� ��������� ����
	Vector2 vel = Vector2(0, 0);		// ������ �������������� ��������
};

