#define _USE_MATH_DEFINES
#include "Player.h"
#include <cmath>

/// <summary>
/// ����������� ���������
/// </summary>
Player::Player()
{

}
/// <summary>
/// ����������� ���������
/// </summary>
Player::Player(World* world)
{
	this->world = world;
}
/// <summary>
/// ��������� ����� ���������
/// </summary>
void Player::GenereateSphere()
{
	sphere.clear(); // ������� ���������� ��������
	int render_distance = World::render_distance - 1; // ��������� ����������

	for (int i = -render_distance; i <= render_distance; i++)
		for (int j = -render_distance; j <= render_distance; j++)
			for (int k = -render_distance; k <= render_distance; k++)
			{
				if (i * i + j * j + k * k < render_distance * render_distance) // ���� ����� ������ �����
				{
					sphere.push_back(new Vector3Int(i, j, k)); // ��������� ���������� � ������
				}
			}
	for (int i = 0; i < sphere.size(); i++) // ���������� ��������� ����� �� ������������ �� ������
		for (int j = 0; j < sphere.size() - 1; j++)
			if (*sphere[j] > *sphere[j + 1])
				swap(sphere[j], sphere[j + 1]);

	length = sphere.size();
}
/// <summary>
/// �������� ���������� 
/// </summary>
/// <param name="world"></param>
void Player::LoadTerrain(World* world)
{
	if (world->chunksLoaded < World::MaxChunksCount - 1) // ���� ���������� ����������� ������ ������ ������������� 
		for (Vector3Int* i : sphere) // ��������� ������� �����
		{
			// ������� ��������� � �������� ������
			int x = this->pos.x + i->x * Chunk::ChunkSize;
			int y = this->pos.y + i->y * Chunk::ChunkSize;
			int z = this->pos.z + i->z * Chunk::ChunkSize;

			world->AddToCreate(x, y, z); // ���������� ��������� � ������� �������� ������ 
		}
}
/// <summary>
/// ��������� ���������� �� ������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns></returns>
float Player::GetDistance(float x, float y, float z)
{
	x -= this->pos.x;
	y -= this->pos.y;
	z -= this->pos.z;

	return sqrtf(x * x + y * y + z * z);
}
/// <summary>
/// ���������� ��������
/// </summary>
void Player::MoveUpdate()
{
	float time = delta_time.Get();

	speed = (sprint ? run_speed: walk_speed) * (fly ? fly_mult : 1); // ��������

	float mult = 100 * time; // ���. ���������

	forward.Move(acceleration * time, speed);
	back.Move(acceleration * time, speed);
	right.Move(acceleration * time, speed);
	left.Move(acceleration * time, speed);
	up.Move(acceleration * time, speed);
	down.Move(acceleration * time, speed);

	float _forward = forward.GetVelocity();
	float _back = back.GetVelocity();
	float _right = right.GetVelocity();
	float _left = left.GetVelocity();
	float _up = up.GetVelocity();
	float _down = down.GetVelocity();

	// ������ ������� ��������������� ��������
	Vector2 xvel = Vector2((_right - _left) * sin(rot + M_PI_2), (_right - _left) * cos(rot + M_PI_2));
	Vector2 yvel = Vector2((_forward - _back) * sin(rot), (_forward - _back) * cos(rot));
	Vector2 direction = xvel + yvel;

	float module = direction.Module();

	if (module > speed) // ������������ ������� ��������
		direction = direction * (speed / module);

	phasa += direction.Module() * time; // ������ ����

	velocity = Vector3(direction.x, direction.y, _up - _down).Module(); // ������ ������ ��������
	// ���������� ���������
	static float dx = direction.x * time;
	static float dy = direction.y * time;
	static float dz = 0;

	static float hv = 0;

	dx = direction.x * time;
	dy = direction.y * time;

	if (fly)
	{
		hv = 0;
		dz = (_up - _down) * time;
	}
	else
	{
		dz = 0;

		if (body->grounded)
			hv = up.GetMove() ? jump_speed : 0;
		else
			hv -= body->g * time;
	}

	if (body->pos.z < -10)
		body->pos.z = 128;

	body->Move(dx, dy, dz + hv * time);
	pos = body->pos;
}
/// <summary>
/// ��������� ��������
/// </summary>
/// <returns></returns>
float Player::GetVelocity()
{
	return velocity;
}
/// <summary>
/// ���������� 
/// </summary>
void Player::Update()
{
	// ������������� ���������� ������ 
	IntPosition.x = pos.x;
	IntPosition.y = pos.y;
	IntPosition.z = pos.z;

	// ������ ������� � �������� ������
	int X = pos.x, Y = pos.y, Z = pos.z;

	if (X < 0)
		X -= Chunk::ChunkSize - 1;
	if (Y < 0)
		Y -= Chunk::ChunkSize - 1;
	if (Z < 0)
		Z -= Chunk::ChunkSize - 1;

	X = (X / Chunk::ChunkSize) * Chunk::ChunkSize;
	Y = (Y / Chunk::ChunkSize) * Chunk::ChunkSize;
	Z = (Z / Chunk::ChunkSize) * Chunk::ChunkSize;

	ChunkPosition.x = X;
	ChunkPosition.y = Y;
	ChunkPosition.z = Z;
}
/// <summary>
/// ������� ������
/// </summary>
/// <param name="alpha"></param>
/// <param name="beta"></param>
void Player::RotateCamera(float alpha, float beta)
{
	camera.zRot += beta;

	if (camera.zRot < 0)
		camera.zRot += 360;
	if (camera.zRot > 360)
		camera.zRot -= 360;

	camera.xRot += alpha;

	if (camera.xRot < 0)
		camera.xRot = 0;
	if (camera.xRot > 180)
		camera.xRot = 180;
}
/// <summary>
/// �������������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="xRot"></param>
/// <param name="zRot"></param>
void Player::Init(float x, float y, float z, float xRot, float zRot)
{
	// ����������
	this->pos.x = x;
	this->pos.y = y;
	this->pos.z = z;
	// ���� �������� ������
	camera.xRot = xRot;
	camera.zRot = zRot;
	// ����� �����
	int flags = RB_CHECK_LOAD_STATE | RB_SPLIT_HEIGHT | RB_USE_COLLISION | RB_COLLISION_MAP;
	body = new RigidBox(world, width, height, 9.8f * 0.05f, {x,y,z}, flags);

	GenereateSphere(); // �������� ����� ��������� ����������
}
/// <summary>
/// ����������
/// </summary>
/// <param name="stream"></param>
void Player::Save(ofstream& stream)
{
	// ������ � ����� ������
	stream << pos.x << endl;
	stream << pos.y << endl;
	stream << pos.z << endl;
	stream << camera.xRot << endl;
	stream << camera.zRot << endl;
}