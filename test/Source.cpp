#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
//����������� ��������� � ������������ ������
#include <GLFW/glfw3.h>
#include <format>
#include <iostream>
#include <filesystem>
#include <string>
#include <thread>
#include <string_view>
#include <cmath>
#include <direct.h>
#include <stb_image.h>
#include "Client.h"
#include "Debug.h"
#include "DeltaTime.h"
#include <windows.h>
#include <experimental/filesystem>

using namespace std;

void Resize(int x, int y);	// ��������� ����������� ��� ������ ����
void Resize();				// ��������� ����������� ��� ������ ����

const int SIZE_X = 1280;	// �������������� ������ ���� � ��������
const int SIZE_Y = 720;		// �������������� ������ ���� � ��������
GLFWwindow* window;			// ��������� �� �������� ����

DeltaTime delta_time;		// ��������� ������ �������
float d_time;				// ������ �������
bool wireframe = false;		// ����� ��������� ����������
double fps;					// ���������� ������ � �������
int lfps = 0, ms = 1;		// ����������� ���������� ������ � �������

Vector3 sky_color;	// ���� ����
Client client;		// ��������� �������

/// <summary>
/// ���������� ������� ������ ���� (����������� �����, ������������ �������������� GLFW)
/// </summary>
/// <param name="window"></param>
/// <param name="button"></param>
/// <param name="action"></param>
/// <param name="mods"></param>
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) // �������� �������
	{
		if (button == client.key_config.destroy) // ���
			client.modifier->Destroy(); // ��������� ��������� ��� ���
		if (button == client.key_config.place) // ���
			client.modifier->Place(); // ��������� ��������� ��� ���
		if (button == client.key_config.copy) // ���
			client.CopyBlock();	// ����������� �����
	}
	if (action == GLFW_RELEASE) // �� ������� 
	{
		if (button == client.key_config.destroy) // ���
			client.modifier->Destroy(false); // ��������� ��������� ��� ���
		if (button == client.key_config.place) // ���
			client.modifier->Place(false); // ��������� ��������� ��� ���
	}
}
/// <summary>
/// ���������� ������� ������ ���� (����������� �����, ������������ �������������� GLFW)
/// </summary>
/// <param name="window"></param>
/// <param name="xoffset"></param>
/// <param name="yoffset"></param>
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset > 0) // ������ ���� �����
		client.ButtonUp();

	if (yoffset < 0) // ������ ���� ����
		client.ButtonDown();
}
/// <summary>
/// ���������� ������� ���������� (����������� �����, ������������ �������������� GLFW)
/// </summary>
/// <param name="window"></param>
/// <param name="key"></param>
/// <param name="scancode"></param>
/// <param name="action"></param>
/// <param name="mods"></param>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) // �������� �������
	{
		if (key == client.key_config.explode) {
			if (client.world->GetBlockID(client.player.look_pos) == Block::tnt->id)
				client.world->Explode(client.player.look_pos);
		}
		else if (key == client.key_config.left)
			client.player.left.Move(client.player.can_move);
		else if (key == client.key_config.right)
			client.player.right.Move(client.player.can_move);
		else if (key == client.key_config.forward)
			client.player.forward.Move(client.player.can_move);
		else if (key == client.key_config.back)
			client.player.back.Move(client.player.can_move);
		else if (key == client.key_config.shift)
			client.player.down.Move(client.player.can_move);
		else if (key == client.key_config.jump)
			client.player.up.Move(client.player.can_move);
		else if (key == client.key_config.sprint)
			client.player.sprint = true;
		else if (key == client.key_config.fly)
		{
			if (client.player.can_move)
				client.player.fly = !client.player.fly; // ���/���� ����
		}
		else if (key == client.key_config.up)
			client.ButtonUp(); // �������� � ���������������� ���������� �����
		else if (key == client.key_config.down)
			client.ButtonDown(); // �������� � ���������������� ���������� ����
		else if (key == client.key_config.enter)
			client.enter = true;  // ������������� � ���������������� ����������
		else if (key == client.key_config.pause)
			client.Pause(!client.pause); // ���/���� ����
		else if(key == GLFW_KEY_F3)
			wireframe = !wireframe; // ���/���� ����� ����
		else if(key == GLFW_KEY_F4)
			Debug::bounds = !Debug::bounds; // ���/���� ����� ��������� ������ ������
	}
	else if (action == GLFW_RELEASE) // ������� �������
	{
		if (key == client.key_config.left)
			client.player.left.Move(false);
		else if (key == client.key_config.right)
			client.player.right.Move(false);
		else if (key == client.key_config.forward)
			client.player.forward.Move(false);
		else if (key == client.key_config.back)
			client.player.back.Move(false);
		else if (key == client.key_config.shift)
			client.player.down.Move(false);
		else if (key == client.key_config.jump)
			client.player.up.Move(false);
		else if (key == client.key_config.sprint)
			client.player.sprint = false;
	}
}
/// <summary>
/// ������������� ������� (����������� �����, ������������ �������������� STB Image)
/// </summary>
/// <param name="texture"></param>
/// <param name="name"></param>
void TextureInit(unsigned int& texture, const char* name)
{
	int width, height, cnt; // ��������� �����������
	unsigned char* data = stbi_load(name, &width, &height, &cnt, 0); //�������� ��������
	glGenTextures(1, &texture); // ������ �� ��������
	glBindTexture(GL_TEXTURE_2D, texture); // ���� ��������������� 
	// ��������� �������� (����������� ����� �������� ��������)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);	// ������� ���� ��������������� 
	stbi_image_free(data);				// ������������ ������
}
/// <summary>
/// ������������� ����
/// </summary>
void GameInit()
{
	client.Init(); // ������������� �������

	TextureInit(client.main_texture, "terrain.png");		// ������������� �������
	TextureInit(client.ui.font, "myfont.png");				// ������������� ������
	TextureInit(client.Menu.font, "myfont.png");			// ������������� ������
	TextureInit(client.inventory.ui.font, "myfont.png");	// ������������� ������

	glEnable(GL_ALPHA_TEST);		// ��������� ��������� �����-������
	glAlphaFunc(GL_GREATER, 0.5);	// ��������� ������� Cut-off
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ������ ������

	glEnable(GL_FOG);                       // ��������� ������ 
	glFogi(GL_FOG_MODE, GL_LINEAR);			// ����� ���� ������
	glHint(GL_FOG_HINT, GL_DONT_CARE);      // ��������������� ��������� ������
}
/// <summary>
/// ��������� �����
/// </summary>
void Render()
{
	int distance = World::render_distance * Chunk::ChunkSize; // ������������ ����������

	Resize(); //������������� ����������� ��� ������ ����

	glEnable(GL_DEPTH_TEST);				// ��������� ������� ���������
	glFogf(GL_FOG_START, distance * 0.5);	// �������, � ������� ���������� �����
	glFogf(GL_FOG_END, distance);			// �������, ��� ����� �������������
	glFogf(GL_FOG_DENSITY, M_E/distance);   // ��������� ������ ����� �����

	if (World::is_day) // ������������ ����� ���� � ����������� �� ������� �����
		sky_color = Vector3(0.6, 0.8, 1);	// ����
	else
		sky_color = Vector3(0, 0, 0.1);		// ����

	glClearDepth(2);
	glClearColor(sky_color.x, sky_color.y, sky_color.z, 1); // ���� ���� (����)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ����� ������� 
	glEnable(GL_TEXTURE_2D); // ������������� 2D �������

	float fog_color[4] = { sky_color.x, sky_color.y, sky_color.z, 1 }; // ���� ����
	glFogfv(GL_FOG_COLOR, fog_color);				// ������������� ���� ������
	client.CameraUpdate();							// ���������� ������
	glEnable(GL_CULL_FACE);							// ������� ������������ ���
	glCullFace(GL_FRONT);							// ���������� ��������� ���������� ������
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	// ��������� ����������� �������
	glEnableClientState(GL_VERTEX_ARRAY);			// ��������� ������� ������
	glEnableClientState(GL_COLOR_ARRAY);			// ��������� ������� ������

	client.Render(); // ����� ������ ���������� � �������

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	// ����� �� ��������� ��������� �������
	glDisableClientState(GL_VERTEX_ARRAY);			// ���������� ��������� ������� ������
	glDisableClientState(GL_COLOR_ARRAY);			// ���������� ��������� ������� ������
	glDisable(GL_DEPTH_TEST);						// ���������� ������� ���������
}
/// <summary>
/// ������������� ����������� ��� �������� ������ ����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Resize(int x, int y)
{
	glViewport(0, 0, x, y); // ����� ������

	float k = x / (float)y;	// ��������� ������
	float sz = 0.01f;		// ����������� ���� ������

	glLoadIdentity();		// ������ ������� �� ������� �� ���������
	glFrustum(-k * sz, k * sz, -sz, sz, 0.01, 100); // �����������
}
/// <summary>
/// ������������� ����������� ��� ������ ����
/// </summary>
void Resize()
{
	int width, height; // ������ � ������ ����
	glfwGetWindowSize(window, &width, &height); // ��������� ��������

	glViewport(0, 0, width, height); // ������������� ����� ������ �� ���������� �������� ����

	float k = width / (float)height; // ����������� ��������� ������ � ������
	float sz = 0.015; // ����������� ���� ������

	glLoadIdentity(); // ������ ������� �� ������� �� ���������
	glFrustum(-k * sz, k * sz, -sz, sz, 0.01, 100); // ��������� �����������
}
///<summary>
///������ ������� ��������� ����� ��� ���������� ������	� ���������� ������ � �������
///</summary>
void CalculateFPS() 
{
	d_time = delta_time.Get();		// ��������� �������� ������ �������
	fps = (1.0 / d_time) * 1000;	// ���-�� ������ � �������

	static int counter = 0;		// ������� �����
	counter++;					// �������������

	if (counter > 30)		// ���� ����� ������ ������
	{
		lfps = (int)fps;	// ��������� ������������ �������� FPS
		ms = (int)d_time;	// ��������� ������������ �������� �����������
		counter = 0;		// ��������� ��������
	}
}
/// <summary>
/// ���������� ���������
/// </summary>
void Update()
{
	client.Update(d_time);				// ���������� �������
	client.world->chunksUpdateing = 0;	// ����� ���-�� ������������� ������
}
/// <summary>
/// ��������� ����������������� ����������
/// </summary>
void RenderUI()
{
	// ����� ������ �������
	client.ui.PrintDebug("FPS: " + to_string(lfps) + " (" + to_string(ms) + " ms)", 1, 0, 0);
	client.ui.PrintDebug("�������: " + to_string((int)client.player.pos.x) + " " +
		std::to_string((int)client.player.pos.y) + " " + to_string((int)client.player.pos.z), 1, 1, 1);
	client.ui.PrintDebug("����������� ������: " + to_string(client.world->chunksUpdateing), 1, 1, 1);
	client.ui.PrintDebug("������ � ������: " + to_string(client.world->GlobalBuffer.size()), 1, 1, 1);
	client.ui.PrintDebug("����� ���������: " + to_string(World::seed), 1, 1, 1);
	client.ui.PrintDebug("���������� ������ " + to_string(client.particles.size()), 1, 1, 1);
	client.ui.PrintDebug("������� �������: " + World::name, 1, 1, 1);
	client.ui.PrintDebug("ID �����: " + to_string(client.world->GetBlockID(client.player.look_pos)), 1, 1, 1);
	client.ui.PrintDebug("[Esc] - �����", 0, 1, 1);
	
	client.RenderUI();
}
/// <summary>
/// ����� �����
/// </summary>
/// <returns></returns>
int main()
{
	Debug debug;					// �������� ������ ��������� ��� ������� 
	setlocale(LC_ALL, "Russian");	// ������� ���� � �������

	debug.active = false;

	while (true) 
	{
		cout << "������� ��� �������� �������� -> ";
		cin >> World::name;

		if (_mkdir("saves"))
			Debug::Log("directory \"saves\" already exists");
		if (_mkdir("saves/worlds"))
			Debug::Log("directory \"worlds\" already exists");
		if (_mkdir((save_folder + World::name + "/").c_str()))
			Debug::Log("directory \"" + World::name + "\" already exists");

		if (!glfwInit()) // ���� ������������� �� �������
			return -1;

		// �������� ���� GLFW
		window = glfwCreateWindow(SIZE_X, SIZE_Y, "Multiverse", NULL, NULL);
		client.window = window;

		if (!window) // ���� ���� �� ���������
		{
			glfwTerminate(); // ���������� GLFW
		}

		glfwMakeContextCurrent(window);  //	��������� ��������� ���� ������� ��� ����������� ������
		glfwSetKeyCallback(window, key_callback); // ��������� ������� ������
		glfwSetMouseButtonCallback(window, mouse_button_callback); // ������� ������ ����
		glfwSetScrollCallback(window, scroll_callback); // ������� ������ ����

		GameInit(); // ������������� ����

		// ������� ���� ���������, �������������� ��� ������� �����
		while (!glfwWindowShouldClose(window) && !client.close)
		{
			glPushMatrix(); // ������ ������ ����� �������
				// ����� ����� ��� �������
			glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);

			Update(); // ���������� ���������
			Render(); // ���������

			glPopMatrix();	// ����� ������ �������

			RenderUI();		// ��������� ����������������� ����������

			glfwSwapBuffers(window);	// ����� ������� ���������� 
			glfwPollEvents();			// �������� ����� �������  

			CalculateFPS();				// ������� ���-�� ������ � �������
		}

		client.Clear();	// ������� �������

		system("cls"); // ������� �������

		glfwTerminate(); //���������� ������
	}

	return 0;
}