#include<iostream>
#include <GL/glut.h>
#include "CMI.h"
#include<Windows.h>
#include<string>
#include <iterator>

using namespace std;

int winW = 400;
int winH = 400;
vector v[50] = {NULL};//, winW / 2, winH / 2, winW / 2, winH / 2 };
vector interV[11];
int i=0;//tuple index
int mouseClickCount = 0;

void disp();
void myMouse(int button, int state, int x, int y);
void reshape(int w, int h);

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(winW, winH);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Catmull room spline");
	
	glutDisplayFunc(disp);
	glutMouseFunc(myMouse);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 1;
}

void disp(void) 
{
	glClearColor(0.6, 0.9, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	glLineWidth(1);
	glPointSize(10.0);

	for (int i = 0; i < mouseClickCount; i++)
	{
		GLdouble innerX, innerY;
		int j = 0;
		float t = 0.0;
		while ( t <= 1.1)
		{
			interV[j].x = v[i-1].x*(-0.5 * t + pow(t, 2) - 0.5*pow(t, 3)) + v[i].x*(1 - 2.5*pow(t, 2) + 1.5*pow(t, 3)) + v[i + 1].x*(0.5*t + 2 * pow(t, 2) - 1.5*pow(t, 3)) + v[i + 2].x*(-0.5*pow(t, 2) + 0.5*pow(t, 3));
			interV[j].y = v[i-1].y*(-0.5 * t + pow(t, 2) - 0.5*pow(t, 3)) + v[i].y*(1 - 2.5*pow(t, 2) + 1.5*pow(t, 3)) + v[i + 1].y*(0.5*t + 2 * pow(t, 2) - 1.5*pow(t, 3)) + v[i + 2].y*(-0.5*pow(t, 2) + 0.5*pow(t, 3));
			j++;
			t += 0.1;
		}


		
 		glBegin(GL_POINTS);
		glVertex2f(v[i].x, v[i].y);
		glEnd();

		glBegin(GL_POINTS);
		glVertex2f(v[mouseClickCount].x, v[mouseClickCount].y);
		glEnd();
		
		glBegin(GL_LINE_STRIP);
		for (int t = 0; t <= 10; t++)
		{
			glVertex2f(interV[t].x, interV[t].y);
		}
		glEnd();
		
	}


glFlush();
}

void myMouse(int button,int state,int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			
			v[i].x = x;
			v[i].y = winH - y;
			
			i++;
			glutPostRedisplay();
			break;
		}
		mouseClickCount++;
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)w, 0, (GLdouble)h);
}