#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <cmath>

void inicializar()
{
	glClearColor(1,1,1,1);
}

// need to improve this
void showAxis(){
	glColor3i(0,0,0);
	// the dots
	float dotX = 0;
	float dotY = 0;
	float limit = 1;
	float step = 0.01;
	
		do {
			// Every 10 steps -> bigger point 
			if ( !((int) (dotX * 100) % 10)) {
				glPointSize(5.0f);
				glBegin(GL_POINTS);
					glVertex2f(dotX,dotY);
				glEnd();
			}
			else {
				glPointSize(1.0f);
				glBegin(GL_POINTS);
					glVertex2f(dotX,dotY);
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
					glVertex2f(dotX,dotY);
				glEnd();
			}
			else {
				glPointSize(1.0f);
				glBegin(GL_POINTS);
					glVertex2f(dotX,dotY);
				glEnd();
			}
			dotY += step;
			if (dotY >= limit) {
				dotY = -limit;
				limit = 0;
			}
		} while (dotY <= limit && dotY != 0);

}

void moveFigure(float steps){ 




}

void keyboardControl(unsigned char key, int x, int y){
	switch (key)
	{
	case 'w':
		//move function
		break;
	
	case 'd':
		//move function
		break;

	case 's':
		//move function
		break;
	
	case 'a':
		//move function
		break;
	
	case 'i':
		//rotate function
		break;
	
	case 'l':
		//rotate function
		break;
	
	case 'k':
		//rotate function
		break;
	
	case 'j':
		//rotate function
		break;
	



	}

}

void drawCube(float FCoriginX, float FCoriginY, int size, int red, int green, int blue, float scaleFactor){
	// double = more precision, otherwise it makes the if > 0.2 part fail
	double actualSize = (double) size / 10;
	glPushMatrix();
		glScalef(scaleFactor,scaleFactor,scaleFactor);
		float strongestIlumination = 0.75;
		float midIlumination = 0.5;
		float weakestIlumination = 0.25;
		
		glBegin(GL_POLYGON);
			// front
			glColor3f(red * midIlumination * 3 / 4, green * midIlumination * 3 / 4, blue * midIlumination * 3 / 4);
			glVertex2f(FCoriginX, FCoriginY);
			glColor3f(red * midIlumination, green * midIlumination, blue * midIlumination);
			glVertex2f(FCoriginX + actualSize, FCoriginY);
			glColor3f(red * weakestIlumination, green * weakestIlumination, blue * weakestIlumination);
			glVertex2f(FCoriginX + actualSize, FCoriginY + actualSize);
			glColor3f(red * weakestIlumination, green * weakestIlumination, blue * weakestIlumination);
			glVertex2f(FCoriginX, FCoriginY + actualSize);

			glVertex2f(FCoriginX, FCoriginY);
		
		// upper bit
		glEnd();
		glBegin(GL_POLYGON);
			float UBoriginX = FCoriginX;
			float UBoriginY = FCoriginY + actualSize;
			float specialSize;
			if ( actualSize > 0.2) {
				specialSize =  actualSize - 0.2  ;
			}
			else {
				specialSize = 0.05;
			}
			glColor3f(red * midIlumination * 3 / 5, green * midIlumination * 3 / 5, blue * midIlumination * 3 / 5);
			glVertex2f(UBoriginX, UBoriginY);
			glColor3f(red * midIlumination * 3 / 5, green * midIlumination * 3 / 5, blue * midIlumination * 3 / 5);
			glVertex2f(UBoriginX + actualSize, UBoriginY);
			glColor3f(red * midIlumination * 1/ 5, green * midIlumination * 1/ 5, blue * midIlumination * 1/ 5);
			glVertex2f(UBoriginX + actualSize + specialSize, UBoriginY + specialSize);
			glColor3f(red * midIlumination * 1/ 5, green * midIlumination * 1/ 5, blue * midIlumination * 1/ 5);
			glVertex2f(UBoriginX + specialSize, UBoriginY + specialSize);
			glVertex2f(UBoriginX, UBoriginY);
		glEnd();

		// side
		glBegin(GL_POLYGON);
			float SoriginX = UBoriginX + actualSize + specialSize;
			float SoriginY = UBoriginY + specialSize;
			glColor3f(red * midIlumination * 1/ 5, green * midIlumination * 1/ 5, blue * midIlumination * 1/ 5);
			glVertex2f(SoriginX, SoriginY);
			glColor3f(red * midIlumination * 1/ 5, green * midIlumination * 1/ 5, blue * midIlumination * 1/ 5);
			glVertex2f(SoriginX, SoriginY - actualSize);
			glColor3f(red * midIlumination * 3 / 5, green * midIlumination * 3 / 5, blue * midIlumination * 3 / 5);
			glVertex2f(SoriginX - specialSize, SoriginY - actualSize - specialSize);
			glColor3f(red * midIlumination * 3 / 5, green * midIlumination * 3 / 5, blue * midIlumination * 3 / 5);
			glVertex2f(SoriginX - specialSize, SoriginY - specialSize);
			glVertex2f(SoriginX, SoriginY);
		glEnd();
	glPopMatrix();
}

