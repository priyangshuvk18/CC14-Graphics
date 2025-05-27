#include <GL/glut.h>
#include <math.h>

char title[] = "Circle Intersection";
int winWidth = 1000;
int winHeight = 1000;
int range_x1 = -1000;
int range_x2 = 1000;
int range_y1 = -1000;
int range_y2 = 1000;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, winWidth, 0, winHeight);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void drawAxes(void)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(range_x1, 0.0);
    glVertex2f(range_x2, 0.0);
    glVertex2f(0.0, range_y1);
    glVertex2f(0.0, range_y2);
    glEnd();

    int num_ticks_x = (int)(range_x2 - range_x1);
    GLfloat tick_size_x = 0.1;
    GLfloat tick_spacing_x = (range_x2 - range_x1) / num_ticks_x;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i <= num_ticks_x; i++)
    {
        glVertex2f(range_x1 + i * tick_spacing_x, -tick_size_x);
        glVertex2f(range_x1 + i * tick_spacing_x, tick_size_x);
    }
    glEnd();

    int num_ticks_y = (int)(range_y2 - range_y1);
    GLfloat tick_size_y = 0.1;
    GLfloat tick_spacing_y = (range_y2 - range_y1) / num_ticks_y;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i <= num_ticks_y; i++)
    {
        glVertex2f(-tick_size_y, range_y1 + i * tick_spacing_y);
        glVertex2f(tick_size_y, range_y1 + i * tick_spacing_y);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // draw first circle
    const int num_segments = 360;
    const float radius1 = 100;
    const float x1 = -50;
    const float y1 = 50;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    for (int i = 0; i <= num_segments; ++i)
    {
        float angle = i * 2.0f * M_PI / num_segments;
        glVertex2f(x1 + radius1 * cos(angle), y1 + radius1 * sin(angle));
    }
    glEnd();

    // draw second circle
    const float radius2 = 100;
    const float x2 = 50;
    const float y2 = -50;
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x2, y2);
    for (int i = 0; i <= num_segments; ++i)
    {
        float angle = i * 2.0f * M_PI / num_segments;
        glVertex2f(x2 + radius2 * cos(angle), y2 + radius2 * sin(angle));
    }
    glEnd();

    // fill intersection area
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; ++i)
    {
        float angle = i * 2.0f * M_PI / num_segments;
        float x = x1 + radius1 * cos(angle);
        float y = y1 + radius1 * sin(angle);
        if ((x - x2) * (x - x2) + (y - y2) * (y - y2) <= radius2 * radius2)
        {
            glVertex2f(x, y);
        }
        x = x2 + radius2 * cos(angle);
        y = y2 + radius2 * sin(angle);
        if ((x - x1) * (x - x1) + (y - y1) * (y - y1) <= radius1 * radius1)
        {
            glVertex2f(x, y);
        }
    }
    glEnd();

    glFlush();
}

void reshape(int width, int height)
{
    float aspect_ratio = (range_x2 - range_x1) / (range_y2 - range_y1);

    float cx = (range_x1 + range_x2) / 2.0;
    float cy = (range_y1 + range_y2) / 2.0;

    int size = width < height ? width : height;
    int x = (width - size) / 2;
    int y = (height - size) / 2;
    glViewport(x, y, size, size);

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
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow(title);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
