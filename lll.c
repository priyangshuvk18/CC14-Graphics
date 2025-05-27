#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define XMIN 100
#define YMIN 100
#define XMAX 400
#define YMAX 400

int x1_user, y1_user, x2_user, y2_user;

// Check if a point is inside the clipping window
int isInside(int x, int y) {
    return (x >= XMIN && x <= XMAX && y >= YMIN && y <= YMAX);
}

// Recursive Midpoint Subdivision algorithm
void midpointClip(int x1, int y1, int x2, int y2) {
    // If both endpoints are inside the clipping window, draw the segment
    if (isInside(x1, y1) && isInside(x2, y2)) {
        glColor3f(1.0, 0.0, 0.0); // Red: visible clipped line
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
        return;
    }

    // Stop recursion if the segment is very small
    if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {
        return;
    }

    int xm = (x1 + x2) / 2;
    int ym = (y1 + y2) / 2;

    // Prevent infinite recursion when midpoint is same as one of the endpoints
    if ((xm == x1 && ym == y1) || (xm == x2 && ym == y2)) {
        return;
    }

    midpointClip(x1, y1, xm, ym);
    midpointClip(xm, ym, x2, y2);
}

// Draw clipping window
void drawClippingWindow() {
    glColor3f(0.0, 1.0, 0.0); // Green: clipping window
    glBegin(GL_LINE_LOOP);
    glVertex2i(XMIN, YMIN);
    glVertex2i(XMAX, YMIN);
    glVertex2i(XMAX, YMAX);
    glVertex2i(XMIN, YMAX);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawClippingWindow();

    // Draw original line in blue
    glColor3f(0.0, 0.0, 1.0); // Blue: original line
    glBegin(GL_LINES);
    glVertex2i(x1_user, y1_user);
    glVertex2i(x2_user, y2_user);
    glEnd();

    // Draw clipped line in red
    midpointClip(x1_user, y1_user, x2_user, y2_user);

    glFlush();
}

// Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

// Main function
int main(int argc, char **argv) {
    printf("Enter coordinates of the line (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1_user, &y1_user, &x2_user, &y2_user);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);  // Changed to match the ortho projection
    glutCreateWindow("Midpoint Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}