void drawTable(){
	glColor3f(0,0,0);
	glColor3f(0,255,0);
	
	// platform
	glBegin(GL_POLYGON);
	  glColor3f(0.125,0,0);
	  glVertex2f(0,0.5);
	  glColor3f(0.25,0,0);
	  glVertex2f(0.6,0.2);
	  glColor3f(1,0,0);
	  glVertex2f(0,-0.5);
	  glColor3f(0.25,0,0);
	  glVertex2f(-0.6,0.2);
	  glVertex2f(0,0.5);
	glEnd();

	// table legs
	float TLoriginX = 0;
	float TLoriginY = -0.5;
	glBegin(GL_POLYGON);
		
		glColor3f(1,0,0);
		glVertex2f(TLoriginX,TLoriginY);
		
		glVertex2f(TLoriginX + 0.025, TLoriginY - -0.03);
		glVertex2f(TLoriginX + 0.025, TLoriginY + -0.12);
		glVertex2f(TLoriginX - 0.025, TLoriginY + -0.12);
		glVertex2f(TLoriginX - 0.025, TLoriginY - -0.03);
		glVertex2f(TLoriginX,TLoriginY);
	glEnd();

	TLoriginX = 0.6;
	TLoriginY = 0.2;
	glBegin(GL_POLYGON);
		glColor3f(0.25,0,0);
		glVertex2f(TLoriginX, TLoriginY);
		glVertex2f(TLoriginX, TLoriginY - 0.12);
		glVertex2f(TLoriginX - 0.03, TLoriginY - 0.12);
		glVertex2f(TLoriginX - 0.03, TLoriginY - 0.03);
		glVertex2f(TLoriginX, TLoriginY);
	glEnd();

	TLoriginX *= -1;
	glBegin(GL_POLYGON);
		glColor3f(0.25,0,0);
		glVertex2f(TLoriginX, TLoriginY);
		glVertex2f(TLoriginX, TLoriginY - 0.12);
		glVertex2f(TLoriginX - -0.03, TLoriginY - 0.12);
		glVertex2f(TLoriginX - -0.03, TLoriginY - 0.03);
		glVertex2f(TLoriginX, TLoriginY);
	glEnd();
}

void drawFirstTriangleStripFirstTablePart(){
	glColor3f(0.125,0.125,0.125);
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.125,0.125,0.125);
		glVertex2f(0.06,-0.01);
		glColor3f(0.0625,0.0625,0.0625);
		glVertex2f(-0.1,0.08);
		glColor3f(0.5,0.5,0.5);
		glVertex2f(0.04,-0.07);
		glColor3f(0.5,0.5,0.5);
		glVertex2f(-0.1,-0.07);
	glEnd();
}

void drawFirstQuadSecondTablePart(){
	glColor3f(0.125,0.125,0.125);
	glBegin(GL_QUADS);
		glColor3f(0.0625,0.0625,0.0625);
		glVertex2f(0.088,0.083);
		glColor3f(0.125,0.125,0.125);
		glVertex2f(0.06,-0.01);
		glColor3f(0.125,0.125,0.125);
		glVertex2f(-0.03,0.04);
		glColor3f(0.0625,0.0625,0.0625);
		glVertex2f(0.01,0.125);
		//glVertex2f(0.078,0.083);
	glEnd();
}

void drawSecondQuadSecondTablePart(){
	glColor3f(0.125,0.125,0.25);
	glBegin(GL_QUADS);
		glColor3f(0.0625,0.0625,0.0625);
		glVertex2f(0.01,0.125);
		glColor3f(0.125,0.125,0.125);
		glVertex2f(-0.03,0.04);
		glColor3f(0.0625,0.0625,0.0625);
		glVertex2f(-0.1,0.08);
		glColor3f(0.03125,0.03125,0.03125);
		glVertex2f(-0.05,0.16);	
	glEnd();
}

