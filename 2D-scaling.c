#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float triangle[3][2] = {
    {100.0, 100.0},
    {150.0, 200.0},
    {200.0, 100.0}
};

float sx = 1.0, sy = 1.0;
float pivot[2] = {150.0, 150.0};

void drawTriangle(float tri[3][2]) {
    glBegin(GL_TRIANGLES);
    glVertex2fv(tri[0]);
    glVertex2fv(tri[1]);
    glVertex2fv(tri[2]);
    glEnd();
}

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-500, 0);
    glVertex2f(500, 0);
    glVertex2f(0, -500);
    glVertex2f(0, 500);
    glEnd();
}

void drawPivot() {
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2fv(pivot);
    glEnd();
    glPointSize(1.0);
}

void scaleTriangle() {
    float temp[3][2];
    
    for (int i = 0; i < 3; i++) {
        temp[i][0] = triangle[i][0] - pivot[0];
        temp[i][1] = triangle[i][1] - pivot[1];
    }
    
    for (int i = 0; i < 3; i++) {
        temp[i][0] *= sx;
        temp[i][1] *= sy;
    }
    
    for (int i = 0; i < 3; i++) {
        temp[i][0] += pivot[0];
        temp[i][1] += pivot[1];
    }
    
    glColor3f(0.0, 0.0, 1.0);
    drawTriangle(temp);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawAxes();
    
    glColor3f(1.0, 0.0, 0.0);
    drawPivot();
    
    glColor3f(0.0, 1.0, 0.0);
    drawTriangle(triangle);
    
    scaleTriangle();
    
    glFlush();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv) {
    printf("Enter scaling factors (sx and sy): ");
    scanf("%f %f", &sx, &sy);
    
    printf("Enter pivot point coordinates (x y): ");
    scanf("%f %f", &pivot[0], &pivot[1]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Scaling with Pivot Point");
    
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}