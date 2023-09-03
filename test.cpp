#include <special-files/include/GL/glut.h>
#include <stdio.h>

void inicializar()
{
    glClearColor(1.0,1.0,0.0,0.0);
}
void graficar()
{
    //printf("hola\n");
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,1,0);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5,-0.2,0.0);
        glVertex3f(-0.1,0.8,0.0);
        glVertex3f(0.5,-0.8,0.0);
    glEnd();

    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,400);
    glutInitWindowPosition(100,200);
    glutCreateWindow("Hola Mundo");

    inicializar();

    glutDisplayFunc(graficar);

    glutMainLoop();

    return 0;
}
