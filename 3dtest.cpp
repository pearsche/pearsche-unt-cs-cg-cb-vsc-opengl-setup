#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <cmath>

void initialize()
{
	glClearColor(0.8,0.8,0.8,0.0);
	glEnable(GL_DEPTH_TEST);
}

// need to improve this
void showAxis(){
	glColor3i(0,0,0);
	// the dots
	float dotX = 0;
	float dotY = 0;
	float dotZ = 0;
	float limit = 1;
	float step = 0.01;
	
		do {
			// Every 10 steps -> bigger point 
			if ( !((int) (dotX * 100) % 10)) {
				glPointSize(5.0f);
				glBegin(GL_POINTS);
					glVertex3f(dotX,dotY,dotZ);
				glEnd();
			}
			else {
				glPointSize(1.0f);
				glBegin(GL_POINTS);
					glVertex3f(dotX,dotY,dotZ);
				glEnd();
			}
			dotX += step;
			
			if (dotX >= limit) {
				dotX = -limit;
				limit = 0;
			}
		} while (dotX <= limit && dotX != 0);
	dotX = 0;
	limit = 1;
	// improve later
		 do {
			// Every 10 steps -> bigger point 
			if ( !((int) (dotY * 100) % 10)) {
				glPointSize(5.0f);
				glBegin(GL_POINTS);
					glVertex3f(dotX,dotY,dotZ);
				glEnd();
			}
			else {
				glPointSize(1.0f);
				glBegin(GL_POINTS);
					glVertex3f(dotX,dotY,dotZ);
				glEnd();
			}
			dotY += step;
			if (dotY >= limit) {
				dotY = -limit;
				limit = 0;
			}
		} while (dotY <= limit && dotY != 0);
	dotX = 0;
	dotY = 0;
	limit = 1;
			// z
		do {
			// Every 10 steps -> bigger point 
			if ( !((int) (dotZ * 100) % 10)) {
				glPointSize(5.0f);
				glBegin(GL_POINTS);
					glVertex3f(dotX,dotY,dotZ);
				glEnd();
			}
			else {
				glPointSize(1.0f);
				glBegin(GL_POINTS);
					glVertex3f(dotX,dotY,dotZ);
				glEnd();
			}
			dotZ += step;
			if (dotZ >= limit) {
				dotZ = -limit;
				limit = 0;
			}
		} while (dotZ <= limit && dotZ != 0);

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

// TODO: hierarchical model
// 5 parts
//	8 levels
// TODO: add articulated arms
// TODO: divide arms in 2

void drawRobot(){
	
	// Torso
	glColor3f(1,1,0);
	glPushMatrix();
		glTranslatef(0,4.75,0);
		glutWireCube(2.5);
		// Head
		glColor3f(1,0,0);
		glPushMatrix();
			glTranslatef(0,3.75,0);
			glutWireSphere(2.5,20,20);
		glPopMatrix();

		// Left Leg
		glColor3f(1,0,1);
		glPushMatrix();
			glTranslatef(0,-3,0.5);
			glScalef(0.125,0.675,0.125);
			glutWireCube(5);
		glPopMatrix();
		
		// Right Leg
		glColor3f(0.5,0,1);
		glPushMatrix();
			glTranslatef(0,-3,-0.5);
			glScalef(0.125,0.675,0.125);
			glutWireCube(5);
		glPopMatrix();

		// Left forearm
		glColor3f(0.5,0,1);
		glPushMatrix();
			glTranslatef(0,0.03,1.75);
			glScalef(0.125,0.5,0.125);
			glutWireCube(5);
			// left arm
			glPushMatrix();
				glColor3f(1,0,1);
				glTranslatef(0,-3.7,0);
				glScalef(1,0.5,1);
				glutWireCube(5);
				// left hand
				glPushMatrix();
					glColor3f(1,0,0);
					glTranslatef(0,-3.90,0);
					glScalef(1,0.5,1);
					glutWireCube(5);
					// finger 1 
						glPushMatrix();
							glColor3f(0,1,1);
							glTranslatef(0,-4.75,0);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
					// finger 2
						glPushMatrix();
							glColor3f(0,1,1);
							glTranslatef(0,-4.75,-2);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
					
					// finger 3
						glPushMatrix();
							glColor3f(0,1,1);
							glTranslatef(0,-4.75,2);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		// Right forearm
		glColor3f(0.5,0,1);
		glPushMatrix();
			glTranslatef(0,0.03,-1.75);
			glScalef(0.125,0.5,0.125);
			glutWireCube(5);
			// right arm
			glPushMatrix();
				glColor3f(1,0,1);
				glTranslatef(0,-3.7,0);
				glScalef(1,0.5,1);
				glutWireCube(5);
				// right hand
				glPushMatrix();
					glColor3f(1,0,0);
					glTranslatef(0,-3.90,0);
					glScalef(1,0.5,1);
					glutWireCube(5);
					// finger 1 
						glPushMatrix();
							glColor3f(0,1,1);
							glTranslatef(0,-4.75,0);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
					// finger 2
						glPushMatrix();
							glColor3f(0,1,1);
							glTranslatef(0,-4.75,-2);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
					
					// finger 3
						glPushMatrix();
							glColor3f(0,1,1);
							glTranslatef(0,-4.75,2);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		
	glPopMatrix();

	
}

double viewX = 35;
double viewY = 35;
double viewZ = 35;

void moveVision(unsigned char key, int x, int y){
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
		viewX = 35;
		viewY = 35;
		viewZ = 35;
		break;
	}
	//std::cout << "HEY";
	//glutSwapBuffers();
	glutPostRedisplay();
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glColor3f(0,0,0);
	gluLookAt(viewX,viewY,viewZ, 0,0,0, 0,1,0);
	//glutWireTeapot(10);
	drawRobot();
	graficarEjes();

	glutSwapBuffers();


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
	glutKeyboardFunc(moveVision);
	glutReshapeFunc(resize);
	glutMainLoop(); 
	
	return 0;
}