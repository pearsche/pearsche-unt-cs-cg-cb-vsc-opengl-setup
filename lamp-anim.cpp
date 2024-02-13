#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint metal_texture;
GLuint wood_texture;
GLuint ball_texture;
// load a texture from file using the stb_image library
uint32_t loadTexture(const char* filename) {
	int width, height, components;
	unsigned char* data = stbi_load(filename, &width, &height, &components, STBI_rgb);
	
	glPushAttrib(GL_TEXTURE_BIT);
	
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//      glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 0, width, height,GL_RGB, GL_UNSIGNED_BYTE, data);
	glPopAttrib();
	
	
	return id;
}


void initialize()
{
	glClearColor(0.8,0.8,0.8,0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
		// lighting
	GLfloat light_diffuse[] = {0.25, 0.25, 0.25, 0.25};
	GLfloat light_specular[] = {0.25, 0.25, 0.25, 0.25};
	GLfloat light_position[] = {1.0, 5.0, -3.0, 0.0};
	GLfloat light_ambient[]= { 0.0, 0.0, 0.0, 1.0 };
	GLfloat global_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// cull back faces
	glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);

	// colorMaterial
	glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
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
//double headRotation = 0;
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
/*
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

}
*/
/*
void drawRobot(){
	
	
	glColor3f(1,1,0);
	glTranslated(bodyMovement,0,0);
	// FIXME: perhaps implement making the robot turn around
	// glRotated(direction,0,1,0);

	glPushMatrix();
		// Torso
		glRotated(bodyRotation,1,0,0);
		glTranslatef(0,4.75,0);
		glutSolidCube(2.5);
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
			glutSolidCube(5);
		glPopMatrix();
		
		// Right Leg
		glColor3f(0.5,0,1);
		glPushMatrix();
			glRotated(-legRotation,0,0,1);
			glTranslatef(0,-3,-0.5);
			glScalef(0.125,0.675,0.125);
			glutSolidCube(5);
		glPopMatrix();

		// Left arm
		glColor3f(0.5,0,1);
		glPushMatrix();
			glRotated(-armRotation,0,0,1);
			glTranslatef(0,0.03,1.75);
			glScalef(0.125,0.5,0.125);
			glutSolidCube(5);
			// left forearm
			glPushMatrix();
				glColor3f(1,0,1);
				glScalef(1,0.5,1);
				glTranslatef(0,-4.5,0);
				glRotated(forearmRotation,0,0,1);
				glutSolidCube(5);
				// left hand
				glPushMatrix();
					glColor3f(1,0,0);
					glRotated(handRotation,1,0,1);
					glTranslatef(0,-2.85,0);
					glScalef(1,0.5,1);
					glutSolidCube(5);
					// fingers rotation
					glRotated(fingerRotation,1,0,1);
					// finger 1 
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,1);
							glTranslatef(0,-4.75,0);
							glScalef(0.25,0.75,0.25);
							glutSolidCube(5);
						glPopMatrix();
					// finger 2
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,1);
							glTranslatef(0,-4.75,-2);
							glScalef(0.25,0.75,0.25);
							glutSolidCube(5);
						glPopMatrix();
					
					// finger 3
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,1);
							glTranslatef(0,-4.75,2);
							glScalef(0.25,0.75,0.25);
							glutSolidCube(5);
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
			glutSolidCube(5);
			// right forearm
			glPushMatrix();
				glColor3f(1,0,1);
				glScalef(1,0.5,1);
				glTranslatef(0,-4.5,0);
				glRotated(forearmRotation,0,0,1);
				glutSolidCube(5);
				// right hand
				glPushMatrix();
					glColor3f(1,0,0);
					glRotated(handRotation,1,0,-1);
					glTranslatef(0,-2.85,0);
					glScalef(1,0.5,1);
					glutSolidCube(5);
					
					// finger 1 
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,-1);
							glTranslatef(0,-4.75,0);
							glScalef(0.25,0.75,0.25);
							glutSolidCube(5);
						glPopMatrix();
					// finger 2
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,-1);
							glTranslatef(0,-4.75,-2);
							glScalef(0.25,0.75,0.25);
							glutSolidCube(5);
						glPopMatrix();
					
					// finger 3
						glPushMatrix();
							glColor3f(0,1,1);
							// fingers rotation
							glRotated(fingerRotation,1,0,-1);
							glTranslatef(0,-4.75,2);
							glScalef(0.25,0.75,0.25);
							glutSolidCube(5);
						glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		
	glPopMatrix();

	
}
*/




// TODO: splash screen (wire + ball saying "luxo jr together")
// TODO: Lamp model
// TODO: Make the lamp model cast light
// TODO: ball model
// TODO: smol lamp model
// TODO: ALSO make it cast light

double cylinderRotation = 0;
void testRotation() {
	cylinderRotation += 1;
	std::cout << "rot" << cylinderRotation << "\n";
}

void antitestRotation() {
	cylinderRotation -= 1;
	std::cout << "rot" << cylinderRotation << "\n";
}

// TODO: ball anim
double ballXmovement = 0;
double ballYmovement = 0;
double ballZmovement = 0;
double ballRotation = 0;
double ballXrotation = 0;
double ballYrotation = 0;
double ballZrotation = 0;
// essentially "sequence"
int step = 0;

void animBall() {

	switch (step)
	{
	case 0:
		// pos x offscreen -> big lamp base
		// rotation of the ball happens slightly
		ballRotation += 5;
		ballZrotation = 1;
		// first kind of movement happens on X axis
		ballXmovement -= 0.5;
		if (ballXmovement <= -43.5)
		{
			step += 1;
			ballZrotation = 0;
		}
		
		break;
	
	case 1:
		// bounce
		ballRotation -= 1.25;
		//std::cout << "ballRotation" << ballRotation;
		ballZrotation = 1;
		ballXmovement += 0.125;
		if (ballXmovement >= -38.5)
		{
			step += 1;
			ballZrotation = 0;
		}
		break;

	case 12:
		// big lamp base -> offscreen
		ballRotation -= 5;
		ballZrotation = 1;
		ballXmovement += 0.5;
		if (ballXmovement >= 0) {
			step += 1;
		}
		break;
	case 13:
		// pos x offscreen -> neg x offscreen, some pos z gained
		ballZrotation = 1;
		ballYrotation = 1;
		ballRotation += 5;
		ballXmovement -= 0.5;
		ballZmovement += 0.1;
		{
			if (ballXmovement <= -100) {
				step += 10;
			}
		}
		break;
	case 6:
		// neg x offscreen -> near big lamp, z retained
		ballRotation -= 1;
		ballYrotation = 1;
		ballZrotation = 0;
		ballXmovement += 0.25;
		break;

	case 7:
		//near big lamp -> some distance away from big lamp
		ballRotation -= 1;
		ballYrotation = 1;
		ballXmovement += 0.25;
		break;
	}

}

void spawnBall(float size) {
	glPushMatrix();
		glTranslatef(0,size,0);
		// anim: ball movement
		glTranslatef(ballXmovement, 0, ballZmovement);
		// anim: ball rotation
		glRotatef(ballRotation, ballXrotation, ballYrotation, ballZrotation);
		// anim: ball rotation, y axis
		//glRotatef(ballYrotation, 0, 1, 0);
		glutWireSphere(size,250, 250);
	glPopMatrix();
}

// head
double headXmovement = 0;
double headYmovement = 0;
double headZmovement = 0;
double headRotation = 0;
double headXrotation = 0;
double headYrotation = 0;
double headZrotation = 0;

// top arm, affects lamp head a bit
double topXmovement = 0;
double topYmovement = 0;
double topZmovement = 0;
double topRotation = 0;
double topXrotation = 0;
double topYrotation = 0;
double topZrotation = 0;

// combined top+bottom movement
double combinedTBXmovement = 0;
double combinedTBYmovement = 0;
double combinedTBZmovement = 0;
double combinedTBrotation = 0;
double combinedTBYrotation = 0;
double combinedTBZrotation = 0;

// general lamp movement
double lampXmovement = 0;
double lampYmovement = 0;
double lampZmovement = 0;
double lampRotation = 0;
double lampYrotation = 0;
double lampZrotation = 0;

// this is for the bottom arm and the base, essentially
double bottomXmovement = 0;
double bottomYmovement = 0;
double bottomZmovement = 0;
double bottomRotation = 0;
double bottomYrotation = 0;
double bottomZrotation = 0;
int helper = 0;

double light1Rotation = 0;
double light1Xrotation = 0;
double light1Yrotation = 0;
double light1Zrotation = 0;
double light1Xmovement = 8.85;
double light1Ymovement = 11.75;
double light1Zmovement = 0;

double light1Xdirection = 0;
double light1Ydirection = -1;
double light1Zdirection = 0;
void spawnLampLight(){
	GLfloat light1_ambient[ ]={0.125, 0.125, 0.125, 1.0};
	GLfloat light1_diffuse[ ]={1.0, 1.0, 1.0, 1.0};
	GLfloat light1_specular[ ]={1.0, 1.0, 1.0, 1.0};
	// 3.85, 8.75f, 0
	// (-1.95,5.25,0);
	//std::cout << "light pos: " << light1Xmovement << " " << " " << light1Ymovement << " " << light1Zmovement << " ";
	
	GLfloat light1_position[ ]={light1Xmovement, light1Ymovement, light1Zmovement, 1.0};
	GLfloat spot_direction[ ]={light1Xdirection, light1Ydirection, light1Zdirection};
	GLfloat light1_angle = 45;
	//glRotatef(light1Rotation,light1Xrotation,light1Yrotation,light1Zrotation);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_angle);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light1_ambient);

	glEnable(GL_LIGHT1);
}

void animLamp(){
	switch (step)
	{
	case 0:
		// nothing lol
		break;
	
	case 2:
		// head rotates to look at ball
		// then, pushes it offscreen
		headRotation += 0.5;
		headYrotation = 1;
		//light1Rotation += 0.5;
		//light1Yrotation = 1;
		
		light1Xdirection += 0.005;

		spawnLampLight();
		
		if (headRotation >= 10) {
			step += 1;
			//headYrotation = 0;
		}
		break;

	case 3:
		// body then extends so that it can appreciate the ball better
		combinedTBrotation += 0.5;
		combinedTBZrotation = -1;

		//light1Zrotation = -1;
		//light1Rotation = 0.5;
		//light1Xdirection -= 0.005;
		spawnLampLight();

		bottomRotation += 0.5;
		bottomZrotation = -1;


		combinedTBXmovement -= 0.0235;
		combinedTBYmovement += 0.00625;

		//light1Xmovement -= 0.0235;
		//light1Ymovement += 0.00625;
		spawnLampLight();
		
		bottomXmovement += 0.00625;
		//bottomYmovement += 0.00625;

		topRotation += 0.25;
		topZrotation = 1;

		//light1Rotation += 0.25;
		//light1Zrotation = 1;
		spawnLampLight();
		
		topXmovement -= 0.005;
		topYmovement += 0.0135;

		//light1Xmovement += 0.05;
		//light1Ymovement += 0.0135;
		spawnLampLight();

		headRotation -= 0.125;
		headYrotation = 1;

		//light1Rotation -= 0.125;
		//light1Yrotation = 1;
		spawnLampLight();

		if (combinedTBrotation >= 20) {
			step = 8;
			//topZrotation++;
			//combinedTBZrotation++;
			//headYrotation++;
			//helper = topRotation;
		}
		break;

	//TODO: add a wait point between these 2

	case 8:
		//std::cout << " " << helper;
		//topZrotation = 0;
		//combinedTBZrotation = 0;
		//headYrotation = 0;
		// rotates a bit around to look at it better (neg Y, neg X)
		//topRotation = 0;
		helper = topRotation;
		topRotation -= 0.25;
		//topXrotation = 1;
		topZrotation = 1;

		//light1Rotation -= 0.25;
		//light1Zrotation = 1;
		spawnLampLight();
		
		topXmovement += 0.0025;
		topYmovement -= 0.0135;

		light1Xmovement += 0.0125;
		light1Ymovement -= 0.0125;
		//light1Zmovement += 0.0125;
		spawnLampLight();
		
		headRotation += 0.35;
		//light1Rotation += 0.35;
		spawnLampLight();
		
		//headXrotation = 1;
		//headYrotation = 0;
		//headZrotation = 1;

		if (topRotation <= -10) {
			step += 1;
			//topZrotation = 0;
		}
		break;

	//TODO: add pause
	case 9:
		combinedTBrotation += 0.5;
		//light1Rotation += 0.5;
		light1Xdirection -= 0.0075;
		spawnLampLight();
		
		bottomRotation += 0.5;

		//std::cout << "combinedTBrot" << combinedTBrotation;
		combinedTBXmovement -= 0.0265;
		combinedTBYmovement += 0.02;

		light1Xmovement += 0.02;
		light1Ymovement -= 0.075;
		//light1Zmovement += 0.075;
		spawnLampLight();
		
		if (combinedTBrotation >= 45)
		{
			step += 1;
		}
		break;

	case 10:
		//std::cout << " " << topRotation << " ";
		topRotation -= 0.35;
		light1Xmovement -= 0.2;
		light1Ymovement -= 0.005;
		light1Xdirection -= 0.175;
		spawnLampLight();
		
		//topXmovement -= 0.00;
		topYmovement -= 0.025;
		//light1Ymovement += 0.075;
		//light1Zmovement -= 0.075;
		spawnLampLight();
		
		headRotation -= 2.5;
		//light1Rotation += 2.5;
		spawnLampLight();
		

		if (topRotation <= -15) {
			step += 1;
		}
		break;

	case 11:
		headRotation += 2.5;
		//light1Rotation -= 2.5;
		light1Xmovement += 0.1;
		light1Xdirection += 0.125;
		light1Ymovement -= 0.05;
		spawnLampLight();
		//light1Zmovement -= 0.075;
		if (headRotation >= 45) {
			ballRotation += 1;
			ballXmovement += 0.5;
		}

		if (headRotation >= 55)
		{	
			step += 1;
		}
		
		break;
	}
	
}

void spawnLampUpperPart(float scale, GLUquadricObj *lampBase) {
	//
	glPushMatrix();
	//
	
	//GOT IT
	// NEED TO MAKE IT MOVE AS IT GOES UP OR DOWN
	//std::cout << "rot/" << -cylinderRotation / 20;
	//glTranslatef(-0.75,-cylinderRotation / 25,0);
	// anim: upper movement
	glTranslatef(topXmovement,topYmovement,topZmovement);
	// move back to where it was
	glTranslatef(0,8,0);
	// anim: rotate, z axis
	glRotatef(topRotation * 1.25,topXrotation,topYrotation,topZrotation);
	
	// anim: rotate, y axis
	//glRotatef(topYrotation, 0, 1, 0);
	glTranslatef(0,-8,0);
	
	glPushMatrix(); {
		// lamp head
		// anim: rotation
		
		// anim: rotate, y axis
		//glRotatef(headYrotation, 0, 1, 0);
		glPushMatrix(); {
			glColor3f(0.75,0.75,0.75);
			glTranslatef(3.85, 8.75f, 0);
			
			glRotated(90, 1, 0, 0);
			glRotatef(headRotation * 1.25,headXrotation,headYrotation,headZrotation);
			//glRotatef(-cylinderRotation,0,0,1);
			gluCylinder(lampBase, 0.5, 1.5, 1.5, 1000, 1000);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// top arm joint
	glPushMatrix(); {
		// inclined top
		glPushMatrix();{
			glColor3f(0.75,0.75,0.75);
			glTranslatef(3.15,8.45,0);
			glRotatef(40,0,0,1);
			//glRotatef(-cylinderRotation,0,0,1);
			glScalef(1.75,0.375, 0.45);
			glutSolidCube(1);
		}
		glPopMatrix();

		// horizontal bit
		glPushMatrix(); {
			glColor3f(0.75,0.75,0.75);
			glTranslatef(2.85,8.65,0);
			glRotatef(10,0,0,1);
			//glRotatef(-cylinderRotation,0,0,1);
			glScalef(1.25,0.375, 1);
			glutSolidCube(1);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// top arm
	glPushMatrix(); {
		//glPushMatrix();
		//glPopMatrix();
		// left rod that goes between the arm joint and the horizontal rod in the bottom rod that connects to the lamp head
		glPushMatrix(); {
			glColor3f(0.75,0.75,0.75);
			glTranslatef(-0.55,7.95,0.375);
			glRotatef(80,0,0,1);
			
				//glRotatef(-cylinderRotation,0,0,1);
				//glRotatef(-cylinderRotation,0,0,1);
				glScalef(0.175,2.75,0.175);
			glutSolidCube(1);
		}
		glPopMatrix();

		// right rod that goes between the arm joint and the horizontal rod in the bottom rod that connects to the lamp head
		glPushMatrix(); {
			glColor3f(0.75,0.75,0.75);
			glTranslatef(-0.55,7.95,-0.375);
			glRotatef(80,0,0,1);
			//glRotatef(-cylinderRotation,0,0,1);
			glScalef(0.175,2.75,0.175);
			glutSolidCube(1);
		}
		glPopMatrix();

		// rod in the middle of the bottom rod
		glPushMatrix(); {
			glColor3f(0.75,0.75,0.75);
			glTranslatef(0.75,7.725,0);
			//glRotatef(-cylinderRotation,0,0,1);
			glScalef(0.175,0.175,1.5);
			glutSolidCube(1);
		}
		glPopMatrix();

		// rod behind the inclined thing
		glPushMatrix(); {
			glColor3f(0.75,0.75,0.75);
			//glRotatef(16.5,0,0,1);
			glTranslatef(-1.85,8.175,0);
			//glRotatef(12,0,0,1);
			//glRotatef(-cylinderRotation,0,0,1);
			glScalef(0.175,0.175,1.5);
			glutSolidCube(1);
		}
		glPopMatrix();
		
		// upper rod above the previous rod
		glPushMatrix(); {
			glColor3f(0.75,0.75,0.75);
			glTranslatef(0.225,8.35,0);
			glRotatef(-85,0,0,1);
			//glRotatef(-cylinderRotation,0,0,1);
			glScalef(0.175,4.5,0.175);
			glutSolidCube(1);
		}
		glPopMatrix();

		// bottom rod that connects 2nd arm to the arm joint
		glPushMatrix(); {
			glColor3f(0.75,0.75,0.75);
			glTranslatef(0.135,7.675,0);
			glRotatef(-85,0,0,1);
			//glRotatef(-cylinderRotation,0,0,1);
			glScalef(0.175,5,0.175);
			glutSolidCube(1);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// arm joint
	glPushMatrix(); { // ...
		//glRotatef(cylinderRotation,0,0,1);
		glPushMatrix(); { // inclined metal uh thing
			//glTranslatef(2.6,7.75,0);
			//glRotatef(cylinderRotation,0,0,1);
			glPushMatrix(); {
				glColor3f(0.75,0.75,0.75);
				glTranslatef(-2.6,7.75,0);
				//glTranslatef(-2.6 - -cylinderRotation / 10, 7.75 - -cylinderRotation / 10, 0);
				glRotatef(30,0,0,1);
				//glRotatef(-cylinderRotation * 1.375 ,0,0,1);
				glScalef(1.75,0.375, 0.45);
				glutSolidCube(1);
			}
			glPopMatrix();
		} // inclined metal thing
		glPopMatrix(); // ...
		

		// horizontal rod
		glPushMatrix(); { // ...
			//glRotatef(cylinderRotation,0,0,1);
			glPushMatrix(); {
				glColor3f(0.75,0.75,0.75);
				glTranslatef(-2.9,7.35,0);
				glRotatef(10,0,0,1);
				//glRotatef(-cylinderRotation * 1.5 ,0,0,1);
				glScalef(1,0.375, 1);
				glutSolidCube(1);
			}
			glPopMatrix(); 
		} // horizontal rod
		glPopMatrix(); // ...
	}
	glPopMatrix();

	//
	glPopMatrix();
	//
}
void spawnLamp(float scale) {
	GLUquadricObj *lampBase = gluNewQuadric();
	gluQuadricDrawStyle(lampBase, GLU_LINE);
	
	glPushMatrix(); {
		glMatrixMode(GL_MODELVIEW);
		// global scale
		glScalef(scale,scale,scale);
		// built bottom to top
		// anim: body movement
		glTranslatef(lampXmovement,lampYmovement,lampZmovement);
		// anim: rotation
		glRotatef(lampRotation, 0, lampYrotation, lampZrotation);
		// anim: rotation y axis
		//glRotatef(lampYrotation, 0, 1, 0);
		glPushMatrix(); {
			
			
			// for the anim
			glPushMatrix(); {
				// combined top+bottom animation, excluding lamp base
				// anim: combined t+b movement
				glTranslatef(combinedTBXmovement,combinedTBYmovement,combinedTBZmovement);
				// anim: combined t+b rotation, z axis
				glRotatef(combinedTBrotation,0,combinedTBYrotation,combinedTBZrotation);
				// anim: combined t+b rotation, y axis
				//glRotatef(combinedTBYrotation, 0, 1, 0);
				glPushMatrix(); {;
					spawnLampUpperPart(scale,lampBase);
				}
				glPopMatrix();

				// bottom arm
				glPushMatrix(); {
					// anim: bottom part movement
					//glTranslatef(bottomXmovement,bottomYmovement,bottomZmovement);
					// anim: bottom rotation, z axis
					//glRotatef(bottomRotation,0,bottomYrotation,bottomZrotation);
					// anim: bottom rotation, y axis
					//glRotatef(bottomYrotation,0,1,0);
					// back rod from the base to the top arm
					glPushMatrix(); {
						glColor3f(0.75,0.75,0.75);
						glTranslatef(-1.95,5.25,0);
						glRotatef(35,0,0,1);
						glScalef(0.175,5,0.175);
						glutSolidCube(1);
					}
					glPopMatrix();
					

					// lil rod that connects both bottle like shape sides
					glPushMatrix(); {
						glColor3f(0.75,0.75,0.75);
						glRotatef(16.5,0,0,1);
						glTranslatef(0,6.5,0);
						glRotatef(12,0,0,1);
						glScalef(0.175,0.175,0.5);
						glutSolidCube(1);
					}
					glPopMatrix();
					
					// right side of the bottle like shape
					glPushMatrix(); {
						glColor3f(0.75,0.75,0.75);
						glTranslatef(-1.15,5.25,-0.35);
						glRotatef(35,0,0,1);
						glScalef(0.175,5,0.175);
						glutSolidCube(1);
					}
					glPopMatrix();
					
					// left side of the bottle like shape
					glPushMatrix(); {
						glColor3f(0.75,0.75,0.75);
						glTranslatef(-1.15,5.25,0.35);
						glRotatef(35,0,0,1);
						glScalef(0.175,5,0.175);
						glutSolidCube(1);
					}
					glPopMatrix();
					

					// left rod that connects from the lil rod up above to the long metal bit
					glPushMatrix(); {
						glColor3f(0.75,0.75,0.75);
						glTranslatef(-0.555,5.52,0.175);
						glRotatef(59.5,0,0,1);
						glScalef(0.175,3,0.175);
						glutSolidCube(1);
					}
					glPopMatrix();

					// right rod that connects from the lil rod up above to the long metal bit
					glPushMatrix(); {
						glColor3f(0.75,0.75,0.75);
						glTranslatef(-0.555,5.52,-0.15);
						glRotatef(59.5,0,0,1);
						glScalef(0.175,3,0.175);
						glutSolidCube(1);
					}
					glPopMatrix();
				}
				glPopMatrix();

		}
			glPopMatrix();

			// bottom part 
			glPushMatrix(); {
				// anim: bottom part movement
				glTranslatef(bottomXmovement,bottomYmovement,bottomZmovement);
				
				// anim: bottom rotation, y axis
				//glRotatef(bottomRotation,0,bottomYrotation,0);
				
				glTranslatef(0.25,3.65,0);
				// anim: combined t+b movement
				
				//glTranslatef(combinedTBXmovement,combinedTBYmovement,combinedTBZmovement);
				// anim: bottom rotation, z axis
				glRotatef(bottomRotation,0,bottomYrotation,bottomZrotation);
				// anim: combined t+b rotation, z axis
				//glRotatef(combinedTBrotation,0,combinedTBYrotation,combinedTBZrotation);
				glTranslatef(-0.25,-3.65,0);
				// inclined metal uh thing
				glPushMatrix(); {
					glColor3f(0.75,0.75,0.75);
					glTranslatef(0.25,3.85,0);
					glRotatef(50,0,0,1);
					glScalef(2.375,0.375, 0.45);
					glutSolidCube(1);
				}
				glPopMatrix();

				// lil dent 1
				glPushMatrix(); {
					glColor3f(0.75,0.75,0.75);
					glTranslatef(0.35,3.65,-0.15);
					glRotatef(10,0,0,1);
					glScalef(0.1,1,0.05);
					glutSolidCube(1);
				}
				glPopMatrix();
				
				// lil dent 2 
				glPushMatrix(); {;
					glColor3f(0.75,0.75,0.75);
					glTranslatef(0.35,3.65,0.15);
					glRotatef(10,0,0,1);
					glScalef(0.1,1,0.05);
					glutSolidCube(1);
				}
				glPopMatrix();
				
				// horizontal rod
				glPushMatrix(); {
					glColor3f(0.75,0.75,0.75);
					glTranslatef(0,3,0);
					glRotatef(10,0,0,1);
					glScalef(1,0.375, 1);
					glutSolidCube(1);
				}
				glPopMatrix();
			}
			glPopMatrix();

			// lil rod connecting the lamp base and the bottom arm
			glPushMatrix(); {
				// anim: bottom part movement
				//glTranslatef(bottomXmovement,bottomYmovement,bottomZmovement);
				// anim: bottom rotation, z axis
				// disabled: perhaps not needed
				// glRotatef(bottomZrotation,0,0,1);
				// anim: bottom rotation, y axis
				//glRotatef(bottomRotation,0,bottomYrotation,0);

				glTranslatef(0, 2.65, 0);
				glScalef(0.375, 1, 0.375);
				glutSolidCube(1);
			}
			glPopMatrix();
		}
		glPopMatrix();
		
		// lamp base 
		glPushMatrix(); {
			// top part of the lamp base
			// anim: bottom part movement
			//glTranslatef(bottomXmovement,bottomYmovement,bottomZmovement);
			// anim: bottom rotation, z axis
			// disabled: perhaps not needed
			// glRotatef(bottomZrotation,0,0,1);
			// anim: bottom rotation, y axis
			//glRotatef(bottomRotation,0,bottomYrotation,0);
			glPushMatrix(); {
				glColor3f(0.75,0.75,0.75);
				glTranslatef(0, 2.25f, 0);
				glRotated(90, 1, 0, 0);
				gluCylinder(lampBase, 0.25, 1, 0.75, 1000, 1000);
			}
			glPopMatrix();
			// mid part of the lamp base
			glPushMatrix(); {
				glColor3f(0.75,0.75,0.75);
				glTranslatef(0, 1.5f, 0);
				glRotated(90, 1, 0, 0);
				gluCylinder(lampBase, 1, 3, 1.5, 1000, 1000);
			}
			glPopMatrix();
			// bottom bit
			glPushMatrix(); {
				glColor3f(0.75,0.75,0.75);
				glRotated(90, 1, 0, 0);
				gluCylinder(lampBase, 1,3,0,1000,1000);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}


void spawnFloor(){
	glPushMatrix();
		//glNormal3f(0,-1,0);
		for (int i = 0; i < 125; i++)
		{
			glPushMatrix();
				glTranslatef(0,0,i);
				glutSolidCube(1);
				for (int i = 0; i < 125; i++)
		{
			glPushMatrix();
				glTranslatef(i,0,0);
				glutSolidCube(1);
			glPopMatrix();
		}
			glPopMatrix();
		}
		
		
		
	glPopMatrix();
}
void animate(){
	animBall();
	animLamp();
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

	case 'g':
		//light1Yrotation = 1;
		//light1Rotation += 1;
		light1Xdirection += 1;
		//std::cout << "plusx" << light1Xmovement;
		spawnLampLight();
		break;

	case 'h':
		light1Xdirection -= 1;
		//std::cout << "minusx" << light1Xmovement;
		spawnLampLight();
		break;
		
	case 'b':
		//light1Yrotation = 1;
		//light1Rotation += 1;
		light1Ydirection += 1;
		//std::cout << "plusy" << light1Ymovement;
		spawnLampLight();
		break;

	case 'n':
		light1Ydirection -= 1;
		//std::cout << "minusy" << light1Ymovement;
		spawnLampLight();
		break;

	case 'f':
		//light1Yrotation = 1;
		//light1Rotation += 1;
		light1Zdirection += 1;
		//std::cout << "plusz" << light1Zmovement;
		spawnLampLight();
		break;

	case 'v':
		light1Zdirection -= 1;
		//std::cout << "minusZ" << light1Zmovement;
		spawnLampLight();
		break;
		
	case 'm':
		std::cout << "light1Xdirection: " << light1Xdirection << "light1Ydirection: " << light1Ydirection << "light1Zdirection: " << light1Zdirection;
		break;

	}
	
	//std::cout << "HEY";
	//glutSwapBuffers();
}


void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();
	//glColor3f(0,0,0);
	gluLookAt(viewX,viewY,viewZ, 0,0,0, 0,1,0);
	//glutWireTeapot(10);
	graficarEjes();
	//glTranslatef(0,5.0f,0);
	glEnable(GL_MODULATE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLfloat plano_s[4] = {1, 0, 0, 0};
	GLfloat plano_t[4] = {0, 1, 0, 0};
	
	glPushMatrix();
		//GLfloat mat_specular[]={1.0,1.0, 1.0, 1.0};
		//GLfloat low_shininess[]={5.0};
		//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		//glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, metal_texture);
		
		float matSpecLamp[] = { 1.0, 1.0, 1.0, 1.0 };
		float matShineLamp[] = { 100.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecLamp);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShineLamp);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_TEXTURE_WRAP_S);
		glTexGenfv (GL_S, GL_OBJECT_PLANE, plano_s);
		glEnable(GL_TEXTURE_GEN_S);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_TEXTURE_WRAP_T);
		glTexGenfv (GL_T, GL_OBJECT_PLANE, plano_t);
		glEnable (GL_TEXTURE_GEN_T);
		//glColor3f(0.53,0.13,0.003);
		//glColor3f(0.0,0.0,0.5);
		spawnLamp(2);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
		
		spawnLampLight();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(50,0,0);
		
		float matSpecBall[] = { 1.0, 1.0, 1.0, 1.0 };
		float matShineBall[] = { 50.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecBall);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShineBall);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ball_texture);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenfv (GL_S, GL_OBJECT_PLANE, plano_s);
		glEnable(GL_TEXTURE_GEN_S);
		 
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenfv (GL_T, GL_OBJECT_PLANE, plano_t);
		glEnable (GL_TEXTURE_GEN_T);
		glColor3f(1,1,0);
		spawnBall(2);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, wood_texture);
		float matSpecFloor[] = { 1.0, 1.0, 1.0, 1.0 };
		float matShineFloor[] = { 50.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecFloor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShineFloor);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_TEXTURE_WRAP_S);
		glTexGenfv (GL_S, GL_OBJECT_PLANE, plano_s);
		glEnable(GL_TEXTURE_GEN_S);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_TEXTURE_WRAP_T);
		glTexGenfv (GL_T, GL_OBJECT_PLANE, plano_t);
		glEnable (GL_TEXTURE_GEN_T);
		glColor3f(0.53,0.13,0.003);
		glTranslatef(-25,-0.5,-25);
		glScalef(0.5,0,0.5);
		spawnFloor();
		glDisable(GL_TEXTURE_2D);
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
	glutIdleFunc(animate);
	
	metal_texture = loadTexture("metal-texture.jpg");
	if (!metal_texture)  {
		printf("No texture created; exiting.\n");
		return EXIT_FAILURE;
	}
	wood_texture = loadTexture("wood-texture.jpg");
	if (!wood_texture)  {
		printf("No texture created; exiting.\n");
		return EXIT_FAILURE;
	}
	ball_texture = loadTexture("ball-texture.jpg");
	if (!ball_texture)  {
		printf("No texture created; exiting.\n");
		return EXIT_FAILURE;
	}
	glutMainLoop(); 
	
	return 0;
}