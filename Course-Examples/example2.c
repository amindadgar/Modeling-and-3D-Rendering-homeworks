// The Sierpinski example
#include <GL/glut.h>

void myinit();
void display();
void MyMouseFunc(int button, int state, int x, int y);

int main(int argc, char** argv)
{
    /* standard GLUT initialization */
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(512,512); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("Sierpinski Gasket"); /* window title */
    glutDisplayFunc(display);
    /* display callback invoked when window opened */
    myinit(); /* set attributes */

    // Add the mouse callback function
    glutMouseFunc(MyMouseFunc);
    


    glutMainLoop(); /* enter event loop */

}

void myinit()
{
    /* attributes */
    glClearColor(0.0, 0.0, 0.0, 0.0); /* black background */
    glColor3f(1.0, 1.0, 0.0); /* draw in yellow */
    glPointSize(1.0);
}


void display()
{
    GLfloat vertices[3][2]={{-1.0,-1.0},{0.0,1.0},{1.0,-1.0}}; /* A triangle */
    int j, k;
    int rand();
    /* standard random number generator */
    GLfloat p[2] ={0.0,0.0}; /* arbitrary initial point inside triangle */
    glClear(GL_COLOR_BUFFER_BIT); /*clear the window */
    glBegin(GL_POINTS);
    for( k=0; k<5000; k++) /* compute and plot 5000 new points */
    {
    j=rand()%3; /* pick a vertex at random */
    /* compute point halfway between selected vertex and old point */
    p[0] = (p[0]+vertices[j][0])/2.0;
    p[1] = (p[1]+vertices[j][1])/2.0;
    glVertex2fv(p); /* plot new point */
    }
    glEnd();
    
    glFlush(); /* clear buffers */
}

void MyMouseFunc(int button, int state, int x, int y)
{
    if(button== GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    exit(0);
}