void drawSecondQuadStripThirdTablePart(){
	glColor3f(0.03125,0.03125,0.03125);
	glBegin(GL_QUAD_STRIP);
		glVertex2f(-0.02,0.18);
		glVertex2f(-0.05,0.16);
		glVertex2f(0.02,0.16);
		glVertex2f(0.01,0.125);
		glVertex2f(0.10,0.12);
		glVertex2f(0.088,0.083);
	glEnd();
}

void drawFirstPolygonRightTableBorder(){
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glColor3f(0.25,0.25,0.25);
		glVertex2f(0.11,0.11);
		glColor3f(0.75,0.75,0.75);
		glVertex2f(0.05,-0.07);
		glColor3f(0.75,0.75,0.75);
		glVertex2f(0.04,-0.07);
		glColor3f(0.25,0.25,0.25);
		glVertex2f(0.10,0.12);
		//glVertex2f(0.098,0.093);
		
	glEnd();
}

void drawSecondPolygonLeftTableBorder(){
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_POLYGON);
		glColor3f(0.5,0.5,0.5);
		glVertex2f(0.05,0.16);
		glColor3f(0.5,0.5,0.5);
		glVertex2f(0.05,0.13);
		glColor3f(0.125,0.125,0.125);
		glVertex2f(-0.02,0.18);
		glColor3f(0.125,0.125,0.125);
		glVertex2f(-0.02,0.19);
		glVertex2f(0.05,0.16);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.25,0.25,0.25);
		glVertex2f(-0.06,0.17);
		glColor3f(0.25,0.25,0.25);
		glVertex2f(-0.05,0.16);
		glColor3f(0.75,0.75,0.75);
		glVertex2f(-0.1,0.08);
		glColor3f(0.75,0.75,0.75);
		glVertex2f(-0.11,0.09);
		glVertex2f(-0.06,0.17);
	glEnd();
}

void drawFirstTriangleTableBorderCorner(){
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_TRIANGLES);
		glColor3f(0.125,0.125,0.125);
		glVertex2f(-0.02,0.19);
		glColor3f(0.25,0.25,0.25);
		glVertex2f(-0.06,0.17);
		glColor3f(0.25,0.25,0.25);
		glVertex2f(-0.05,0.16);
	glEnd();
}

void drawSecondTriangleTableBorderCorner(){
	glColor3f(0.75,0.75,0.75);
	glBegin(GL_TRIANGLES);
		glColor3f(0.125,0.125,0.125);
		glVertex2f(-0.02,0.19);
		glColor3f(0.125,0.125,0.125);
		glVertex2f(-0.02,0.18);
		glColor3f(0.25,0.25,0.25);
		glVertex2f(-0.05,0.16);
	glEnd();
}

void drawFirstQuadStripTV(){
	glColor3f(0,1,0);
	glBegin(GL_QUAD_STRIP);
		glVertex2f(-0.27, 0.25);
		glVertex2f(-0.25,0.20);
		glVertex2f(-0.195,0.262);
		glVertex2f(-0.195,0.19);
		glVertex2f(-0.09,0.27);
		glVertex2f(-0.12,0.18);		
	glEnd();
}

void drawFirstLineColumnBorder(){
	glColor3f(1,0.75,0.75);
	glBegin(GL_LINES);
		glVertex2f(0.04,0.15);
		glVertex2f(0.065,0.245);
	glEnd();
}

void drawSecondLineColumnBorder(){
	glColor3f(1,0.75,0.75);
	glBegin(GL_LINES);
		glVertex2f(0.041,0.148);
		glVertex2f(0.066,0.246);
	glEnd();
}

void drawSecondTriangleStripColumn(){
	glColor3f(0.0375,0.125,0.125);
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.55,0.25,0.25);
		glVertex2f(0.14,0.24);
		glColor3f(0.75,0.25,0.25);
		glVertex2f(0.065,0.245);
		glColor3f(0.55,0.25,0.25);
		glVertex2f(0.14,0.14);
		glColor3f(0.85,0.35,0.35);
		glVertex2f(0.04,0.148);
		glColor3f(0.55,0.25,0.25);
		glVertex2f(0.13,0.10);
	glEnd();


}

