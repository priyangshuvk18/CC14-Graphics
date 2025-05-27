#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int start_x, start_y, end_x, end_y;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int dx = end_x - start_x;
    int dy = end_y - start_y;

    float x_inc, y_inc, steps;

    if(abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }

    x_inc = dx / steps;
    y_inc = dy / steps;

    glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        float x = start_x, y = start_y;
        for(int i = 0; i < steps; i++) {
            glVertex2i(round(x), round(y));
            x += x_inc;
            y += y_inc;
        }
    glEnd();

    glFlush();
}

void reshape(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    printf("Enter the starting point (x1, y1): ");
    scanf("%d %d", &start_x, &start_y);

    printf("Enter the ending point (x2, y2): ");
    scanf("%d %d", &end_x, &end_y);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Line Drawing Algorithm");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
