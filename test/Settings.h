#pragma once
#include<iostream>
using namespace std;
const int render_chunk_throughput = 4; // ���������� ������ �� ��������� ���������
const int update_chunk_throughput = 4; // ���������� ������ �� ����������
const int create_chunk_throughput = 1; // ���������� ������ �� ��������
const string save_folder = "saves/worlds/"; // ���������� ����������