#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

/*
#include "stdafx.h"
#include "glm.h"
#include "Texture.h"
*/

void initialize()
{
	glClearColor(0.8,0.8,0.8,0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

void graficarEjes()
{
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(50,0,0);
		
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,50,0);
		
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,50);
	glEnd();
}
// coordenadas para la visión
double viewX = 35;
double viewY = 35;
double viewZ = 35;

// coordenadas x, y e z para el movimiento de la caja "box"
double boxXmovement = 0;
double boxYmovement = 0;
double boxZmovement = 0;

// controles
void controls(unsigned char key, int x, int y){
	switch (key)
	{
	case 'r':
		// FIXME: mover caja a su origen
		boxXmovement = 0;
		boxYmovement = 0;
		boxZmovement = 0;

		// Cámara
		viewX = 35;
		viewY = 35;
		viewZ = 35;
		break;
	
	case 'w':
		boxYmovement += 0.05;
		break;
	
	case 's':
		boxYmovement -= 0.05;
		break;

	case 'd':
		boxXmovement += 0.05;
		break;

	case 'a':
		boxXmovement -= 0.05;
		break;

	case 'q':
		boxZmovement += 0.05;
		break;

	case 'e':
		boxZmovement -= 0.05;
		break;

	case 'i':
		viewY += 1;
		break;
	
	case 'k':
		viewY -= 1;
		break;

	case 'l':
		viewX += 1;
		break;

	case 'j':
		viewX -= 1;
		break;

	case 'o':
		viewZ += 1;
		break;

	case 'u':
		viewZ -= 1;
		break;
	}
	// Negar movimiento en X de la caja
	// FIXME: encontrar una mejor forma de hacer esto
	if (boxZmovement >= 3.5){
		boxZmovement -= 0.05;
	}
	if (boxZmovement <= -3.5){
		boxZmovement += 0.05;
	}
	
	
}

void drawArea(){
	glColor3f(0.5,0.35,0.75);
	glBegin(GL_LINES);
		glVertex3f(-500,0,-5);
		glVertex3f(500,0,-5);

		glVertex3f(-500,0,5);
		glVertex3f(500,0,5);
	glEnd();
}
void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewX,viewY,viewZ, 0,0,0, 0,1,0);
	graficarEjes();
	glPushMatrix();
		drawArea();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(boxXmovement,boxYmovement,boxZmovement);
		glutWireCube(3);
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();

}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float) w / (float) h, 1, 100);
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(100,200);
	glutCreateWindow("honk");
	initialize();
	glutDisplayFunc(render);
	glutKeyboardFunc(controls);
	glutReshapeFunc(resize);
	//glutIdleFunc(animate);
	glutMainLoop();
	return 0;
}