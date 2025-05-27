#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// initialize
int width = 1000;
int height = 1000;
char title[] = "2D Translation";
int range_x1 = -10;
int range_x2 = 10;
int range_y1 = -10;
int range_y2 = 10;

// Define the shape vertices
GLfloat vertices[][2] = {
    {1.0, 1.0},
    {2.0, 1.0},
    {2.0, 2.0},
    {1.0, 2.0}};

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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw original
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (register int i = 0; i < 4; i++)
    {
        glVertex2fv(vertices[i]);
    }
    glEnd();

    // Draw the transformation
    glPushMatrix();         // Save the current matrix
    translate(tx, ty, 0.0); // Translate the shape
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (register int i = 0; i < 4; i++)
    {
        glVertex2fv(vertices[i]);
    }
    glEnd();

    glPopMatrix(); // Restore the previous matrix
    axis();        // Draw the x and y axes
    glFlush();     // Render the scene
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
