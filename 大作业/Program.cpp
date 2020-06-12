#include "SMSystem.h"
#include <fstream>
#include <string>
using namespace std;

SMSystem test = SMSystem();
void display()
{
	test.Simulate();
	test.DrawWireframe();
	test.DrawGraphyics();
}
void Init()
{
	GLfloat light_position[] = { 0, 1.5, 1.5, 0.0 };
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void LoadFromFile(SMSystem& smsystem, string fileName = "toufa.obj")
{
	ifstream filein(fileName);
	if (!filein.is_open())return;

	string temp;
	while (!filein.eof())
	{
		filein >> temp;
		if (temp == "v")
		{
			//处理顶点
			float vertex_position[3];
			filein >> vertex_position[0] >> vertex_position[1] >> vertex_position[2];
			test.AddPoint(Vector3f(vertex_position));
		}
		else if (temp == "f")
		{
			//处理面片
			int vertex_index[4], count = 0;
			char ch;

			filein.read(&ch, 1);
			filein.seekg(-1, ios::cur);
			while (isdigit(ch))
			{
				filein >> vertex_index[count++] >> temp;
				filein.read(&ch, 1);
				filein.seekg(-1, ios::cur);
			}
		}
	}
}
int main(int argc, char* argv[])
{
	//LoadFromFile(test);
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			test.AddPoint(MassPoint(Vector3f((float)(j * 0.039 - 0.98), 0.99, -i * 0.04), 0.1));
		}
	}
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 19; ++j)
		{
			test.AddSpring(j + i * 20, j + i * 20 + 1);
		}
	}
	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			test.AddSpring(j + i * 20 + 20, j + i * 20);
			if (j > 0)test.AddSpring(j + i * 20 + 20 - 1, j + i * 20);
			if (j < 19)test.AddSpring(j + i * 20 + 20 + 1, j + i * 20);
		}
	}
	test.SetPointFixed(0);
	//test.SetPointFixed(1025);
	test.SetPointFixed(49);
	//test.SetPointFixed(2450);
	//test.MakeTestSurface();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	Init();
	//glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutMainLoop();
}