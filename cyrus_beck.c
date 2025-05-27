/******************************************************************************************************************
Name: Dhruba Saha
Program: Write a program in C to implement Cyrus-Beck algorithm.
Program No. 014
Date: 2023-04-29
*******************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define XMIN -50
#define YMIN -50
#define XMAX 50
#define YMAX 50

char title[] = "Cyrus-Beck Algorithm";
int winWidth = 1000;
int winHeight = 1000;
int range_x1 = -500;
int range_x2 = 500;
int range_y1 = -500;
int range_y2 = 500;

typedef struct
{
    float x, y;
} point;

typedef struct
{
    point p1, p2;
} line;

point P, N;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, winWidth, 0, winHeight);
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

float dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

point subtract(point a, point b)
{
    point c = {a.x - b.x, a.y - b.y};
    return c;
}

point add(point a, point b)
{
    point c = {a.x + b.x, a.y + b.y};
    return c;
}

point scale(float c, point a)
{
    point b = {c * a.x, c * a.y};
    return b;
}

void cyrus_beck(line l)
{
    point D = subtract(l.p2, l.p1);
    float t0 = 0, t1 = 1;
    float numerator, denominator;

    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            N = (point){-1, 0};
            P = (point){XMIN, YMIN};
            break;
        case 1:
            N = (point){1, 0};
            P = (point){XMAX, YMIN};
            break;
        case 2:
            N = (point){0, -1};
            P = (point){XMIN, YMIN};
            break;
        case 3:
            N = (point){0, 1};
            P = (point){XMIN, YMAX};
            break;
        }

        numerator = dot(subtract(P, l.p1), N);
        denominator = dot(D, N);

        if (denominator == 0)
        {
            if (numerator < 0)
            {
                return;
            }
        }
        else
        {
            float t = numerator / denominator;
            if (denominator < 0)
            {
                if (t > t1)
                {
                    return;
                }
                else if (t > t0)
                {
                    t0 = t;
                }
            }
            else
            {
                if (t < t0)
                {
                    return;
                }
                else if (t < t1)
                {
                    t1 = t;
                }
            }
        }
    }

    point clipped_p1 = add(l.p1, scale(t0, D));
    point clipped_p2 = add(l.p1, scale(t1, D));
    glBegin(GL_LINES);
    glVertex2f(clipped_p1.x, clipped_p1.y);
    glVertex2f(clipped_p2.x, clipped_p2.y);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(XMIN, YMIN);
    glVertex2f(XMAX, YMIN);
    glVertex2f(XMAX, YMAX);
    glVertex2f(XMIN, YMAX);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    line l1 = {{-50, -70}, {70, 50}};
    line l2 = {{-70, -50}, {50, 70}};
    cyrus_beck(l1);
    cyrus_beck(l2);

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
