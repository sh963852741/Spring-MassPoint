#include "SMSystem.h"
using namespace std;

SMSystem test = SMSystem();
void display()
{
	test.Simulate();
	test.DrawWireframe();
}
void Init()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char* argv[])
{
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			test.AddPoint(MassPoint(Vector3f((float)(j * 0.039 - 0.98), 0.99, -i * 0.04), 0.1));
		}
	}
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 49; ++j)
		{
			test.AddSpring(j + i * 50, j + i * 50 + 1);
		}
	}
	for (int i = 0; i < 49; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			test.AddSpring(j + i * 50 + 50, j + i * 50);
			if (j > 0)test.AddSpring(j + i * 50 + 50 - 1, j + i * 50);
			if (j < 49)test.AddSpring(j + i * 50 + 50 + 1, j + i * 50);
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