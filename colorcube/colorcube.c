/*==========================================================*/
/* ColorCube.c                                              */
/*==========================================================*/
/*                                                          */
/* Rotating cube with color interpolation                   */
/*                                                          */
/* E. Angel, Interactive Computer Graphics                  */
/* A Top-Down Approach with OpenGL, Third Edition           */
/* Addison-Wesley Longman, 2003                             */
/*                                                          */
/* Updated:  Bary W Pollack; March 2005                     */
/*                                                          */
/* Demonstration of use of homogeneous coordinate           */
/* transformations and simple data structure for            */
/* representing the cube from Chapter 4                     */
/*                                                          */
/* Colors are assigned to the vertices                      */
/* Left mouse button control direction of rotation          */
/*                                                          */
/*==========================================================*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>

/*==========================================================*/

GLfloat vertices[][3] = {
    {-1.0, -1.0, -1.0}, { 1.0, -1.0, -1.0}, 
    { 1.0,  1.0, -1.0}, {-1.0,  1.0, -1.0},
    {-1.0, -1.0,  1.0}, { 1.0, -1.0,  1.0}, 
    { 1.0,  1.0,  1.0}, {-1.0,  1.0,  1.0}
};

GLfloat colors[][3] = {
    {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, 
    {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0},
    {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}
};

/*==========================================================*/

void polygon (int a, int b, int c , int d)
{
    /* draw a polygon via list of vertices */
    glBegin (GL_POLYGON);
        glColor3fv (colors[a]);
        glVertex3fv (vertices[a]);
        glColor3fv (colors[b]);
        glVertex3fv (vertices[b]);
        glColor3fv (colors[c]);
        glVertex3fv (vertices[c]);
        glColor3fv (colors[d]);
        glVertex3fv (vertices[d]);
    glEnd ();
}

/*==========================================================*/

void colorcube (void)
{
    /* map vertices to faces */
    polygon (0, 3, 2, 1);
    polygon (2, 3, 7, 6);
    polygon (0, 4, 7, 3);
    polygon (1, 2, 6, 5);
    polygon (4, 5, 6, 7);
    polygon (0, 1, 5, 4);
}

/*==========================================================*/

static GLfloat theta[] = { 0.0, 0.0, 0.0 };
static GLint   axis = 0;

/*==========================================================*/

void display (void)
{
    /* display callback, clear frame buffer and z buffer, 
       rotate cube and draw, swap buffers */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    glRotatef (theta[0], 1.0, 0.0, 0.0);    /* x */
    glRotatef (theta[1], 0.0, 1.0, 0.0);    /* y */
    glRotatef (theta[2], 0.0, 0.0, 1.0);    /* z */

    colorcube ();

    glFlush ();
    glutSwapBuffers ();
}

/*==========================================================*/

void spinCube (void)
{
    /* Idle callback, rotate cube 0.2 degrees about selected axis */
    theta[axis] += 0.2;
    if (theta[axis] > 360.0 )
        theta[axis] -= 360.0;
    glutPostRedisplay ();
}

/*==========================================================*/

void mouse (int btn, int state, int x, int y)
{
    char *sAxis [] = { "X-axis", "Y-axis", "Z-axis" };

    /* mouse callback, selects an axis about which to rotate */
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        axis = (++axis) % 3;
        printf ("Rotate about %s\n", sAxis[axis]);
    }
}

/*==========================================================*/

void myReshape (int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    if (w <= h)
        glOrtho (-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w, 
                             2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho (-2.0 * (GLfloat) w / (GLfloat) h, 
                  2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode (GL_MODELVIEW);
}


/*==========================================================*/

int main (int argc, char **argv)
{
    glutInit (&argc, argv);

    printf ("\nPress left mouse button to change rotation axis\n\n");
    /* need both double buffering and z buffer */
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutCreateWindow ("Color Cube");
    glutReshapeFunc (myReshape);
    glutDisplayFunc (display);
    glutIdleFunc (spinCube);
    glutMouseFunc (mouse);
    glEnable (GL_DEPTH_TEST); /* Enable hidden-surface-removal */

    glutMainLoop ();

    return 0;
}

/*==========================================================*/
