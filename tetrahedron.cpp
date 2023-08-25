#ifdef _APPLE_CC__
#else
#include "glut.h"
//#include <GL/glut.h>
#endif

const int width = 800;
const int height = 600;
const int xPosition = 80;
const int yPosition = 80;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
		glVertex3f(i, 0, 2.5);
		glVertex3f(i, 0, -2.5);
		glVertex3f(2.5, 0, i);
		glVertex3f(-2.5, 0, i);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

	glColor3f(1, 1, 1);
	glColor3f(1, 0, 0);
	glColor3f(0, 1, 0);
	glColor3f(0, 0, 1);
	glColor3f(1, 1, 1);
	glColor3f(1, 0, 0);

	glColor3f(0, 2, 0);
	glColor3f(-1, 0, 1);
	glColor3f(1, 0, 1);
	glColor3f(0, 0, -1.4);
	glColor3f(0, 2, 0);
	glColor3f(-1, 0, 1);
	glEnd();

	glFlush();

}
void init() {
	glClearColor(0.1, 0.39, 0.88, 1.0);
	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2, 2, -1.5, 1.5, 1, 40);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -3);
	glRotatef(50, 1, 0, 0);
	glRotatef(70, 0, 1, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(xPosition, yPosition);
	glutInitWindowSize(width, height);
	glutCreateWindow("A Simple Tetrahedron");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}