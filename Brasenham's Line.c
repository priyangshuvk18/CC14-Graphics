#include <GL/glut.h>
#include <stdio.h>

int start_x, start_y, end_x, end_y;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int dx = end_x - start_x;
    int dy = end_y - start_y;

    int x_inc = dx > 0 ? 1 : -1;
    int y_inc = dy > 0 ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);

    glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(start_x, start_y);

        int x = start_x, y = start_y;
        int p = 2 * dy - dx;

        while (dx--) {
            if (p >= 0) {
                y += y_inc;
                p -= 2 * dx;
            }
            x += x_inc;
            p += 2 * dy;
            glVertex2i(x, y);
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
    glutCreateWindow("Bresenham's Line Drawing Algorithm");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
