#pragma once
/// <summary>
/// ��������� �����
/// </summary>
struct Bound
{
	float width; // ������
	float length; // �����
	float height; // ������

	/// <summary>
	/// �����������
	/// </summary>
	Bound() 
	{
		Set(1, 1, 1);
	}
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="width"></param>
	/// <param name="length"></param>
	/// <param name="height"></param>
	Bound(float width, float length, float height)
	{
		Set(width, length, height);
	}
	/// <summary>
	/// ��������� ������
	/// </summary>
	/// <param name="width"></param>
	/// <param name="length"></param>
	/// <param name="height"></param>
	void Set(float width, float length, float height)
	{
		this->width = width;
		this->length = length;
		this->height = height;
	}
};

