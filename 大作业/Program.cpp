#include "SMSystem.h"
#include <fstream>
#include <string>
using namespace std;

SMSystem test = SMSystem();
void display()
{
	test.Simulate();
	//test.DrawWireframe();
	test.DrawCloth();
	test.DrawGraphyics();
	glFlush();
}
void Init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);


	GLfloat light_position[] = { 0, 0, 1.0, 0 };
	GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	
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
/*用于鼠标控制的变量*/
int mouseX = 0, mouseY = 0;
int mouseLeftDown = 0, mouseRightDown = 0, mouseMiddleDown = 0;
/*用于鼠标控制的变量*/
void processMouse(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = 1;
		}
		else if (state == GLUT_UP)
			mouseLeftDown = 0;
	}

	else if (button == GLUT_MIDDLE_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseMiddleDown = 1;
		}
		else if (state == GLUT_UP)
			mouseMiddleDown = 0;
	}
}
void processMove(int x, int y)
{
	if (mouseLeftDown)
	{
		glRotatef((y - mouseY) / 5.0, 1, 0, 0);
		glRotatef((x - mouseX) / 5.0, 0, 1, 0);

	}
	if (mouseMiddleDown)
	{
		glTranslatef((x - mouseX) / 30.0, (mouseY - y) / 30.0, 0);
	}
	mouseX = x;
	mouseY = y;
}
int main(int argc, char* argv[])
{
	//LoadFromFile(test);
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			test.AddPoint(MassPoint(Vector3f((float)(j * 0.04 - 0.5), 0.3, -i * 0.04)));
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
	test.SetPointFixed(19);
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
	glutMouseFunc(processMouse);
	glutMotionFunc(processMove);
	glutMainLoop();
}