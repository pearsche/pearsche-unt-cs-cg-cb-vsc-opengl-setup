

#include "stdafx.h"
#include <stdlib.h>
// #include <windows.h>
#include <GL/glut.h>
#include "glm.h"
#include "Texture.h"

static float ypoz = 0, zpoz = 0;

GLMmodel* punteroM1 = NULL;
GLMmodel* punteroM2 = NULL;

GLuint	texture;
Texture	treeTextureAr[3];

bool LoadTreeTextures()
{
	int i;
	if (LoadTGA(&treeTextureAr[0], "modelos/bot/Game_character_Albedo.tga") && LoadTGA(&treeTextureAr[1], "modelos/or/Hair00_05.tga")) //&& LoadTGA(&treeTextureAr[1], "modelos/TEXTURA.tga"))
	{
		for (i = 0; i<2; i++){
			glGenTextures(1, &treeTextureAr[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeTextureAr[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeTextureAr[i].bpp / 8, treeTextureAr[i].width, treeTextureAr[i].height, 0, treeTextureAr[i].type, GL_UNSIGNED_BYTE, treeTextureAr[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeTextureAr[i].imageData)
			{
				free(treeTextureAr[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}



void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	LoadTreeTextures();
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}



void graficar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0, 1.5, 2.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);



	glRotatef(ypoz, 0, 1, 0);




	glTranslatef(0,-1,0);

	glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
	glmDraw(punteroM1, GLM_SMOOTH | GLM_TEXTURE);



	glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
	glmDraw(punteroM2, GLM_SMOOTH | GLM_TEXTURE);


	glutSwapBuffers();


}

void redimensionar(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
}


void animate(int i)
{
	ypoz += 0.5;
	if (ypoz>360) ypoz = 0;
	glutPostRedisplay();
	glutTimerFunc(2, animate, 1);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("JLPeralta");
	init();


	///punteroM1 = glmReadOBJ("modelos/or/orcmale.obj");
	punteroM1 = glmReadOBJ("modelos/bot/Bot.obj");
	punteroM2 = glmReadOBJ("modelos/or/pelo.obj");



	glutDisplayFunc(graficar);
	glutReshapeFunc(redimensionar);
	glutTimerFunc(2, animate, 1);
	glutMainLoop();
	return 0;
}



