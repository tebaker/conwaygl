// Describing the progect is a smart first step.
// Letting yourself know what it is you will accomplish by the end of the project.

/* An idea: model a system using machine learning and an OpenGL graphical output */
// OR
/* Creating some very simple user GUI for visually outputting tree diagrams and other 
   things that cracking the coding interview will want you to see.
   Big O, Tree stuff, linked lists and other storage, search and sort algorithms. */


#include <iostream>
#include "Header.h"

// Testing for OpenGL glew inclusion http://ogldev.atspace.co.uk/
#include <glew.h>
#include <glut.h>

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	glVertex2f(10.0, 10.0);
	glVertex2f(150.0, 80.0);
	glVertex2f(100.0, 20.0);
	glVertex2f(200.0, 100.0);
	glEnd();
	glFlush();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Display");
	glutDisplayFunc(display);

	myinit();
	glutMainLoop();
}