// 3D Rotation with pivot.

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

char title[] = "3D Wireframe Rotation with Manual Matrix Manipulation";
int winWidth = 800;
int winHeight = 600;
float angleX = 0.0;  // Rotation angle around the X-axis
float angleY = 0.0;  // Rotation angle around the Y-axis
float pivotX = 0.0;  // Pivot X coordinate
float pivotY = 0.0;  // Pivot Y coordinate
float pivotZ = 0.0;  // Pivot Z coordinate

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black and opaque
    glEnable(GL_DEPTH_TEST);           // Enable depth testing for z-culling
    glMatrixMode(GL_PROJECTION);       // To operate on Projection matrix
    gluPerspective(45.0, (float)winWidth / (float)winHeight, 0.1, 100.0);
}

// Function to apply manual rotation around a pivot point
void manualRotate(float angleX, float angleY) {
    float radX = angleX * M_PI / 180.0;
    float radY = angleY * M_PI / 180.0;

    // First, translate the pivot point to the origin
    glTranslatef(-pivotX, -pivotY, -pivotZ);

    // Rotation matrix around the X-axis
    GLfloat xRotMatrix[16] = {
        1, 0,         0,          0,
        0, cos(radX), -sin(radX), 0,
        0, sin(radX), cos(radX),  0,
        0, 0,         0,          1
    };

    // Rotation matrix around the Y-axis
    GLfloat yRotMatrix[16] = {
        cos(radY),  0, sin(radY), 0,
        0,          1, 0,         0,
       -sin(radY), 0, cos(radY), 0,
        0,          0, 0,         1
    };

    // Apply the rotation matrices
    glMultMatrixf(xRotMatrix);
    glMultMatrixf(yRotMatrix);

    // Finally, translate back to the original position
    glTranslatef(pivotX, pivotY, pivotZ);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // Reset transformations
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);

    // Apply manual rotation
    manualRotate(angleX, angleY);

    // Draw cube as wireframe
    glColor3f(1.0, 0.5, 0.0); // Orange
    glutWireCube(1.5);

    glutSwapBuffers();
}

// Function to handle key press events
void processNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            angleX += 5.0;
            break;
        case 's':
            angleX -= 5.0;
            break;
        case 'a':
            angleY -= 5.0;
            break;
        case 'd':
            angleY += 5.0;
            break;
    }
    if (angleX >= 360) angleX -= 360;
    if (angleY >= 360) angleY -= 360;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    printf("Enter pivot point coordinates (x y z): ");
    scanf("%f %f %f", &pivotX, &pivotY, &pivotZ);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow(title);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
    return 0;
}
