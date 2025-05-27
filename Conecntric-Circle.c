#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

int windowWidth = 800;
int windowHeight = 800;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    float aspect = (float)windowWidth / (float)windowHeight;
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect > 1.0)
    {
        gluOrtho2D(-aspect, aspect, -1.0, 1.0);
    }
    else
    {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        float x = cos(i * PI / 180);
        float y = sin(i * PI / 180);
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        float x = cos(i * PI / 180) * 0.75;
        float y = sin(i * PI / 180) * 0.75;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        float x = cos(i * PI / 180) * 0.5;
        float y = sin(i * PI / 180) * 0.5;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        float x = cos(i * PI / 180) * 0.25;
        float y = sin(i * PI / 180) * 0.25;
        glVertex2f(x, y);
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Concentric Circles");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
