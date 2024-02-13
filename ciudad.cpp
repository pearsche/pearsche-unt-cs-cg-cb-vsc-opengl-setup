#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include "stdafx.h"
#include "glm.h"
#include "Texture.h"

using namespace std;

float camX = 15.0f;
float camY = 6.0f;
float camZ = 0.0f;

int temp = 0; //Iniciara con 0(verde), luego ambar y rojo
float rojo[3] = {0.5, 0.5, 0.5};
float ambar[3] = {0.5, 0.5, 0.5};
float verde[3] = {0.5, 0.5, 0.5};

float carroX = 30.0;
float carroY = 0.0;
float carroZ = -1.5;

float carroEX = -225;
float carroEY = 0.0;
float carroEZ = 1.5;

GLUquadric* quad = gluNewQuadric();
GLUquadricObj *p = gluNewQuadric();

static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.

static float ypoz = 0, zpoz = 0;

// modelos 
GLMmodel* punteroM1 = NULL;
GLMmodel* punterosCyborg[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};


GLuint	texture;
Texture	treeTextureAr[3];


bool LoadTreeTextures()
{
	int i;
	if (LoadTGA(&treeTextureAr[0], "modelos/bot/Game_character_Albedo.tga") && LoadTGA(&treeTextureAr[1], "modelos/metal-texture.tga")) //&& LoadTGA(&treeTextureAr[1], "modelos/TEXTURA.tga"))
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

void inicializar(){
	glClearColor(0.2,0.8,1.0,0.0);
	LoadTreeTextures();
    glEnable(GL_DEPTH_TEST);
    gluQuadricDrawStyle(p,GLU_LINE);
    glShadeModel(GL_SMOOTH);
}

void graficarEjes(){
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

void LinDiscon(){
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslated(-20,0.01,0);
        glutSolidTorus(0.1,1.2,50,2);

        glPushMatrix();
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslated(5,0,0);
            glutSolidTorus(0.1,1.2,50,2);

            glPushMatrix();
                glColor3f(1.0f, 1.0f, 1.0f);
                glTranslated(5,0,0);
                glutSolidTorus(0.1,1.2,50,2);

                glPushMatrix();
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glTranslated(5,0,0);
                    glutSolidTorus(0.1,1.2,50,2);

                    glPushMatrix();
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glTranslated(5,0,0);
                        glutSolidTorus(0.1,1.2,50,2);

                        glPushMatrix();
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glTranslated(5,0,0);
                            glutSolidTorus(0.1,1.2,50,2);

                            glPushMatrix();
                                glColor3f(1.0f, 1.0f, 1.0f);
                                glTranslated(5,0,0);
                                glutSolidTorus(0.1,1.2,50,2);
                            glPopMatrix();
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
}

void PasZebra(){
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslated(15,0.01,-2.5);
            glutSolidTorus(0.25,1.2,50,2);

            glPushMatrix();
                glColor3f(1.0f, 1.0f, 1.0f);
                glTranslated(0,0,0.7);
                glutSolidTorus(0.25,1.2,50,2);

                glPushMatrix();
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glTranslated(0,0,0.7);
                    glutSolidTorus(0.25,1.2,50,2);

                    glPushMatrix();
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glTranslated(0,0,0.7);
                        glutSolidTorus(0.25,1.2,50,2);

                        glPushMatrix();
                            glColor3f(1.0f, 1.0f, 1.0f);
                            glTranslated(0,0,0.7);
                            glutSolidTorus(0.25,1.2,50,2);

                            glPushMatrix();
                                glColor3f(1.0f, 1.0f, 1.0f);
                                glTranslated(0,0,0.7);
                                glutSolidTorus(0.25,1.2,50,2);

                                glPushMatrix();
                                    glColor3f(1.0f, 1.0f, 1.0f);
                                    glTranslated(0,0,0.7);
                                    glutSolidTorus(0.25,1.2,50,2);

                                    glPushMatrix();
                                        glColor3f(1.0f, 1.0f, 1.0f);
                                        glTranslated(0,0,0.7);
                                        glutSolidTorus(0.25,1.2,50,2);

                                        glPushMatrix();
                                            glColor3f(1.0f, 0.25f, 1.0f);
                                            glTranslated(1.8,0,-2.5);
                                            glRotated(90,0,1,0);
                                            glutSolidTorus(0.2,2.5,50,2);

                                        glPopMatrix();
                                    glPopMatrix();
                                glPopMatrix();
                            glPopMatrix();
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

}

void pista(){

    glPushMatrix();///PISTA
        glColor3f(0.3f, 0.3f, 0.3f);
        glTranslated(0,0,0);
        glutSolidTorus(3,300,50,2);

        glPushMatrix();///PASO ZEBRA SEMAFORO
            PasZebra();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 1
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 2
            glTranslated(40, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 3
            glTranslated(-35, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///PASO ZEBRA PARE
            glTranslated(-75,0 , 0);
            PasZebra();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 3
            glTranslated(-75, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 7
            glTranslated(-95, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 8
            glTranslated(-110, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///PASO ZEBRA VIA DOBLE
            glTranslated(-150,0 , 0);
            PasZebra();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 9
            glTranslated(-150, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 9
            glTranslated(-180, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 9
            glTranslated(-210, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 10
            glTranslated(-240, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix();///LINEAS DISCONTINUAS 11
            glTranslated(-270, 0, 0);
            LinDiscon();
        glPopMatrix();

        glPushMatrix(); ///VEREDA IZQUIERDA
            glColor3f(0.7f, 0.7f, 0.7f);
            glTranslated(0,0.1,4);
            glutSolidTorus(1,300,50,2);
        glPopMatrix();

        glPushMatrix(); ///VEREDA DERECHA
            glColor3f(0.7f, 0.7f, 0.7f);
            glTranslated(0,0.1,-4);
            glutSolidTorus(1,300,50,2);
        glPopMatrix();

        glPushMatrix(); ///PASTO
            glColor3f(0.4f, 0.9f, 0.4f);
            glTranslated(0,-0.1,0);
            glutSolidTorus(100,300,50,2);
        glPopMatrix();

    glPopMatrix();

}

void semaforo(){///Semaforo
    glPushMatrix();///Palo
        glColor3f(1, 1, 0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, 0.25, 0.25, 5, 20, 20);
        //gluDeleteQuadric(quad);

        glPushMatrix();///ESO P
            glColor3f(1, 1, 0);
            glTranslatef(0, 0, 4);
            gluCylinder(quad, 0.5, 0.5, 2, 20, 20);
            //gluDeleteQuadric(quad);

            glPushMatrix();///Colores
                glColor3f(rojo[0], rojo[1], rojo[2]);///ROJO
                glTranslatef(0.5, 0, 1.5);
                glutSolidSphere(0.25, 20, 20);
            glPopMatrix();

            glPushMatrix();
                glColor3f(ambar[0], ambar[1], ambar[2]);///Ambar: 1, 0.8, 0.4
                glTranslatef(0.5, 0, 1);
                glutSolidSphere(0.25, 20, 20);
            glPopMatrix();

            glPushMatrix();
                glColor3f(verde[0], verde[1], verde[2]);///VERDE
                glTranslatef(0.5, 0, 0.5);
                glutSolidSphere(0.25, 20, 20);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();

}

void pare(){///Se�al Pare
    glPushMatrix();///Palo
        glColor3f(0.5, 0.2, 0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, 0.25, 0.25, 5, 20, 20);
        ////gluDeleteQuadric(quad);

        glPushMatrix();///ESO P
            glTranslated(0.25, 0.25, 5);
            glRotated(90, 0, 1, 0);
            glBegin(GL_POLYGON);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(-0.4,0.73,0);
                glVertex3f(0.4,0.73,0);
                glVertex3f(0.97,0.17,0);
                glVertex3f(0.97,-0.63,0);
                glVertex3f(0.4,-1.2,0);
                glVertex3f(-0.4,-1.2,0);
                glVertex3f(-0.97,-0.63,0);
                glVertex3f(-0.97,0.17,0);
            glEnd();

            glPushMatrix();
                glTranslated(0, -0.05, 0.1);
                glScaled(0.9, 0.9, 0.9);
                glBegin(GL_POLYGON);
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex3f(-0.4,0.73,0);
                    glVertex3f(0.4,0.73,0);
                    glVertex3f(0.97,0.17,0);
                    glVertex3f(0.97,-0.63,0);
                    glVertex3f(0.4,-1.2,0);
                    glVertex3f(-0.4,-1.2,0);
                    glVertex3f(-0.97,-0.63,0);
                    glVertex3f(-0.97,0.17,0);
                glEnd();

                glPushMatrix();
                    glTranslated(0, 0, 0.1);
                    glScaled(0.9, 0.9, 0.9);
                    glBegin(GL_POLYGON);
                        glColor3f(1.0f, 0.0f, 0.0f);
                        glVertex3f(-0.4,0.73,0);
                        glVertex3f(0.4,0.73,0);
                        glVertex3f(0.97,0.17,0);
                        glVertex3f(0.97,-0.63,0);
                        glVertex3f(0.4,-1.2,0);
                        glVertex3f(-0.4,-1.2,0);
                        glVertex3f(-0.97,-0.63,0);
                        glVertex3f(-0.97,0.17,0);
                    glEnd();
                glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}

void viaDoble(){///Se�al Via Doble

    glPushMatrix();///Palo
        glColor3f(0.5, 0.2, 0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, 0.25, 0.25, 5, 20, 20);
        ////gluDeleteQuadric(quad);

        glPushMatrix();
            glTranslated(0.25, 0.0, 5);
            glRotated(90, 0, 1, 0);
            glBegin(GL_POLYGON);
                glColor3f(1.0f, 0.8f, 0.0f);
                glVertex3f(0.0, 1.5, 0);
                glVertex3f(1.5, 0.0, 0.0);
                glVertex3f(0.0, -1.5, 0);
                glVertex3f(-1.5, 0.0, 0);
            glEnd();

            glPushMatrix();
                glTranslated(0.0, 0.0, 0.1);
                glScaled(0.9, 0.9, 0.9);
                glBegin(GL_POLYGON);
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glVertex3f(0.0, 1.5, 0);
                    glVertex3f(1.5, 0.0, 0.0);
                    glVertex3f(0.0, -1.5, 0);
                    glVertex3f(-1.5, 0.0, 0);
                glEnd();

                glPushMatrix();
                    glTranslated(0.0, 0.0, 0.1);
                    glScaled(0.9, 0.9, 0.9);
                    glBegin(GL_POLYGON);
                        glColor3f(1.0f, 0.8f, 0.0f);
                        glVertex3f(0.0, 1.5, 0);
                        glVertex3f(1.5, 0.0, 0.0);
                        glVertex3f(0.0, -1.5, 0);
                        glVertex3f(-1.5, 0.0, 0);
                    glEnd();

                    glPushMatrix();///FLECHA
                        glTranslated(0.0, 0.5, 0.1);
                        glRotated(90.0, 0, 0, 1);
                        glScaled(0.25, 0.45, 0.25);
                        glBegin(GL_POLYGON);
                            glColor3f(0.0f, 0.0f, 0.0f);
                            glVertex3f(0.0, 1.5, 0);
                            glVertex3f(1.0, 0.5, 0.0);
                            glVertex3f(0.5, 0.5, 0);
                            glVertex3f(0.5, -1.5, 0);
                            glVertex3f(-0.5, -1.5, 0);
                            glVertex3f(-0.5, 0.5, 0);
                            glVertex3f(-1.0, 0.5, 0.0);
                        glEnd();
                    glPopMatrix();

                    glPushMatrix();///FLECHA
                        glTranslated(0.0, -0.5, 0.1);
                        glRotated(-90.0, 0, 0, 1);
                        glScaled(0.25, 0.45, 0.25);
                        glBegin(GL_POLYGON);
                            glColor3f(0.0f, 0.0f, 0.0f);
                            glVertex3f(0.0, 1.5, 0);
                            glVertex3f(1.0, 0.5, 0.0);
                            glVertex3f(0.5, 0.5, 0);
                            glVertex3f(0.5, -1.5, 0);
                            glVertex3f(-0.5, -1.5, 0);
                            glVertex3f(-0.5, 0.5, 0);
                            glVertex3f(-1.0, 0.5, 0.0);
                        glEnd();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}

/*
void persona(){

    glPushMatrix();///Tronco
        glColor3f(1, 1, 1);
        glTranslatef(0, 7, 0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(quad, 1.25, 1.5, 4, 20, 20);
        //gluDeleteQuadric(quad);

        glPushMatrix();///Pelvis
            glColor3f(0.5, 0.5, 0.5);
            glTranslatef(0, 0, -1);
            gluCylinder(quad, 1.2, 1.2, 1, 20, 20);
            //gluDeleteQuadric(quad);

            glPushMatrix();///PIERNA DERECHA
                glColor3f(0.1, 0.1, 0.1);
                glTranslatef(0, 0.6, -3.0);
                gluCylinder(quad, 0.5, 0.5, 3, 20, 20);
                //gluDeleteQuadric(quad);

                glPushMatrix();///Rodilla
                    glColor3f(0.5, 0.5, 0.5);
                    glTranslatef(0, 0, 0);
                    glutSolidSphere(0.5, 20, 20);

                    glPushMatrix();///Pierna
                        glColor3f(0.1, 0.1, 0.1);
                        glTranslatef(0.0, 0.0, -3.2);
                        gluCylinder(quad, 0.5, 0.5, 3, 20, 20);
                        //gluDeleteQuadric(quad);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

            glPushMatrix();///PIERNA IZQUIERDA
                glColor3f(0.1, 0.1, 0.1);
                glTranslatef(0, -0.6, -3.0);
                gluCylinder(quad, 0.5, 0.5, 3, 20, 20);
                //gluDeleteQuadric(quad);

                glPushMatrix();///Rodilla
                    glColor3f(0.5, 0.5, 0.5);
                    glTranslatef(0, 0, 0);
                    glutSolidSphere(0.5, 20, 20);

                    glPushMatrix();///Pierna
                        glColor3f(0.1, 0.1, 0.1);
                        glTranslatef(0.0, 0.0, -3.2);
                        gluCylinder(quad, 0.5, 0.5, 3, 20, 20);
                        //gluDeleteQuadric(quad);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

        glPopMatrix();

        glPushMatrix();///HOMBRO DERECHO
            glColor3f(0.5, 0.5, 0.5);
            glTranslatef(0, 1.8, 3.5);
            glutSolidSphere(0.7, 20, 20);

            glPushMatrix();///Antebrazo
                glColor3f(0.1, 0.1, 0.1);
                glTranslatef(0, 0, -2.6);
                gluCylinder(quad, 0.5, 0.5, 3, 20, 20);
                //gluDeleteQuadric(quad);

                glPushMatrix();///Codo
                    glColor3f(0.5, 0.5, 0.5);
                    glTranslatef(0, 0, 0);
                    glutSolidSphere(0.5, 20, 20);

                    glPushMatrix();///Brazo
                        glColor3f(0.1, 0.1, 0.1);
                        glTranslatef(0, 0, -3.2);
                        gluCylinder(quad, 0.5, 0.5, 3, 20, 20);
                        //gluDeleteQuadric(quad);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();///Hombro Izquierdo
            glColor3f(0.5, 0.5, 0.5);
            glTranslatef(0, -1.8, 3.5);
            glutSolidSphere(0.7, 20, 20);

            glPushMatrix();///Antebrazo
                glColor3f(0.1, 0.1, 0.1);
                glTranslatef(0, 0, -2.6);
                gluCylinder(quad, 0.5, 0.5, 3, 20, 20);
                //gluDeleteQuadric(quad);

                glPushMatrix();///Codo
                    glColor3f(0.5, 0.5, 0.5);
                    glTranslatef(0, 0, 0);
                    glutSolidSphere(0.5, 20, 20);

                    glPushMatrix();///Brazo
                        glColor3f(0.1, 0.1, 0.1);
                        glTranslatef(0, 0, -3.2);
                        gluCylinder(quad, 0.5, 0.5, 3, 20, 20);
                        //gluDeleteQuadric(quad);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();///Cuello
            glColor3f(0.5, 0.5, 0.5);
            glTranslatef(0, 0, 4);
            gluCylinder(quad, 0.8, 0.8, 1, 20, 20);
            //gluDeleteQuadric(quad);

            glPushMatrix();///Cabeza
                glColor3f(1, 1, 1);
                glTranslatef(0, 0, 2);
                glutSolidSphere(1.5, 20, 20);

                glPushMatrix();///OJOS
                    glColor3f(0, 0, 0);
                    glTranslatef(1.6, -0.5, 0);
                    glutSolidSphere(0.25, 20, 20);
                glPopMatrix();

                glPushMatrix();///OJOS
                    glColor3f(0, 0, 0);
                    glTranslatef(1.6, 0.5, 0);
                    glutSolidSphere(0.25, 20, 20);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();


    glPopMatrix();

}
*/


void carro(){

    glPushMatrix();///MOTOR :V
        glColor3f(0.0f, 1.0f, 0.0f);
        glTranslated(0,0.5,0);
        glutSolidCube(0.2);

        glPushMatrix(); ///FOCO DELANTERO IZQUIERDO
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslated(-1,0,0.8);
            glutSolidCube(0.2);
        glPopMatrix();

        glPushMatrix(); ///FOCO DELANTERO DERECHO
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslated(-1,0,-0.8);
            glutSolidCube(0.2);
        glPopMatrix();

        glPushMatrix(); ///FOCO TRACERO IZQUIERDO
            glColor3f(1.0f, 0.0f, 0.0f);
            glTranslated(1,0,0.8);
            glutSolidCube(0.2);
        glPopMatrix();

        glPushMatrix(); ///FOCO TRACERO DERECHO
            glColor3f(1.0f, 0.0f, 0.0f);
            glTranslated(1,0,-0.8);
            glutSolidCube(0.2);
        glPopMatrix();

        glPushMatrix();///CUERPO
            glColor3f(0.0f, 0.0f, 1.0f); ///amarillo
            glTranslated(0,0,0);
            glRotated(90,1,0,0);
            glRotated(45,0,0,1);
            glutSolidTorus(0.5,1,20,4);
        glPopMatrix();

         glPushMatrix();///VENTANA
            glColor3f(1.0f, 1.0f, 1.0f); ///amarillo
            glTranslated(0,0.35,0);
            glRotated(90,1,0,0);
            glRotated(45,0,0,1);
            glutSolidTorus(0.6,0.6,8,4);
        glPopMatrix();

        glPushMatrix();///RUEDA DELANTERA IZQUIERDA
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslated(-0.7,-0.4,1);
            glutSolidTorus(0.08,0.25,10,100);
        glPopMatrix();

        glPushMatrix();///RUEDA DELANTERA DERECHA
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslated(-0.7,-0.4,-1);
            glutSolidTorus(0.08,0.25,10,100);
        glPopMatrix();

        glPushMatrix();///RUEDA TRASERA IZQUIERDA
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslated(0.7,-0.4,1);
            glutSolidTorus(0.08,0.25,10,100);
        glPopMatrix();

        glPushMatrix();///RUEDA TRASERA DERECHA
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslated(0.7,-0.4,-1);
            glutSolidTorus(0.08,0.25,10,100);
        glPopMatrix();

    glPopMatrix();
}

void carroE(){

    glPushMatrix();///MOTOR :V
        glColor3f(0.0f, 1.0f, .0f);
        glTranslated(0,0.5,0);
        glutSolidCube(0.2);

        glPushMatrix(); ///FOCO DELANTERO IZQUIERDO
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslated(-1,0,0.8);
            glutSolidCube(0.2);
        glPopMatrix();

        glPushMatrix(); ///FOCO DELANTERO DERECHO
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslated(-1,0,-0.8);
            glutSolidCube(0.2);
        glPopMatrix();

        glPushMatrix(); ///FOCO TRACERO IZQUIERDO
            glColor3f(1.0f, 0.0f, 0.0f);
            glTranslated(1,0,0.8);
            glutSolidCube(0.2);
        glPopMatrix();

        glPushMatrix(); ///FOCO TRACERO DERECHO
            glColor3f(1.0f, 0.0f, 0.0f);
            glTranslated(1,0,-0.8);
            glutSolidCube(0.2);
        glPopMatrix();

        glPushMatrix();///CUERPO
            glColor3f(0.0f, 1.0f, 0.0f); ///amarillo
            glTranslated(0,0,0);
            glRotated(90,1,0,0);
            glRotated(45,0,0,1);
            glutSolidTorus(0.5,1,20,4);
        glPopMatrix();

         glPushMatrix();///VENTANA
            glColor3f(1.0f, 1.0f, 1.0f); ///amarillo
            glTranslated(0,0.35,0);
            glRotated(90,1,0,0);
            glRotated(45,0,0,1);
            glutSolidTorus(0.6,0.6,8,4);
        glPopMatrix();

        glPushMatrix();///RUEDA DELANTERA IZQUIERDA
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslated(-0.7,-0.4,1);
            glutSolidTorus(0.08,0.25,10,100);
        glPopMatrix();

        glPushMatrix();///RUEDA DELANTERA DERECHA
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslated(-0.7,-0.4,-1);
            glutSolidTorus(0.08,0.25,10,100);
        glPopMatrix();

        glPushMatrix();///RUEDA TRASERA IZQUIERDA
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslated(0.7,-0.4,1);
            glutSolidTorus(0.08,0.25,10,100);
        glPopMatrix();

        glPushMatrix();///RUEDA TRASERA DERECHA
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslated(0.7,-0.4,-1);
            glutSolidTorus(0.08,0.25,10,100);
        glPopMatrix();

    glPopMatrix();
}

double legRotation = 0;
double armRotation = 0;
double forearmRotation = 0;
double headRotation = 0;
double handRotation = 0;
double fingerRotation = 0;
double fingerRotationX = 0;
double fingerRotationZ = 0;
double bodyMovement = 0;
double direction = 1;
double bodyRotation = 0;

// steps
float stepLeg = 0.5;
float stepArm = 1;
float stepForearm = -1;
float stepHand = 1;
float stepHead = 0.25;
float stepFinger = 0.25;
float stepBody = 0.0375;
float stepBodyRotation = 0.0625 * 2;

// 17.5 / 0.75, 0.0, -4 / 0.75
double robotPosX = 17.5 / 0.75;
double robotPosY = 0.0;
double robotPosZ = -4 / 0.75;

bool semaforoRojo = false;
int escena = 0;

void animateRobot(int value){
	robotPosZ += 0.05;
    legRotation += stepLeg;
	armRotation += stepArm;
	forearmRotation += stepForearm;
	headRotation += stepHead;
	handRotation += stepHand;
	fingerRotation += stepFinger;
	bodyRotation += stepBodyRotation;
	bodyMovement += stepBody;
	// robot pos
    if (robotPosZ >= (4 / 0.75) && !semaforoRojo){
        robotPosZ -= 0.05;
    }
    // leg anim
	if (legRotation >= 15 || legRotation <= -15 )
	{
		stepLeg *= -1;
	}

	if (armRotation >= 35 || armRotation <= -25 )
	{
		stepArm *= -1;
	}

	if (forearmRotation >= 35 || forearmRotation <= -25 )
	{
		stepForearm *= -1;
	}

	if (headRotation >= 15 || headRotation <= -15) {
		stepHead *= -1;
	}

	if (handRotation >= 35 || handRotation <= -25) {
		stepHand *= -1;
	}

	if (fingerRotation >= 7.5 || fingerRotation <= -7.5) {
		stepFinger *= -1;
	}
	if (bodyRotation >= 4 || bodyRotation <= -4) {
		stepBodyRotation *= -1;
	}
    glutPostRedisplay();  // Solicitar redibujar la escena
    glutTimerFunc(25, animateRobot, 0);  // Configurar el temporizador para la pr�xima iteraci�n
}

void graficarRobot(){
   glPushMatrix(); {
		glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
        glScalef(0.025,0.025,0.025);
		glColor3f(1,1,1);
		// a su lugar
		glTranslatef(0,118,0);
        // rotación
        glRotated(bodyRotation,1,0,0);
		// centro
		glTranslatef(0,-118,0);
		// Torso
		glmDraw(punterosCyborg[0], GLM_SMOOTH | GLM_TEXTURE);

		glPushMatrix(); {
			// a su lugar
			glTranslatef(0,154.2,0);
			// rotación
            glRotated(headRotation,0,1,0);
            // centro
			glTranslatef(0,-154.2,0);
			// cabeza
			glmDraw(punterosCyborg[1], GLM_SMOOTH | GLM_TEXTURE);
		} glPopMatrix();

		// brazo izq
		glPushMatrix(); {
			// a su lugar
			glTranslatef(-42.6,142.4,0);
			// rotación
         glRotated(-armRotation,1,0,0);
         // centro
			glTranslatef(42.6,-142.4,0);
			// brazo izq
			glmDraw(punterosCyborg[2], GLM_SMOOTH | GLM_TEXTURE);

			glPushMatrix(); {
				// a su lugar
				glTranslatef(-2.81 * 20,5.85 * 20,0);
				// rotación
         	glRotated(forearmRotation,1,0,0);
            // centro
				glTranslatef(2.81 * 20,-5.75 * 20,0);
				// antebrazo izq
				glmDraw(punterosCyborg[3], GLM_SMOOTH | GLM_TEXTURE);

				glPushMatrix(); {
					// a su lugar
					glTranslatef(-3.06 * 20,3.34 * 20,0);
					// rotación
                    glRotated(handRotation,1,0,1);
                    // centro
					glTranslatef(3.06 * 20,-3.34 * 20,0);
					// mano izq
					glmDraw(punterosCyborg[4], GLM_SMOOTH | GLM_TEXTURE);
					glPushMatrix(); {
						// a su lugar
						glTranslatef(-2.87 * 20,2.82 * 20,0);
						// rotación
                  glRotated(fingerRotation,1,1,0);
                  // centro
						glTranslatef(2.87 * 20,-2.82 * 20,0);
						// dedos izq
						glmDraw(punterosCyborg[5], GLM_SMOOTH | GLM_TEXTURE);
					} glPopMatrix();
				} glPopMatrix();
			} glPopMatrix();
		} glPopMatrix();
		
		// brazo der
		glPushMatrix(); {
			// a su lugar
			glTranslatef(42.6,142.4,0);
            // rotación
            glRotated(armRotation,1,0,0);
			// centro
			glTranslatef(-42.6,-142.4,0);
			// brazo der
			glmDraw(punterosCyborg[6], GLM_SMOOTH | GLM_TEXTURE);

			glPushMatrix(); {
				// a su lugar
				glTranslatef(2.81 * 20,5.85 * 20,0);
                // rotación
                glRotated(-forearmRotation,1,0,0);
				// centro
				glTranslatef(-2.81 * 20,-5.75 * 20,0);
				// antebrazo der
				glmDraw(punterosCyborg[7], GLM_SMOOTH | GLM_TEXTURE);

				glPushMatrix(); {
					// a su lugar
					glTranslatef(3.06 * 20,3.34 * 20,0);
					// rotación
                    glRotated(-handRotation,1,0,1);
                    // centro
					glTranslatef(-3.06 * 20,-3.34 * 20,0);
					// mano der
					glmDraw(punterosCyborg[8], GLM_SMOOTH | GLM_TEXTURE);
					glPushMatrix(); {
						// a su lugar
						glTranslatef(2.87 * 20,2.82 * 20,0);
						// rotación
                        glRotated(-fingerRotation,1,1,0);
                        // centro
						glTranslatef(-2.87 * 20,-2.82 * 20,0);
						// dedos der
						glmDraw(punterosCyborg[9], GLM_SMOOTH | GLM_TEXTURE);
					} glPopMatrix();
				} glPopMatrix();
			} glPopMatrix();
		} glPopMatrix();
	
		// pierna izq
		glPushMatrix(); {
			// a su lugar
			glTranslatef(-0.78 * 20,3.24 * 20,0);
			// rotación
         glRotated(legRotation,1,0,0);
         // centro
			glTranslatef(0.78 * 20,-3.24 * 20,0);
			// muslo izq
			glmDraw(punterosCyborg[10], GLM_SMOOTH | GLM_TEXTURE);
			
			// pierna izq
			glPushMatrix();{
				// a su lugar
				glTranslatef(-0.84 * 20,1.33 * 20,0);
				// rotación
      		glRotated(-legRotation,1,0,0);
				// centro
				glTranslatef(0.84 * 20,-1.33 * 20,0);
				// pierna izq
				glmDraw(punterosCyborg[11], GLM_SMOOTH | GLM_TEXTURE);
				
				// pie izq
				glPushMatrix();{
					// a su lugar
					glTranslatef(-0.83 * 20,0.30 * 20,0);
					// rotación
					glRotated(-fingerRotation * 2,1,0,0);
					// centro
					glTranslatef(0.83 * 20,-0.30 * 20,0);
					// pie izq
					glmDraw(punterosCyborg[12], GLM_SMOOTH | GLM_TEXTURE);
				} glPopMatrix();
			} glPopMatrix();
		} glPopMatrix();
		
		// pierna der
		glPushMatrix(); {
			// a su lugar
			glTranslatef(0.78 * 20,3.24 * 20,0);
			// rotación
      	glRotated(-legRotation,1,0,0);
      	// centro
			glTranslatef(-0.78 * 20,-3.24 * 20,0);
			// muslo der
			glmDraw(punterosCyborg[13], GLM_SMOOTH | GLM_TEXTURE);
			
			// pierna der
			glPushMatrix();{
				// a su lugar
				glTranslatef(0.84 * 20,1.33 * 20,0);
				// rotación
      		glRotated(legRotation,1,0,0);
				// centro
				glTranslatef(-0.84 * 20,-1.33 * 20,0);
				// pierna der
				glmDraw(punterosCyborg[14], GLM_SMOOTH | GLM_TEXTURE);
				
				// pie der
				glPushMatrix();{
					// a su lugar
					glTranslatef(0.83 * 20,0.30 * 20,0);
					// rotación
					glRotated(fingerRotation * 2,1,0,0);
					// centro
					glTranslatef(-0.83 * 20,-0.30 * 20,0);
					// pie der
					glmDraw(punterosCyborg[15], GLM_SMOOTH | GLM_TEXTURE);
				} glPopMatrix();
			} glPopMatrix();
		} glPopMatrix();
		
	} glPopMatrix();
}


void graficar(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(camX + carroX, camY + carroY, camZ + carroZ, carroX, carroY, carroZ, 0, 1, 0);
    graficarEjes();

    GLUquadric* quad = gluNewQuadric();

    glPushMatrix();
        pista();

        glPushMatrix();///Semaforo
            glTranslatef(12.0, 0.0, -3.5);
            semaforo();
        glPopMatrix();

        glPushMatrix();///Se�al Pare
            glTranslatef(-65, 0, -3.5);
            pare();
        glPopMatrix();

        glPushMatrix();///Se�al Via Doble
            glTranslatef(-75, 0.0, 0.0);
            viaDoble();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();///Peaton
        glScaled(0.75, 0.75, 0.75);
        // 17.5 / 0.75, 0.0, -4 / 0.75
        glTranslated(robotPosX,robotPosY,robotPosZ);
        //glRotated(-90, 0, 1, 0);
        graficarRobot();
    glPopMatrix();

    
    glPushMatrix();///Carro Usuario
        glTranslated(carroX,carroY,carroZ);
        //carro();
        glRotated(-90,0,1,0);
        //LoadTreeTextures();
        glColor3f(1,1,1);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
	    glmDraw(punteroM1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix(); ///Carro Escenario 3
        glTranslatef(carroEX, carroEY, carroEZ);
        glRotated(180, 0 ,1 ,0);
        carroE();
    glPopMatrix();

    // cout << "x = " << carroX;

	glutSwapBuffers();
}




// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
   char *c;

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Routine to convert floating point to char string.
void floatToString(char * destStr, int precision, float val)
{
   sprintf(destStr,"%f",val);
   destStr[precision] = '\0';
}



void animacionSemaforo(int value){

    if(temp >= 0 && temp <= 5){///Rojo
        semaforoRojo = true;
        rojo[0] = 1;
        rojo[1] = 0;
        rojo[2] = 0;
        ambar[0] = 0.5;
        ambar[1] = 0.5;
        ambar[2] = 0.5;
        verde[0] = 0.5;
        verde[1] = 0.5;
        verde[2] = 0.5;
    }

    if(temp >= 6 && temp <= 11){///Verde
        semaforoRojo = false;
        rojo[0] = 0.5;
        rojo[1] = 0.5;
        rojo[2] = 0.5;
        ambar[0] = 0.5;
        ambar[1] = 0.5;
        ambar[2] = 0.5;
        verde[0] = 0;
        verde[1] = 1;
        verde[2] = 0;
    }

    if(temp >= 12 && temp <= 14){///Ambar
        semaforoRojo = false;
        rojo[0] = 0.5;
        rojo[1] = 0.5;
        rojo[2] = 0.5;
        ambar[0] = 1;
        ambar[1] = 0.8;
        ambar[2] = 0.4;
        verde[0] = 0.5;
        verde[1] = 0.5;
        verde[2] = 0.5;
    }

    if(temp == 15){
        temp = 0;
    }

    temp++;

    glutPostRedisplay();  // Solicitar redibujar la escena
    glutTimerFunc(1000, animacionSemaforo, 0);  // Configurar el temporizador para la pr�xima iteraci�n
}

// semaforo: usar variable para bloquear/liberar 
// chequear linea blanca + color rojo
// se le puede poner texto + el temporizador

int cronometro = 0;
bool puedePasarSeñalPare = false;
void timer(int value) {
    if (carroX <= -50 && carroX >= -57)
    {
        // temporizador de 5 segundos
        cronometro += 1;
        // valor de 5 segundos
        std::cout << "cronometro: " << cronometro;
        if (cronometro == 5) {
            puedePasarSeñalPare = true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000,timer,0);
}

void animacionCarro(unsigned char key, int x, int y){

    const float velocidadRecta = 1.0f;
    const float velocidadLateral = 0.2f;
    const float limite = 0.0f;

    switch (key) {

        case 'w':

            if(carroX > -284){
                carroX -= velocidadRecta;
            }else{
                carroX -= limite;
            }
            break;

        case 's':

            if(carroX < 40){
                carroX += velocidadRecta;
            }else{
                carroX += limite;
            }
            break;

        case 'a':

            if(carroZ < 1.8){
                carroZ += velocidadLateral;
            }else{
                carroZ += limite;
            }
            break;

        case 'd':

            if(carroZ > -1.8){
                carroZ -= velocidadLateral;
            }else{
                carroZ -= limite;
            }
            break;
        // reseteo
        case 'r':
            carroX = 30.0;
            carroZ = -1.5;
            puedePasarSeñalPare = false;
            robotPosZ = -4 / 0.75;
            cronometro = 0;
            break;
    }

    // escena 1: regresar semaforo
    // falta: bool/int para seleccionar escena
    // falta: hacer que el carro se detenga solo
    if (carroX == 15 && semaforoRojo)
    {
        std::cout << "Pasaste luz roja";
        carroX = 30;
        carroZ = -1.5;
        robotPosZ = -4 / 0.75;
    } 

    // escena 2
    if (carroX < -57 && puedePasarSeñalPare == false)
    {
        std::cout << "No esperaste los 5 segundos requeridos.";
        carroX = -30;
        carroZ = -1.5;
        cronometro = 0;
    }
    // escena 3
    if (carroX < -130)
    {
        if (carroZ >= 0.5)
        {
            std::cout << "Invadiste carril de sentido contrario";
            carroX = -130;
            carroZ = -1.5;
            carroEX = -225;
            carroEZ = 1.5;
        }
    }
    
    

    glutPostRedisplay();

}

void animacionCarroE(int value){

    if(carroX < -130 && carroEX != -130){
        carroEX = carroEX + 0.9;
    }

    glutPostRedisplay();
    glutTimerFunc(100, animacionCarroE, 0);

}


void redimensionar(int w, int h){
	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)w/(float)h,1,100);

}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(100,200);
	glutCreateWindow("Calle");
	inicializar();

	punteroM1 = glmReadOBJ("modelos/car2.obj");
    punterosCyborg[0] = glmReadOBJ("modelos/bot/Tronco.obj");
   punterosCyborg[1] = glmReadOBJ("modelos/bot/Cabeza.obj");
   punterosCyborg[2] = glmReadOBJ("modelos/bot/Brazo_Izquierdo.obj");
	punterosCyborg[3] = glmReadOBJ("modelos/bot/Antebrazo_Izquierdo.obj");
	punterosCyborg[4] = glmReadOBJ("modelos/bot/Mano_Izquierda.obj");
	punterosCyborg[5] = glmReadOBJ("modelos/bot/Dedos_Izquierdos.obj");
   punterosCyborg[6] = glmReadOBJ("modelos/bot/Brazo_Derecho.obj");
	punterosCyborg[7] = glmReadOBJ("modelos/bot/Antebrazo_Derecho.obj");
	punterosCyborg[8] = glmReadOBJ("modelos/bot/Mano_Derecha.obj");
	punterosCyborg[9] = glmReadOBJ("modelos/bot/Dedos_Derechos.obj");
	punterosCyborg[10] = glmReadOBJ("modelos/bot/Muslo_Izquierdo.obj");
   punterosCyborg[11] = glmReadOBJ("modelos/bot/Pierna_Izquierda.obj");
	punterosCyborg[12] = glmReadOBJ("modelos/bot/Pie_Izquierdo.obj");
	punterosCyborg[13] = glmReadOBJ("modelos/bot/Muslo_Derecho.obj");
   punterosCyborg[14] = glmReadOBJ("modelos/bot/Pierna_Derecha.obj");
	punterosCyborg[15] = glmReadOBJ("modelos/bot/Pie_Derecho.obj");

    glutDisplayFunc(graficar);
	glutReshapeFunc(redimensionar);
    glutKeyboardFunc(animacionCarro);
    //glutIdleFunc(animateRobot);
    glutTimerFunc(1000,timer,0);
    glutTimerFunc(1000, animacionSemaforo, 0);
    glutTimerFunc(100, animacionCarroE, 0);
    glutTimerFunc(25, animateRobot, 0);

	glutMainLoop();

	return 0;
}