float tx = 0;
float ty = 0;
int directionX = 1;
int directionY = 1;
void screensaverAnim(int value){
	float posXLimit = 1.4;
	float negXLimit = -2.8;
	float posYLimit = 2.8;
	float negYLimit = -0.7;
	float step = 0.01;
	// switch for x-axis movement
	switch (directionX){
		case 1:
			if (tx + (posXLimit / 10) >= 1){
				directionX *= -1;
			}
		break;
	 case -1:
		if (tx + (negXLimit / 10) <= -1){
				directionX *= -1;
			}
		break;
	}
	tx += step * directionX;
	// switch for y-axis movement
	switch (directionY){
		case 1:
			if (ty + (posYLimit / 10) >= 1){
				directionY *= -1;
			}
		break;
	 case -1:
		if (ty + (negYLimit / 10) <= -1){
				directionY *= -1;
			}
		break;
	}
	ty += step * directionY;
	glutPostRedisplay();
	glutTimerFunc(10,screensaverAnim,1);
}

void drawRamp(float originX, float originY){
	glColor3f(0,0,0);
	// 1
	float lastX = originX;
	float lastY = originY;
	// sometimes needed
	float helperX = 0;
	float helperY = 0;
	
	glBegin(GL_POLYGON);
		glColor3f(0.2,0,0);
		glVertex2f(lastX,lastY);
		glColor3f(0.125,0,0);
		glVertex2f(lastX += 0.02, lastY += 0.01);
		glColor3f(0.2,0,0);
		glVertex2f(lastX += 0.13, lastY += -0.02);
		glColor3f(0.225,0,0);
		glVertex2f(lastX += -0.04, lastY += -0.01);
		// with these we can calculate 2
		helperX = lastX;
		helperY = lastY;
	glEnd();

	// with the origins, lastX&Y we can calculate 4
	// 4
	glBegin(GL_POLYGON);
		glColor3f(0.225,0,0);
		glVertex2f(lastX,lastY);
		glColor3f(0.15,0,0);
		glVertex2f(lastX += -0.0155, lastY += -0.01);
		glColor3f(0.125,0,0);
		glVertex2f(lastX += -0.09, lastY += 0.01);
		glColor3f(0.2,0,0);
		glVertex2f(originX, originY);
	glEnd();

	// 2
	glBegin(GL_POLYGON);
		glColor3f(0.225,0,0);
		glVertex2f(lastX = helperX, lastY = helperY);
		glColor3f(0.2,0,0);
		glVertex2f(lastX += 0.04, lastY += 0.01 );
		glColor3f(0.5,0,0);
		glVertex2f(lastX += -0.11, lastY += -0.07);
		// for 3 and 5
		helperX = lastX;
		helperY = lastY;
		glColor3f(0.625,0,0);
		glVertex2f(lastX += -0.04, lastY += -0.01);
	glEnd();

	// 5
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
		glColor3f(0.5,0,0);
		glVertex2f(lastX = helperX, lastY = helperY);
		glColor3f(0.2,0,0);
		glVertex2f(lastX += 0.11, lastY += 0.07);
		glColor3f(0.175,0,0);
		glVertex2f(lastX, lastY += -0.02);
		glColor3f(0.45,0,0);
		glVertex2f(lastX += -0.08, lastY += -0.0575);
	glEnd();

	// 3
	glBegin(GL_POLYGON);
		glColor3f(0.5,0,0);
		glVertex2f(lastX = helperX, lastY = helperY);
		glColor3f(0.75,0,0);
		glVertex2f(lastX += 0.16, lastY += -0.01);
		glColor3f(0.875,0,0);
		glVertex2f(lastX += -0.03, lastY += -0.02);
		glColor3f(0.625,0,0);
		glVertex2f(lastX += -0.17, lastY += 0.02);
		helperX = lastX;
		helperY = lastY;
	glEnd();

	// 6
	glBegin(GL_POLYGON);
		glColor3f(0.675,0,0);
		glVertex2f(lastX = helperX, lastY = helperY);
		glColor3f(0.75,0,0);
		glVertex2f(lastX += 0.17, lastY += -0.02);
		helperX = lastX;
		helperY = lastY;
		glColor3f(0.625,0,0);
		glVertex2f(lastX, lastY += -0.02);
		glColor3f(0.675,0,0);
		glVertex2f(lastX += -0.17, lastY += 0.02);
	glEnd();

	// 7
	glColor3f(0.5,0,0.5);
	glBegin(GL_POLYGON);
		glColor3f(0.75,0,0);
		glVertex2f(lastX = helperX, lastY = helperY);
		glColor3f(0.625,0,0);
		glVertex2f(lastX += 0.03, lastY += 0.02);
		glColor3f(0.625,0,0);
		glVertex2f(lastX, lastY += -0.02);
		glColor3f(0.75,0,0);
		glVertex2f(lastX += -0.03, lastY += -0.02);
	glEnd();

}

