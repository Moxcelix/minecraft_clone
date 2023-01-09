#pragma once
#define _USE_MATH_DEFINES

#include<iostream>
#include<vector>
#include <cmath>

#include <GLFW/glfw3.h>

#include"VertexData.h"
#include"UVData.h"
#include"World.h"
#include"RigidBox.h"

using namespace std;

/// <summary>
/// ����� �������
/// </summary>
class Particles
{
private:
	float _magnitude = .75f;
public:
	struct Particle
	{
		Vector3 my_pos;		// ������� �������
		Vector3 pos;		// �����
		World* world;		// ��������� �� ���
		Block* block;		// ����
		RigidBox* body;		// ������ ����

		float max_time;		// ����� ����

		float time = 0;					// �����
		float dx = 0, dy = 0, dz = 0;	// ���������� ���������
		float hv = 0;					// ��� ���������� �������
		bool is_dead = false;			// ���� "������"

		float alpha = 0, beta = 0, gamma = 0;	// ���� ��������
		float velocity = 0.007f;				// ��������
		float acceleration = 0.25f;				// ���������

		float size = 0.1f;			// ������
		float g = 9.8f * 0.03f;		// ��������� ���������� �������

		ColorSquad squad;			// ����� ������
		Block::Direction tdir;		// ����������� ��������

		float tx, ty, tdx, tdy;		// ���������� �������

		/// <summary>
		/// �����������
		/// </summary>
		/// <param name="block"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <param name="max_time"></param>
		/// <param name="world"></param>
		/// <param name="pos"></param>
		Particle(Block* block, float x, float y, float z, float max_time, World* world, Vector3 pos)
		{
			body = new RigidBox(world, size, size, g, { x + pos.x, y + pos.y, z + pos.z }, RB_USE_COLLISION);
			// ���������� ���������� ��������� ��������
			dx = x * acceleration;
			dy = y * acceleration;
			dz = z * acceleration;

			this->world = world;
			this->block = block;
			this->pos = pos;
			this->max_time = max_time;
			// ��������� ����� �����
			tdir = Block::Direction((rand() % 3) * 2);
			squad = ColorSquad(block->Color(tdir));

			tx = block->TileCoord(tdir).x;
			ty = block->TileCoord(tdir).y;

			tdx = rand() / (float)RAND_MAX * .75f;
			tdy = rand() / (float)RAND_MAX * .75f;
		}
		
		~Particle() 
		{
			delete body;
		}
		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="deltaTime"></param>
		void Move(double deltaTime)
		{
			time += deltaTime * 0.001f;
			is_dead = time >= max_time;
			// ���������� ���������
			dx -= dx * velocity * deltaTime;
			dy -= dy * velocity * deltaTime;
			dz -= dz * velocity * deltaTime;

			if (body->grounded) // ������� ���������� �������
				hv = 0;
			else
				hv -= body->g * deltaTime;

			body->Move(dx, dy, dz + hv * deltaTime); // ��������

			my_pos = body->pos;	// ���������� �������
		}
		/// <summary>
		/// ������� ���������
		/// </summary>
		/// <param name="vd"></param>
		/// <param name="ud"></param>
		void SetMesh(VertexData* vd, UVData* ud)
		{
			/// ������� ���� �������� �� ������
			float px = world->player->camera.x;
			float py = world->player->camera.y;
			float pz = world->player->camera.z;

			Vector2 a(py - my_pos.y, pz - my_pos.z);
			Vector2 b(px - my_pos.x, pz - my_pos.z);
			Vector2 c(px - my_pos.x, py - my_pos.y);

			alpha = atan2(a.y, a.x);
			beta = atan2(b.y, b.x);
			gamma = atan2(c.y, c.x);

			// ��������� ���������
			float l = world->GetLight(floor(my_pos.x + .5f), floor(my_pos.y + .5f), floor(my_pos.z + .5f));

			if(l == 0)
				l = world->GetLight(floor(pos.x + .5f), floor(pos.y + .5f), floor(pos.z + .5f));

			l = (l / float(Chunk::MaxLight)) * (1 - Chunk::brightness) + Chunk::brightness;

			squad = ColorSquad(block->Color(tdir) * l);

			vd->FaceParticle(0, 0, 0, 0.18f, squad);
			ud->AddUV(tx + tdx, ty - tdy, .25f, .25f);
		}
	};

	bool working = true;

	World* world;					// ��������� �� ���
	VertexData vertexData;			// ������ ������
	UVData uvData;					// ������ UV
	Vector3 pos;					// �������
	vector<Particle*> particles;	// ������ ���������� �� �������

	// �����������
	Particles(Block* block, World* world, Vector3 pos, int count);

	void Clear();						// �������
	void Render(unsigned int texture);	// ������
	void Update(double deltaTime);		// ����������
};

