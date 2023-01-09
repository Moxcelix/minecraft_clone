#include "Ray.h"
/// <summary>
/// ����������� ����
/// </summary>
/// <param name=""></param>
/// <param name="length"></param>
/// <param name="delpos"></param>
/// <param name="addpos"></param>
/// <returns>��������� ���� �� ����</returns>
bool Ray::Trace(float far, float& length, Vector3& delpos, Vector3& addpos)
{
	float half = 0.5f; // ��������
	for (float t = 0; t <= far; t += eps)
	{
		delpos = start + direction * t;
		length = (delpos - start).Module();

		if (delpos.x > 0) delpos.x += 0.5f;
		if (delpos.x < 0) delpos.x -= 0.5f;
		if (delpos.y > 0) delpos.y += 0.5f;
		if (delpos.y < 0) delpos.y -= 0.5f;
		if (delpos.z > 0) delpos.z += 0.5f;
		if (delpos.z < 0) delpos.z -= 0.5f;
		// ��� ������������ � ������ ������������� ���
		if (world->GetBlockID(delpos.x, delpos.y, delpos.z)) 
		{
			Vector3 pos = delpos - direction * eps;
			addpos = Vector3(pos.x, pos.y, pos.z);
			return true;
		}
	}
	return false;
}