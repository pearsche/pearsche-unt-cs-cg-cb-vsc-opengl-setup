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

double rotHelper = 0;

// all in degress
// unless specified with an X, Y or Z
// rotations happen in the Z axis

double legRotation = 0;
double armRotation = 0;
double forearmRotation = 30;
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
float stepForearm = 1;
float stepHand = 0.25;
float stepHead = 0.25;
float stepFinger = 0.25;
float stepBody = 0.0375;
float stepBodyRotation = 0.0625;
// animation signals, just in case
bool legSignal, armLock, forearmLock, headLock, handLock, fingerLock = false;

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

	if (forearmRotation >= 60 || forearmRotation <= 0 )
	{
		stepForearm *= -1;
	}

	if (headRotation >= 15 || headRotation <= -15) {
		stepHead *= -1;
	}

	if (handRotation >= 10 || handRotation <= -10) {
		stepHand *= -1;
	}

	if (fingerRotation >= 7.5 || fingerRotation <= -7.5) {
		stepFinger *= -1;
	}
	if (bodyRotation >= 2 || bodyRotation <= -2) {
		stepBodyRotation *= -1;
	}

	glutPostRedisplay();
}

void drawRobot(){
	
	
	glColor3f(1,1,0);
	glTranslated(bodyMovement,0,0);
	// FIXME: perhaps implement making the robot turn around
	// glRotated(direction,0,1,0);

	glPushMatrix();
		// Torso
		glRotated(bodyRotation,1,0,0);
		glTranslatef(0,4.75,0);
		glutWireCube(2.5);
		// Head
		glColor3f(1,0,0);
		glPushMatrix();
			glTranslatef(0,3.75,0);
			glRotated(headRotation,0,1,0);
			glutWireSphere(2.5,20,20);
		glPopMatrix();

		// Left Leg
		glColor3f(1,0,1);
		glPushMatrix();
			glRotated(legRotation,0,0,1);
			glTranslatef(0,-3,0.5);
			glScalef(0.125,0.675,0.125);
			glutWireCube(5);
		glPopMatrix();
		
		// Right Leg
		glColor3f(0.5,0,1);
		glPushMatrix();
			glRotated(-legRotation,0,0,1);
			glTranslatef(0,-3,-0.5);
			glScalef(0.125,0.675,0.125);
			glutWireCube(5);
		glPopMatrix();

		// Left arm
		glColor3f(0.5,0,1);
		glPushMatrix();
			glRotated(-armRotation,0,0,1);
			glTranslatef(0,0.03,1.75);
			glScalef(0.125,0.5,0.125);
			glutWireCube(5);
			// left forearm
			glPushMatrix();
				glColor3f(1,0,1);
				glScalef(1,0.5,1);
				glTranslatef(0,-4.5,0);
				glRotated(forearmRotation,0,0,1);
				glutWireCube(5);
				// left hand
				glPushMatrix();
					glColor3f(1,0,0);
					glRotated(handRotation,1,0,1);
					glTranslatef(0,-2.85,0);
					glScalef(1,0.5,1);
					glutWireCube(5);
					// fingers rotation
					glRotated(fingerRotation,1,0,1);
					// finger 1 
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,1);
							glTranslatef(0,-4.75,0);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
					// finger 2
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,1);
							glTranslatef(0,-4.75,-2);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
					
					// finger 3
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,1);
							glTranslatef(0,-4.75,2);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		// Right arm
		glColor3f(0.5,0,1);
		glPushMatrix();
			glRotated(armRotation,0,0,1);
			glTranslatef(0,0.03,-1.75);
			glScalef(0.125,0.5,0.125);
			glutWireCube(5);
			// right forearm
			glPushMatrix();
				glColor3f(1,0,1);
				glScalef(1,0.5,1);
				glTranslatef(0,-4.5,0);
				glRotated(forearmRotation,0,0,1);
				glutWireCube(5);
				// right hand
				glPushMatrix();
					glColor3f(1,0,0);
					glRotated(handRotation,1,0,-1);
					glTranslatef(0,-2.85,0);
					glScalef(1,0.5,1);
					glutWireCube(5);
					
					// finger 1 
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,-1);
							glTranslatef(0,-4.75,0);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
					// finger 2
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,-1);
							glTranslatef(0,-4.75,-2);
							glScalef(0.25,0.75,0.25);
							glutWireCube(5);
						glPopMatrix();
					
					// finger 3
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,-1);
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
		viewX = 35;
		viewY = 35;
		viewZ = 35;
		bodyMovement = 0;
		break;
	case 'k':
		rotHelper += 1;
		break;

	case 'l':
		rotHelper -= 1;
		break;

	case 'c':
		direction *= -1;
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
	graficarEjes();
	drawRobot();
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
	glutKeyboardFunc(controls);
	glutReshapeFunc(resize);
	glutIdleFunc(animateRobot);
	glutMainLoop(); 
	
	return 0;
}