int directionA = -1;
int directionB = 1;
int collisionSelector = 3;
int checkHelper = 1;
int yAxisHelperCounter = 0;
void moveCube(int value){
	float posXLimit = 0.35;
	float negXLimit = 0.32;

	float collisionPointsX[4] = {0.05, 0.26, 0.05, 0.34};
	float collisionPointsY[4] = {0, -0.03, -0.17, -0.21};

	// set to the last, as we start from the bottom border

	float step = 0.01;
	float distanceX = ( collisionPointsX[collisionSelector] - collisionPointsX[collisionSelector - checkHelper] ) * 100 ;
	float distanceY = ( collisionPointsY[collisionSelector] - collisionPointsY[collisionSelector - checkHelper] ) * 100;
	int altitudeChangeSteps = ceil((distanceX / distanceY));
	if (altitudeChangeSteps < 0) {
		altitudeChangeSteps *= -1;
	}
	yAxisHelperCounter += 1;

	if (yAxisHelperCounter >= altitudeChangeSteps) {
		yAxisHelperCounter = 0;
		ty += step * directionB;
	}
	
	if (collisionSelector - checkHelper < 0 || collisionSelector - checkHelper > 3) {
		checkHelper *= -1;
		directionB *= -1;
	}
	switch (directionA){
		case 1:
			if (tx + posXLimit >= collisionPointsX[collisionSelector - checkHelper]){
				directionA *= -1;
				collisionSelector -= checkHelper;
			}
		break;
	 case -1:
		if (tx + negXLimit <= collisionPointsX[collisionSelector - checkHelper]){
				directionA *= -1;
				collisionSelector -= checkHelper;
			}
		break;
	}
	tx += step * directionA;
	// fot the y axis
	/*
	switch (directionB){
		case 1:
			if (ty >= ( collisionPointsY[collisionSelector - checkHelper] - collisionPointsY[collisionSelector] ) ){
				directionB *= -1;
				
			}
		break;
	 case -1:
		if (ty <= ( collisionPointsY[collisionSelector - checkHelper] - collisionPointsY[collisionSelector]) ){
				directionB *= -1;
			}
		break;
	}*/
	glutPostRedisplay();
	glutTimerFunc(10,moveCube,1);
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	// below is the dvd screensaver animation code
	/*
	glLoadIdentity();
	showAxis();
	glTranslatef(tx,ty,0);
	drawSecondPolygonLeftTableBorder();
	drawFirstTriangleStripFirstTablePart();
	drawFirstQuadSecondTablePart();
	drawSecondQuadSecondTablePart();
	drawSecondQuadStripThirdTablePart();
	drawFirstPolygonRightTableBorder();

	drawSecondTriangleStripColumn();
	drawFirstLineColumnBorder();
	drawSecondLineColumnBorder();
	drawFirstQuadStripTV();
	drawFirstTriangleTableBorderCorner();
	drawSecondTriangleTableBorderCorner();*/
	
	// below is the old code for the table+cube demo
	//drawTable();
	//drawCube(-0.05,0.3,1,0,0,1,0);
	glPushMatrix();
		glScalef(2,2,1);
		drawRamp(0,0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(tx,ty,0);
		glPushMatrix();
			glTranslatef(0.32,-0.21,1);
			drawCube(0,0,1,0,1,0,0.25);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		
	glPopMatrix();

	showAxis();
	glFlush();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1152,648);
	glViewport( 0, 0, 1152, 648 );
	glutInitWindowPosition(100,200);
	glutCreateWindow("h0nk");

	inicializar();

	glutDisplayFunc(render);
	//glutTimerFunc(100,screensaverAnim,1);
	glutTimerFunc(100,moveCube,1);
	glutMainLoop();

	return 0;
}
