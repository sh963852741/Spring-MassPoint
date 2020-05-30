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
	test.MakeTestSurface();
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