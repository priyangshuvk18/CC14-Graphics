
#include <GL/glut.h>
#include <math.h>

int windowWidth = 600;
int windowHeight = 600;

#define PI 3.14159265

void drawEllipse(float xRadius, float yRadius, float x, float y) {
    float theta;

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++) {
        theta = i * PI / 180;
        glVertex2f(x + xRadius * cos(theta), y + yRadius * sin(theta));
    }
    glEnd();
}

void drawCircle(float radius, float x, float y) {
    float theta;

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++) {
        theta = i * PI / 180;
        glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw outer ellipse
    glColor3f(1.0, 0.0, 0.0);
    drawEllipse(200.0, 300.0, 0.0, 0.0);

    // Draw inner circle
    glColor3f(0.0, 0.0, 1.0);
    drawCircle(100.0, 0.0, 0.0);

    glFlush();
}

void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width/2, width/2, -height/2, height/2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Circle inside Ellipse");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
