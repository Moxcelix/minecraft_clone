#include "UVData.h"
float UVData::stface[8] = { 1, 1, 0, 1, 0, 0, 1, 0  }; // UV �����
/// <summary>
/// ���������� ������� �����
/// </summary>
void UVData::AddFace() 
{
	AddUV(stface, 8);
}
/// <summary>
/// ���������� UV
/// </summary>
/// <param name="coords"></param>
/// <param name="length"></param>
void UVData::AddUV(float coords[], int length)
{
	for (int i = 0; i < length; i++) 
	{
		UVs.push_back(coords[i]);
	}
}
/// <summary>
/// �������������� � ������
/// </summary>
/// <returns></returns>
float* UVData::ToArray()
{
	inied = true;

	int size = UVs.size();
	
	result = new float[size];

	for (int i = 0; i < size; i++)
	{
		result[i] = UVs[i];
	}

	return result;
}
/// <summary>
/// ���������� UV
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void UVData::AddUV(float x, float y)
{
	y = 15 - y;
	UVs.push_back(x * xUVSize + xUVSize);
	UVs.push_back(y * yUVSize + yUVSize);
	UVs.push_back(x * xUVSize);
	UVs.push_back(y * yUVSize + yUVSize);
	UVs.push_back(x * xUVSize);
	UVs.push_back(y * yUVSize);
	UVs.push_back(x * xUVSize + xUVSize);
	UVs.push_back(y * yUVSize);
}
/// <summary>
/// ���������� UV
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="dx"></param>
/// <param name="dy"></param>
void UVData::AddUV(float x, float y, float dx, float dy)
{
	y = 15 - y;
	UVs.push_back(x * xUVSize + xUVSize * dx);
	UVs.push_back(y * yUVSize + yUVSize * dy);
	UVs.push_back(x * xUVSize);
	UVs.push_back(y * yUVSize + yUVSize * dy);
	UVs.push_back(x * xUVSize);
	UVs.push_back(y * yUVSize);
	UVs.push_back(x * xUVSize + xUVSize * dx);
	UVs.push_back(y * yUVSize);
}
/// <summary>
/// ������� ����� UV
/// </summary>
void UVData::Clear()
{
	UVs.clear();
}
/// <summary>
/// ����������� 
/// </summary>
UVData::UVData() 
{

}
/// <summary>
/// ����������
/// </summary>
UVData::~UVData()
{
	UVs.clear();

	if(inied)
		delete[] result;
}