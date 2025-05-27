#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

// initialize
int width = 1000;
int height = 1000;
char title[] = "2D Rotation";
int range_x1 = -10;
int range_x2 = 10;
int range_y1 = -10;
int range_y2 = 10;

// Define the vertices of the triangle
GLfloat vertices[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    2.0f, 0.0f, 0.0f};

// Define the rotation factors
GLfloat angle = 30.0f;

void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    GLfloat c = cos(angle * M_PI / 180.0f);
    GLfloat s = sin(angle * M_PI / 180.0f);
    GLfloat norm = sqrt(x * x + y * y + z * z);
    x /= norm;
    y /= norm;
    z /= norm;

    GLfloat mat[16] = {0};
    mat[0] = x*x*(1-c)+c;
    mat[1] = x*y*(1-c)-z*s;
    mat[2] = x*z*(1-c)+y*s;
    mat[3] = 0;
    mat[4] = y*x*(1-c)+z*s;
    mat[5] = y*y*(1-c)+c;
    mat[6] = y*z*(1-c)-x*s;
    mat[7] = 0;
    mat[8] = x*z*(1-c)-y*s;
    mat[9] = y*z*(1-c)+x*s;
    mat[10] = z*z*(1-c)+c;
    mat[11] = 0;
    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;
    mat[15] = 1;

    glMultMatrixf(mat);
}

// Define the translation factors
GLfloat tx = 2.5;
GLfloat ty = 1.5;

void translate(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    m[12] += m[0] * x + m[4] * y + m[8] * z;
    m[13] += m[1] * x + m[5] * y + m[9] * z;
    m[14] += m[2] * x + m[6] * y + m[10] * z;
    glLoadMatrixf(m);
}

void axis(void)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(range_x1, 0.0); // Draw x-axis
    glVertex2f(range_x2, 0.0);
    glVertex2f(0.0, range_y1); // Draw y-axis
    glVertex2f(0.0, range_y2);
    glEnd();

    // Draw x-axis tick marks
    int num_ticks_x = (int)(range_x2 - range_x1);
    GLfloat tick_size_x = 0.1;
    GLfloat tick_spacing_x = (range_x2 - range_x1) / num_ticks_x;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (register int i = 0; i <= num_ticks_x; i++)
    {
        glVertex2f(range_x1 + i * tick_spacing_x, -tick_size_x);
        glVertex2f(range_x1 + i * tick_spacing_x, tick_size_x);
    }
    glEnd();

    // Draw y-axis tick marks
    int num_ticks_y = (int)(range_y2 - range_y1);
    GLfloat tick_size_y = 0.1;
    GLfloat tick_spacing_y = (range_y2 - range_y1) / num_ticks_y;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (register int i = 0; i <= num_ticks_y; i++)
    {
        glVertex2f(-tick_size_y, range_y1 + i * tick_spacing_y);
        glVertex2f(tick_size_y, range_y1 + i * tick_spacing_y);
    }
    glEnd();
}

void reshape(int width, int height)
{
    // Calculate the aspect ratio of the shape
    float aspect_ratio = (range_x2 - range_x1) / (range_y2 - range_y1);

    // Compute the center of the bounding box
    float cx = (range_x1 + range_x2) / 2.0;
    float cy = (range_y1 + range_y2) / 2.0;

    // Set the viewport to fill the largest square that fits within the window
    int size = width < height ? width : height;
    int x = (width - size) / 2;
    int y = (height - size) / 2;
    glViewport(x, y, size, size);

    // Set the orthographic projection matrix to maintain the aspect ratio of the shape
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect_ratio > 1)
    {
        float left = (range_x1 - cx) * aspect_ratio;
        float right = (range_x2 - cx) * aspect_ratio;
        glOrtho(left, right, range_y1 - cy, range_y2 - cy, -1.0, 1.0);
    }
    else
    {
        float bottom = (range_y1 - cy) / aspect_ratio;
        float top = (range_y2 - cy) / aspect_ratio;
        glOrtho(range_x1 - cx, range_x2 - cx, bottom, top, -1.0, 1.0);
    }

    // Switch back to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(range_x1, range_x2, range_y1, range_y2);
    glViewport(0, 0, width, height);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the window

    // Draw original
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3fv(vertices);
    glVertex3fv(vertices + 3);
    glVertex3fv(vertices + 6);
    glEnd();

    // Draw the second shape
    glPushMatrix();            // Save the current matrix
    rotate(angle, 0.0, 0.0, 0.0); // Translate the shape
    glTranslatef(tx, ty, 0.0); // Translate the shape
    glColor3f(0.0, 1.0, 0.0);  // Set color to green

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3fv(vertices);
    glVertex3fv(vertices + 3);
    glVertex3fv(vertices + 6);
    glEnd();

    glPopMatrix(); // Restore the previous matrix
    axis();        // Draw the x and y axes
    glFlush();     // Render the scene
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(title);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
