#include <GL/glut.h>
#include <stdio.h>
#include "initFunctions.h"


#define MAX_WINDOW_WIDTH 640
#define MAX_WINDOW_HEGHT 480


// to enable debugging assign any number rather than zero to this in the main function
// variable from initFunctions.c
extern int DEBUG;

// to change the speed of the game ( changing game difficulty )
// variable from initFunctions.c
extern int GAME_SPEED;


void display_objects(int info);
void init_display();
void keyboardCallbackFunction(unsigned char key, int x, int y);

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(MAX_WINDOW_WIDTH, MAX_WINDOW_HEGHT);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Ping Pong");

    /* if you want to enable debugging uncomment the code below */
    // DEBUG = 1;
    
    init_display();
    glutKeyboardFunc(keyboardCallbackFunction);

    glutMainLoop();

}

void init_display(){
    /*
        initialize the display
        remove colors and make a white background
        
    */

   // set background to white
   // and remove the color buffer
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);

    create_menu( (char *)"Quit", (char *)"Reset Game", (char *)"Game Level");
    

    // Run the game using glutTimer callback function
    glutTimerFunc(20, display_objects, 0);

}

void display_objects(int info){

    /*
        display the objects with their moving position
    */
    glClear(GL_COLOR_BUFFER_BIT);

    display_game_window();
    display_squares();
    display_ball();
    print_scores();


    glFlush();
    glutTimerFunc(30 / GAME_SPEED, display_objects, 0);

}

void keyboardCallbackFunction(unsigned char key, int x, int y){
    /*
        keyboardCallbackFunction
        change each player's square position 
        player1 using 8,and 5
        player2 using w and s
    */

   switch (key){
       case '8':
            // player 1 and move up
            change_player_position(1, 1);
            break;

        case '5':
            // player 1 and move down
            change_player_position(1, -1);
            break;

        case 'w':
            // player 2 and move up
            change_player_position(2, 1);
            break;

        case 's':
            // player 2 and move down
            change_player_position(2, -1);
            break;
            
        default:
            break;
   }
    

   
}