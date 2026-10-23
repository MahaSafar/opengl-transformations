//
//  main.cpp
//  CG-Lab#4
//
//  Created by Omniah H. Nagoor on 25/03/2026.
//  Copyright © 2026 Omniah H. Nagoor. All rights reserved.

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>      // handle the window-managing operations
#else
#include <GL/glew.h>
#include <GL/freeglut.h>    // handle the window-managing operations
#endif
#include <stdlib.h>
#include <iostream>
//#include <conio.h>

using namespace std;

GLint win_width = 500,
win_hight = 500;
GLdouble PI = 3.14159265359;
float transValue = 0.0f;
float scaleValue = 1.0f;


void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}

void MyMainObj()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.9f, 0.6f, 0.2f);
	glVertex2f(0.0f, -0.8f);
	glColor3f(1.0f, 0.8f, 0.4f);
	glVertex2f(0.4f, -0.1f);
	glVertex2f(-0.4f, -0.1f);
	glEnd();
	glColor4f(0.2f, 0.9f, 0.2f, 0.7f);
	drawFilledCircle(0.0f, 0.2f, 0.25f);
	glColor4f(1.0f, 0.1f, 0.6f, 0.7f);
	drawFilledCircle(0.2f, 0.05f, 0.25f);
	glColor4f(0.1f, 0.3f, 0.7f, 0.7f);
	drawFilledCircle(-0.2f, 0.05f, 0.25f);
}




static
void special(int key, int x, int y)
{
	//handle special keys
	switch (key) {
	case GLUT_KEY_HOME:

		break;
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

		break;
	default:
		break;
	}
}


static
void mouse(int button, int state, int x, int y)
{
	// Exercise 4; زر الماوس الأيسر يكبر الحجم
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		scaleValue = 2.0f;
	}
	// Exercise 5: زر الماوس الأيمن يعكس ويكبر
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		scaleValue = -2.0f;
	}
	glutPostRedisplay();
}

static
void motion(int x, int y)
{

}

static void play(void)
{
	glutPostRedisplay();
}

static
void key(unsigned char keyPressed, int x, int y) // key handling
{
	switch (keyPressed) {
	case 't': // Exercise 2: زيادة التحريك
		transValue += 0.1f;
		cout << "New transValue: " << transValue << endl;
		break;
	case 'T': // Exercise 3: تقليل التحريك
		transValue -= 0.1f;
		cout << "New transValue: " << transValue << endl;
		break;
	case 27: exit(0); break; // Exit on ESC
	}
	glutPostRedisplay();
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	// glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Exercise 1
	// Req#1: gluOrtho2D(-0.4, 0.4, -0.4, 0.4);
	// Req#2:gluOrtho2D(-3.0, 3.0, -3.0, 3.0);
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void reshapeFunc(GLint new_width, GLint new_hight)
{
	glViewport(0, 0, new_width, new_hight);
	win_width = new_width;
	win_hight = new_hight;

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// تطبيق التحريك (Exercise 2 & 3) والتكبير (Exercise 4 & 5)
	glPushMatrix();
	glTranslatef(transValue, 0.0f, 0.0f); // يتحرك بناءً على الكيبورد
	glScalef(scaleValue, scaleValue, 1.0f); // يتكبر بناءً على الماوس
	MyMainObj();
	glPopMatrix();

	
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);               		  // Initialize GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   //  Specify the display Mode ñ RGB, RGBA or color 				              //  Index, single or double Buffer
	glutInitWindowSize(500, 500);  		 // Set the window's initial width & height
	glutInitWindowPosition(50, 50); 		 // Position the window's initial top-left corner
	glutCreateWindow("OpenGL Lab#4 - Maha Safar - 446009760");    // Create a window with the given title
	init();

	transValue = 0.0;
	scaleValue = 1.0;

	glutIdleFunc(play);
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeFunc);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);

	glutMainLoop();           		// Enter the infinitely event-processing loop

	return 0;
}


