#include <stdlib.h>
// #include <windows.h>
#include <GL/glut.h>
#include "stdafx.h"
#include "glm.h"
#include "Texture.h"

GLMmodel* punterosCyborg[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};


GLuint	texture;
Texture	treeTextureAr[3];

bool LoadTreeTextures()
{
	int i;
	if (LoadTGA(&treeTextureAr[0], "modelos/bot/Game_character_Albedo.tga") /*&& LoadTGA(&treeTextureAr[1], "modelos/bot/Game_character_Roughness.tga") && LoadTGA(&treeTextureAr[2], "modelos/bot/Game_character_Normal.tga")*/)
	{
		for (i = 0; i<1; i++){
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
   //glEnable(GL_NORMALIZE);
	//glEnable(GL_LIGHTING);
		// lighting
	/*
	GLfloat light_diffuse[] = {0.25, 0.25, 0.25, 0.25};
	GLfloat light_specular[] = {0.25, 0.25, 0.25, 0.25};
	GLfloat light_position[] = {1.0, 5.0, -3.0, 0.0};
	GLfloat light_ambient[]= { 0.0, 0.0, 0.0, 1.0 };
	GLfloat global_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	//glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	*/
	// cull back faces
	//glEnable(GL_CULL_FACE);
   //glCullFace(GL_BACK);

	// colorMaterial
	//glEnable(GL_COLOR_MATERIAL);
   //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

double viewX = 5;
double viewY = 5;
double viewZ = 5;

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

void animateRobot(){
	legRotation += stepLeg;
	armRotation += stepArm;
	forearmRotation += stepForearm;
	headRotation += stepHead;
	handRotation += stepHand;
	fingerRotation += stepFinger;
	bodyRotation += stepBodyRotation;
	bodyMovement += stepBody;
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


void controls(unsigned char key, int x, int y){
	switch (key)
	{
	case 'a':
		viewX += 1;
		break;
	
	case 'd':
		viewX -= 1;
		break;
	
	case 'w':
		viewY += 1;
		break;
	
	case 's':
		viewY -= 1;
		break;
		
	case 'q':
		viewZ += 1;
		break;
	
	case 'e':
		viewZ -= 1;
		break;
	
	case 'r':
		viewX = 5;
		viewY = 5;
		viewZ = 5;
		//bodyMovement = 0;
		break;
	case 'k':
		//rotHelper += 1;
		break;

	case 'l':
		//rotHelper -= 1;
		break;

	case 'c':
		//direction *= -1;
		break;

	case 'g':
		//light1Yrotation = 1;
		//light1Rotation += 1;
		//light1Xdirection += 1;
		//std::cout << "plusx" << light1Xmovement;
		//spawnLampLight();
		break;

	case 'h':
		//light1Xdirection -= 1;
		//std::cout << "minusx" << light1Xmovement;
		//spawnLampLight();
		break;
		
	case 'b':
		//light1Yrotation = 1;
		//light1Rotation += 1;
		//light1Ydirection += 1;
		//std::cout << "plusy" << light1Ymovement;
		//spawnLampLight();
		break;

	case 'n':
		//light1Ydirection -= 1;
		//std::cout << "minusy" << light1Ymovement;
		//spawnLampLight();
		break;

	case 'f':
		//light1Yrotation = 1;
		//light1Rotation += 1;
		//light1Zdirection += 1;
		//std::cout << "plusz" << light1Zmovement;
		//spawnLampLight();
		break;

	case 'v':
		//light1Zdirection -= 1;
		//std::cout << "minusZ" << light1Zmovement;
		//spawnLampLight();
		break;
		
	case 'm':
		//std::cout << "light1Xdirection: " << light1Xdirection << "light1Ydirection: " << light1Ydirection << "light1Zdirection: " << light1Zdirection;
		break;

	}
	
	//std::cout << "HEY";
	//glutSwapBuffers();
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
/*
void graficarRobot(){
	
   glPushMatrix(); {
		glScalef(0.005,0.005,0.005);
		glColor3f(1,1,1);
		// a su lugar
		glTranslatef(0,118,0);
		// centro
		glTranslatef(0,-118,0);
		// Torso
		glmDraw(punterosCyborg[0], GLM_SMOOTH | GLM_TEXTURE);

		glPushMatrix(); {
			// a su lugar
			glTranslatef(0,154.2,0);
			// centro
			glTranslatef(0,-154.2,0);
			// cabeza
			glmDraw(punterosCyborg[1], GLM_SMOOTH | GLM_TEXTURE);
		} glPopMatrix();

		// brazo izq
		glPushMatrix(); {
			// a su lugar
			glTranslatef(-42.6,142.4,0);
			// centro
			glTranslatef(42.6,-142.4,0);
			// brazo izq
			glmDraw(punterosCyborg[2], GLM_SMOOTH | GLM_TEXTURE);

			glPushMatrix(); {
				// a su lugar
				glTranslatef(-2.81 * 20,4.74 * 20,0);
				// centro
				glTranslatef(2.81 * 20,-4.74 * 20,0);
				// antebrazo izq
				glmDraw(punterosCyborg[3], GLM_SMOOTH | GLM_TEXTURE);

				glPushMatrix(); {
					// a su lugar
					glTranslatef(-3.06 * 20,3.34 * 20,0);
					// centro
					glTranslatef(3.06 * 20,-3.34 * 20,0);
					// mano izq
					glmDraw(punterosCyborg[4], GLM_SMOOTH | GLM_TEXTURE);
					glPushMatrix(); {
						// a su lugar
						glTranslatef(-2.87 * 20,2.82 * 20,0);
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
			// centro
			glTranslatef(-42.6,-142.4,0);
			// brazo der
			glmDraw(punterosCyborg[6], GLM_SMOOTH | GLM_TEXTURE);

			glPushMatrix(); {
				// a su lugar
				glTranslatef(2.81 * 20,4.74 * 20,0);
				// centro
				glTranslatef(-2.81 * 20,-4.74 * 20,0);
				// antebrazo der
				glmDraw(punterosCyborg[7], GLM_SMOOTH | GLM_TEXTURE);

				glPushMatrix(); {
					// a su lugar
					glTranslatef(3.06 * 20,3.34 * 20,0);
					// centro
					glTranslatef(-3.06 * 20,-3.34 * 20,0);
					// mano der
					glmDraw(punterosCyborg[8], GLM_SMOOTH | GLM_TEXTURE);
					glPushMatrix(); {
						// a su lugar
						glTranslatef(2.87 * 20,2.82 * 20,0);
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
			// centro
			glTranslatef(0.78 * 20,-3.24 * 20,0);
			// muslo izq
			glmDraw(punterosCyborg[10], GLM_SMOOTH | GLM_TEXTURE);
			
			// pierna izq
			glPushMatrix();{
				// a su lugar
				glTranslatef(-0.84 * 20,1.33 * 20,0);
				// centro
				glTranslatef(0.84 * 20,-1.33 * 20,0);
				// pierna izq
				glmDraw(punterosCyborg[11], GLM_SMOOTH | GLM_TEXTURE);
				
				// pie izq
				glPushMatrix();{
					// a su lugar
					glTranslatef(-0.83 * 20,0.30 * 20,0);
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
			// centro
			glTranslatef(-0.78 * 20,-3.24 * 20,0);
			// muslo der
			glmDraw(punterosCyborg[13], GLM_SMOOTH | GLM_TEXTURE);
			
			// pierna der
			glPushMatrix();{
				// a su lugar
				glTranslatef(0.84 * 20,1.33 * 20,0);
				// centro
				glTranslatef(-0.84 * 20,-1.33 * 20,0);
				// pierna der
				glmDraw(punterosCyborg[14], GLM_SMOOTH | GLM_TEXTURE);
				
				// pie der
				glPushMatrix();{
					// a su lugar
					glTranslatef(0.83 * 20,0.30 * 20,0);
					// centro
					glTranslatef(-0.83 * 20,-0.30 * 20,0);
					// pie der
					glmDraw(punterosCyborg[15], GLM_SMOOTH | GLM_TEXTURE);
				} glPopMatrix();
			} glPopMatrix();
		} glPopMatrix();
		
	} glPopMatrix();
}
*/

void graficar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewX,viewY,viewZ, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

	//glTranslatef(0,-1,0);
	//glutSolidCube(1);
	//glPushMatrix();
	
	//glmDraw(punteroM1, GLM_SMOOTH | GLM_TEXTURE);
	//glPopMatrix();

	//glTranslatef(1, 1, 1);
	//glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
	//glmDraw(punteroM2, GLM_SMOOTH | GLM_TEXTURE);
	
	//glScalef(0.2,0.2,0.2);
	glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
	//glmDraw(punterosCyborg, GLM_SMOOTH | GLM_TEXTURE);
	glPushMatrix();
		graficarRobot();
   glPopMatrix();
	
	glPushMatrix(); {
		graficarEjes();
	}
	glPopMatrix();
	glutSwapBuffers();
   glutPostRedisplay();
}

void redimensionar(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
}


/*void animate(int i)
{
	ypoz += 0.5;
	if (ypoz>360) ypoz = 0;
	glutPostRedisplay();
	glutTimerFunc(2, animate, 1);
}
*/

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CYBORG");
	init();


	// punteroM1 = glmReadOBJ("modelos/car2.obj");
	//punteroM2 = glmReadOBJ("modelos/piernaDerecha.obj");
   //punterosCyborg[0] = glmReadOBJ("modelos/Cyborg/Cabeza.obj");
   
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
   glutKeyboardFunc(controls);
	glutIdleFunc(animateRobot);
	//glutTimerFunc(2, animate, 1);
	glutMainLoop();
	return 0;
}
