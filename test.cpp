#include <GL/glut.h>
#include <iostream>
#include <stdio.h>

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

void drawCube(float FCoriginX, float FCoriginY, int size){
	// double = more precision, otherwise it makes the if > 0.2 part fail
	double actualSize = (double) size / 10;
	
	glBegin(GL_POLYGON);
		// front
		glVertex2f(FCoriginX, FCoriginY);
		glVertex2f(FCoriginX + actualSize, FCoriginY);
		glVertex2f(FCoriginX + actualSize, FCoriginY + actualSize);
		glVertex2f(FCoriginX, FCoriginY + actualSize);
		glVertex2f(FCoriginX, FCoriginY);

		// upper bit
		float UBoriginX = FCoriginX;
		float UBoriginY = FCoriginY + actualSize;
		float specialSize;
		if ( actualSize > 0.2) {
			specialSize =  actualSize - 0.2  ;
		}
		else {
			specialSize = 0.05;
		}
		glVertex2f(UBoriginX, UBoriginY);
		glVertex2f(UBoriginX + actualSize, UBoriginY);
		glVertex2f(UBoriginX + actualSize + specialSize, UBoriginY + specialSize);
		glVertex2f(UBoriginX + specialSize, UBoriginY + specialSize);
		glVertex2f(UBoriginX, UBoriginY);

		// side
		float SoriginX = UBoriginX + actualSize + specialSize;
		float SoriginY = UBoriginY + specialSize;
		glVertex2f(SoriginX, SoriginY);
		glVertex2f(SoriginX, SoriginY - actualSize);
		glVertex2f(SoriginX - specialSize, SoriginY - actualSize - specialSize);
		glVertex2f(SoriginX - specialSize, SoriginY - specialSize);
		glVertex2f(SoriginX, SoriginY);
	glEnd();

	

}
void render()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glColor3f(0,255,0);
	glBegin(GL_POLYGON);
	  glColor3f(0.125,0,0);
	  glVertex2f(0,0.5);
	  glColor3f(0.25,0,0);
	  glVertex2f(0.6,0.2);
	  glColor3f(1,0,0);
	  glVertex2f(0,-0.5);
	  glColor3f(0.25,0,0);
	  glVertex2f(-0.6,0.2);
	  glColor3f(1,0,0);
	  glVertex2f(-0.6,0.2);
	glEnd();
	
	glColor3f(0,0,1);
	drawCube(0.15,0.18,1);

	showAxis();
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,200);
	glutCreateWindow("h0nk");

	inicializar();

	glutDisplayFunc(render);

	glutMainLoop();

	return 0;
}
