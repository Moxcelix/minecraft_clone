#include "DeltaTime.h"
/// <summary>
/// ��������� �������� ������ �������
/// </summary>
/// <returns></returns>
float DeltaTime::Get() 
{
	delta_time = clock() - old_time;	// ������� ������ �������
	old_time = clock();					// ������ ������� �������

	return delta_time;					// ������� ��������
}
/// <summary>
/// �����������
/// </summary>
DeltaTime::DeltaTime() 
{
	Get(); // ������� ������� ��������
}