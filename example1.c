#include <GL/glut.h>

void mydisplay();
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Sierpinski example");
    
    // callback function
    glutDisplayFunc(mydisplay);
    glutMainLoop();

}

void mydisplay()
{
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);//set the color for clearing the display
    glClear(GL_COLOR_BUFFER_BIT); //clear color buffer instead of depth or ...
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glFlush(); //empty commands buffers causing commands to be executed quickly
}
