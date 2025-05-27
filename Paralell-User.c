#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float start_x, start_y, end_x, end_y;
int num_of_parallel_lines;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Calculate the slope and y-intercept of the main line
    float slope = (end_y - start_y) / (end_x - start_x);
    float y_intercept = start_y - slope * start_x;

    // Calculate the y-coordinates of the parallel lines
    float y_coordinates[num_of_parallel_lines];
    for(int i=0; i<num_of_parallel_lines; i++)
    {
        y_coordinates[i] = y_intercept + (i+1) * ((end_y - start_y) / (num_of_parallel_lines+1));
    }

    glColor3f(0.0, 0.0, 1.0); // set color to blue

    // Draw the main line
    glBegin(GL_LINES);
    glVertex2f(start_x, start_y);
    glVertex2f(end_x, end_y);
    glEnd();

    // Draw the parallel lines
    glColor3f(1.0, 0.0, 0.0); // set color to red
    for(int i=0; i<num_of_parallel_lines; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(start_x, y_coordinates[i]);
        glVertex2f(end_x, y_coordinates[i]);
        glEnd();
    }

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    printf("Enter start point (x,y) of the line: ");
    scanf("%f %f", &start_x, &start_y);

    printf("Enter end point (x,y) of the line: ");
    scanf("%f %f", &end_x, &end_y);

    printf("Enter the number of parallel lines to draw: ");
    scanf("%d", &num_of_parallel_lines);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Parallel Lines Drawing");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
