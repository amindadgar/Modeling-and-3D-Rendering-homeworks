#include <GL/glut.h>
#include <stdio.h>
#include "initFunctions.h"


#define MAX_WINDOW_WIDTH 640
#define MAX_WINDOW_HEGHT 480


// to enable debugging assign any number rather than zero to this in the main function
extern int DEBUG;

// scores for each player
int score[2] = {0, 0};


void display_objects(int info);
void init_display();
void keyboardCallbackFunction(unsigned char key, int x, int y);
void print_scores();

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(MAX_WINDOW_WIDTH, MAX_WINDOW_HEGHT);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Ping Pong");

    /* if you want to enable debugging uncomment the code below */
    // DEBUG = 1;
    
    init_display();
    print_scores();
    glutKeyboardFunc(keyboardCallbackFunction);

    glutMainLoop();

}
void print_scores(){
    /* 
        print scores
    */

    // set the color to blue at first
    glColor3f(0, 0, 1);

    // set the text position
    glRasterPos2d(0,0.9);

    // our scores are between 0 to 9
    // to print numbers we need to sum it with 48 ( See ascii table )
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[0] + 48 );
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '-');

    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[1] + 48);

    // reset Color to default black
    glColor3f(0,0,0);

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
    display_game_window();
    print_scores();


    glFlush();
    glutTimerFunc(20, display_objects, 0);

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