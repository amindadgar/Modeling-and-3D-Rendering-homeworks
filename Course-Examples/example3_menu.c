#include <GL/glut.h>
#include <stdio.h>


// Course example
// Creating a simple menu

void init_display();
void my_menu(int id);
void create_menu();
void plot_triangle(double *x,double *y,double *z);

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 640

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Example3 Menus");
    
    init_display();
    // glutDisplayFunc(display_callback_func);
    create_menu();

    glutMainLoop();
}

// initialize display parameters
void init_display(){
    glClearColor(1.0 ,1.0 ,1.0,1.0);
    glColor3b(1.0, 0.0, 1.0);
    glPointSize(1.0);

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

// create a simple menu using two entry
void create_menu(){
    glutCreateMenu(my_menu);
    glutAddMenuEntry("Plot Triangle",1);
    glutAddMenuEntry("Exit",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void my_menu(int id){
    switch (id)
    {
        case 1:
        {
            printf("Plotting Triangle\n");
            double x[2] = {0.8,0.8};
            double y[2] = {0.8,1};
            double z[2] = {1,1};
            plot_triangle(x,y,z);
            break;
        }
        case 2:
            exit(0);
            break;
    }
}
void plot_triangle(double *x,double *y,double *z){
    glBegin(GL_TRIANGLES);
        glVertex2d(x[0],x[1]);
        glVertex2d(y[0],y[1]);
        glVertex2d(z[0],z[1]);
    glEnd();

    glFlush();
}

