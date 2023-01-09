#pragma once
#include"Vector3.h"
#include<iostream>
#include<fstream>
#include<GLFW/glfw3.h>
using namespace std;
using std::string;
/// <summary>
/// ����� �������
/// </summary>
class Debug
{
public:
	static bool active; // ����������
	static bool bounds; // �����
	static ofstream log; // ����� ������
	string file_name = "log.txt"; // ��� �����
	static void Log(string text); // ����� ������
	static void DrawBox(Vector3 pos, Vector3 dim, Vector3 color); // ��������� �����
	Debug(); // �����������
	~Debug(); // ����������
};

