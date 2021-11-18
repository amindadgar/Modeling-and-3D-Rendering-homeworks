#include <GL/glut.h>
#include <stdio.h>

// This program would draw a triangle using 3 clicks of the left mouse
// Writtern by: Mohammad Amin Dadgar
// Thursday 18 November 2021

void initDisplay();
void displayCallbackFunction();
void set_pointer_positions_zero();
double generate_random();
// int get_array_row_size(GLdouble data[][2]);
// int get_array_column_size(GLdouble data[][2]);
void draw_triangle(GLdouble points_vector[][2]);
int check_array(GLdouble data[][2], double value);
void mouseCallbackFunction(int button, int state, int x, int y);


// Global variables
// with the count of 3 we will display the new triangle
int counter = 0;
// This 3d array would save 3 points of x and y 
GLdouble pointer_positions[3][2] = {{0.0 ,0.0 }, {0.0 ,0.0}, {0.0 ,0.0}};

#define ARRAY_COLUMN_SIZE 2
#define ARRAY_ROW_SIZE 3


int main(int argc, char** argv ){

    // intializing window codes
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Homework #1, Dadgar, Stu_no: 4003624016");
    initDisplay();

    // Register a display callback
    glutDisplayFunc(displayCallbackFunction);
    glutMouseFunc(mouseCallbackFunction);

    glutMainLoop();

}

void initDisplay(){
    printf("initializing the window parameters\n");
    // initialize the window and parameters

    // set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0); 

    // set default color to white
    glColor3f(0.0 ,0.0 ,0.0);
    // set point size to 1
    glPointSize(1.0);

}
void mouseCallbackFunction(int button, int state, int x, int y){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // if there was a click somewhere save it 
        // and by the count of 3 plot a triangle with it
        pointer_positions[counter][0] = x;
        pointer_positions[counter][1] = y;
        counter++; 

        printf("LOG: Mouse click detected. Location: %d,%d\n", x,y);
    }
    if (counter == 3)
    {
        // try different colors for each time drawing!
        double red = generate_random();
        double green = generate_random();
        double blue = generate_random();

        glColor3f(red, green, blue);

        glBegin(GL_TRIANGLES);
            glVertex2dv(pointer_positions[0]);
            glVertex2dv(pointer_positions[1]);
            glVertex2dv(pointer_positions[2]);
        glEnd();

        glFlush();

        // remove the triangle buffer
        set_pointer_positions_zero(); 
        counter = 0;
    }
}
void displayCallbackFunction(){
    printf("Display callback function invoked!\n");  

    // clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // if the pointer_positions array containes 0 ( was not initialized )
    if(check_array(pointer_positions, 0.0) == 1){
        // just draw a simple
        GLdouble pointer_positions[3][2] = {{-0.5,0}, {0.5,0}, {0,0.5}}; 
        draw_triangle(pointer_positions);
    }
    else
        draw_triangle(pointer_positions);

    glFlush();

}

// draw triangle using the points_vector
// points_vector must be the size 3 rows and 2 columns
void draw_triangle(GLdouble points_vector[][2]){
    glBegin(GL_TRIANGLES);
        glVertex2dv(points_vector[0]);
        glVertex2dv(points_vector[1]);
        glVertex2dv(points_vector[2]);
    glEnd();
}

// check an array array values equals to value or not 
int check_array(GLdouble data[][2], double value){

    // int rows = get_array_row_size(pointer_positions);
    // int columns = get_array_column_size(pointer_positions);
    int rows = ARRAY_ROW_SIZE;
    int columns = ARRAY_COLUMN_SIZE;


    for(int i=0; i< rows; i++)
        for(int j=0; j<columns; j++)
            if(data[i][j] != value)
                return 0;
    
    // if the array's numbers were equal to value we would return 1 
    return 1;
}
void set_pointer_positions_zero(){

    // int rows = sizeof(pointer_positions) / sizeof(pointer_positions[0]);
    // int columns = sizeof(pointer_positions[0]) - sizeof(pointer_positions[0][0]);

    // int rows = get_array_row_size(pointer_positions);
    // int columns = get_array_column_size(pointer_positions);
    int rows = ARRAY_ROW_SIZE;
    int columns = ARRAY_COLUMN_SIZE;


    for(int i = 0;i < rows;i++)
        for(int j=0; j<columns; j++)
            pointer_positions[i][j] = 0;

}
// int get_array_row_size(GLdouble data[][2]){
//     return sizeof(data) / ARRAY_COLUMN_SIZE;
// }
// int get_array_column_size(GLdouble data[][2]){
//     return sizeof(data[0]) - sizeof(data[0][0]);
// }
double generate_random(){
    return ( (double)rand() / (double)RAND_MAX );
}
