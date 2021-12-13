#include <GL/glut.h>
#include "initFunctions.h"
#include "debuggingFunctions.h"

// define the border value of the window
#define BORDER 0.9

// this is the rate of ball moving
int BALL_ACTION = -1.0;

// the steps for changing ball position
float STEP_X = 0.01;
float STEP_Y = 0.00;

// The rate of changing ball steps
int STEP_CHANGE_RATE = 4;

// default value is zero, DON'T CHANGE THIS VALUE!!!!
// if you want to enable debugging change this in the main.c function
int DEBUG = 0;

// scores of the players
int score[2] = {0, 0};

// change the difficulty of the game by changing its speed
// 1 -> easy, 2 -> medium, 3 -> Hard
int GAME_SPEED = 1;

// id of each menu
#define MENU_EXIT 0
#define MENU_START_OVER 1
#define MENU_LEVEL 2

// level submenu IDs
#define SUBMENU_LEVEL_EASY 3
#define SUBMENU_LEVEL_MEDIUM 4
#define SUBMENU_LEVEL_HARD 5


// the ball initializing position
float BALL_POSITION[15][2] = {
    {-0.03,0.03},
    {-0.04,0.015},
    {-0.045,0},
    {-0.04,-0.015},
    {-0.03,-0.03}, 
    {-0.015,-0.04}, 
    {0,-0.045},
    {0.015,-0.045},
    {0.03,-0.03},
    {0.04,-0.015},
    {0.045,0},
    {0.04,0.015},
    {0.03,0.03},
    {0.015,0.04},
    {0,0.04}
    }; 

 
// the first player position
float PLAYER_ONE_POSIOTION[4][2] = {
    {-0.8, -0.15},
    {-0.8,  0.15},
    {-0.75,  0.15},
    {-0.75, -0.15}
    }; 

// the second player position
float PLAYER_TWO_POSIOTION[4][2] = {
    {0.8, -0.15},
    {0.8,  0.15},
    {0.75,  0.15},
    {0.75, -0.15}
    }; 

void reset_ball_positions(char position){
    /*
        if ball hits the border reset it

        reset and start from the ball from right or left ( 'r' character and 'l' character)
    */
    BALL_POSITION[0][0] = -0.03;
    BALL_POSITION[0][1] = 0.03;

    BALL_POSITION[1][0] = -0.04;
    BALL_POSITION[1][1] = 0.015;

    BALL_POSITION[2][0] = -0.045;
    BALL_POSITION[2][1] = 0;

    BALL_POSITION[3][0] = -0.04;
    BALL_POSITION[3][1] = -0.015;

    BALL_POSITION[4][0] = -0.03;
    BALL_POSITION[4][1] = -0.03;

    BALL_POSITION[5][0] = -0.015;
    BALL_POSITION[5][1] = -0.04;

    BALL_POSITION[6][0] = 0;
    BALL_POSITION[6][1] = -0.045;

    BALL_POSITION[7][0] = 0.015;
    BALL_POSITION[7][1] = -0.045;

    BALL_POSITION[8][0] = 0.03;
    BALL_POSITION[8][1] = -0.03;

    BALL_POSITION[9][0] = 0.04;
    BALL_POSITION[9][1] = -0.015;

    BALL_POSITION[10][0] = 0.045;
    BALL_POSITION[10][1] = 0;

    BALL_POSITION[11][0] = 0.04;
    BALL_POSITION[11][1] = 0.015;

    BALL_POSITION[12][0] = 0.03;
    BALL_POSITION[12][1] = 0.03;

    BALL_POSITION[13][0] = 0.015;
    BALL_POSITION[13][1] = 0.04;

    BALL_POSITION[14][0] = 0;
    BALL_POSITION[14][1] = 0.04;

    // reset the ball action
    BALL_ACTION = -1.0;

    // reset the steps
    if (position == 'r'){
        STEP_X = -0.01;
        STEP_Y = 0.00;
    } else
        STEP_X = 0.01;
        STEP_Y = 0.00;
    
    

}

void reset_player_positions(){
    /*
        reset both player positions 
    */

   // reset first player
    PLAYER_ONE_POSIOTION[0][0] = -0.8;
    PLAYER_ONE_POSIOTION[0][1] = -0.15;

    PLAYER_ONE_POSIOTION[1][0] = -0.8;
    PLAYER_ONE_POSIOTION[1][1] = 0.15;

    PLAYER_ONE_POSIOTION[2][0] = -0.75;
    PLAYER_ONE_POSIOTION[2][1] = 0.15;

    PLAYER_ONE_POSIOTION[3][0] = -0.75;
    PLAYER_ONE_POSIOTION[3][1] = -0.15;

    // reset second player
    PLAYER_TWO_POSIOTION[0][0] = 0.8;
    PLAYER_TWO_POSIOTION[0][1] = -0.15;

    PLAYER_TWO_POSIOTION[1][0] = 0.8;
    PLAYER_TWO_POSIOTION[1][1] = 0.15;

    PLAYER_TWO_POSIOTION[2][0] = 0.75;
    PLAYER_TWO_POSIOTION[2][1] = 0.15;

    PLAYER_TWO_POSIOTION[3][0] = 0.75;
    PLAYER_TWO_POSIOTION[3][1] = -0.15;

}

void reset_scores(){
    /*
        reset the scores of the players
    */
   score[0] = 0;
   score[1] = 0;
}
void change_player_position(int player, int position){
    /*
        player == 1 is player_one
        player == 2 is player_two

        if position > 0 then move up
        else if position < 0 then move down
        */

    switch (player) {
        case 2:
            /* FIRST PLAYER */

            if (position > 0){

                // check the highest y value in player1 that doesn't go beyond the borders
                if (PLAYER_ONE_POSIOTION[1][1] + 0.05 < BORDER)
                {
                    // move all the y positions slightly up
                    PLAYER_ONE_POSIOTION[0][1] += 0.05;
                    PLAYER_ONE_POSIOTION[1][1] += 0.05;
                    PLAYER_ONE_POSIOTION[2][1] += 0.05;
                    PLAYER_ONE_POSIOTION[3][1] += 0.05;
                }

            } else if (position < 0){

                // check the lowest y value in player1 that doesn't go beyond the borders
                if(PLAYER_ONE_POSIOTION[0][1] - 0.05 > -1 * BORDER){
                    // move all the y positions slightly down
                    PLAYER_ONE_POSIOTION[0][1] -= 0.05;
                    PLAYER_ONE_POSIOTION[1][1] -= 0.05;
                    PLAYER_ONE_POSIOTION[2][1] -= 0.05;
                    PLAYER_ONE_POSIOTION[3][1] -= 0.05;
                }
            }
            break;


        case 1:
            /* SECOND PLAYER */

            // check the highest y value in player2 that doesn't go beyond the borders
            if(position > 0){
                if (PLAYER_TWO_POSIOTION[1][1] + 0.05 < BORDER){
                // move all the y positions slightly up
                    PLAYER_TWO_POSIOTION[0][1] += 0.05;
                    PLAYER_TWO_POSIOTION[1][1] += 0.05;
                    PLAYER_TWO_POSIOTION[2][1] += 0.05;
                    PLAYER_TWO_POSIOTION[3][1] += 0.05;
            }

            } else if (position < 0){

                // check the lowest y value in player2 that doesn't go beyond the borders
                if (PLAYER_TWO_POSIOTION[0][1] - 0.05 > -1 * BORDER ){
                        
                    // move all the y positions slightly down
                    PLAYER_TWO_POSIOTION[0][1] -= 0.05;
                    PLAYER_TWO_POSIOTION[1][1] -= 0.05;
                    PLAYER_TWO_POSIOTION[2][1] -= 0.05;
                    PLAYER_TWO_POSIOTION[3][1] -= 0.05;
                }

            }
            break;


        default:
            // print an error and close the program
            print_input_player_error(player);
            exit(1);
            break;
   }
}

void display_squares(){
    /*
        draw the squares for each player
    */

    // make the players color to red
    glColor3f(1,0,0);

    // first player
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i < 4;i++)
            glVertex2fv(PLAYER_ONE_POSIOTION[i]);
    glEnd();

    // second player
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i < 4;i++)
        glVertex2fv(PLAYER_TWO_POSIOTION[i]);
    glEnd();

    // make the color to defualt black
    glColor3f(0,0,0);

}

double compare_float(float value1, float value2){
    /*
        compare value1 and value2 and return the difference in double format
    */
    double data;
    data = value1 - value2;
    
    return data;
}
int change_ball_action( float player_y1, float player_y2,float player_x1, float player_x2,  float ball_x,float ball_y ){
    /*
        if the y of the ball was between the y of the player position ( Also ball x position was between player's x )
        else return the same ball action

        player_y2 > player_y1 ( y2 is the upper bound of the player's square )
        player_x2 > player_x1 ( x2 is the upper bound of the player's square )
    */


    if( ( compare_float(ball_x, player_x2) > 0 && compare_float(ball_x, player_x2) < 0.006) && 
            compare_float(ball_y, player_y1) > 0.005 && compare_float(ball_y, player_y2) <= 0  ){


        // change the way ball is going
        
        // this condition is made to avoid making steps zero
        if( compare_float(ball_y, player_y1 ) > 0.00001 ){
            STEP_Y = -1 * ((player_y1 - ball_y) / 25) * STEP_CHANGE_RATE;
            // STEP_X = -1 * ((player_y1 - ball_y) / 50)* STEP_CHANGE_RATE;
        }
        return BALL_ACTION * -1;

    } else 
        return BALL_ACTION;
}

void check_ball_hit_player(){
    /*
        check weather the ball hits a player or not
        if the ball didn't hit any player, return 0
        else return a number

        check the y of the ball that is between the y of the player's square
    */

   // 15 is the ball vertexes (array) length
//    for (int index = 0; index < 15; index++){
   for (int index = 2; index < 15; index+=8){

       // to check the changes in action
       // if the action was changed, break the loop
       int ball_new_action = BALL_ACTION;

        // If the x of the ball was negative
        // then there's a chance for it to hit the first player 
        if( BALL_POSITION[index][0] < 0){
            // check the first player
            ball_new_action = change_ball_action(PLAYER_ONE_POSIOTION[0][1], PLAYER_ONE_POSIOTION[1][1],
             PLAYER_ONE_POSIOTION[0][0], PLAYER_ONE_POSIOTION[2][0],  BALL_POSITION[index][0], BALL_POSITION[index][1] );

            if( ball_new_action != BALL_ACTION){
                BALL_ACTION = ball_new_action;
                break;
            }
                
        } else {
            // check the second player
            ball_new_action = change_ball_action(PLAYER_TWO_POSIOTION[0][1], PLAYER_TWO_POSIOTION[1][1],
                 PLAYER_TWO_POSIOTION[0][0], PLAYER_TWO_POSIOTION[2][0] , BALL_POSITION[index][0], BALL_POSITION[index][1]);

            if( ball_new_action != BALL_ACTION ){
                BALL_ACTION = ball_new_action;
                break;
            }
        }
   }
} 

void change_ball_position(){
    /*
        change the ball in the way it is going
        index is the index of the ball

        BALL_ACTION  is the rate of how the ball position increasing or decreasing
    */

    for(int index = 0; index < 15; index++){
        // increase ball position each time it is shown
        BALL_POSITION[index][0] += STEP_X * BALL_ACTION;
        BALL_POSITION[index][1] += STEP_Y * BALL_ACTION;
    }

}
int check_ball_hit_upper_bound(int index){
    /*
        check upper bounds if the ball hits it or not

        return 1 if the ball hits the upper or lower bounds
    */
    
    if(BALL_POSITION[index][1] >= BORDER){

        STEP_Y = STEP_Y * -1;
        return 1;

    } else if(BALL_POSITION[index][1] <= -1* BORDER){
        
        STEP_Y = STEP_Y * -1;
        return 1;

    }else
        return 0;
}

char check_round_winner(){
    /*
        check wether player1 wins or not to reset the ball to go right side or left
    */
   if (score[0] >= score[1]){
       return 'r';
   } else 
    return 'l';
   
}

void print_winner_text(char player_num){
    /*
        print the player1 winner or player two text
    */

    glColor3f(1, 0.5, 0);

    // set the text position
    glRasterPos2d(0,0.5);

    // print the string "player 1 won!" or "player 2 won!"
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'p');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, player_num);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'w');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');

    // reset Color to default black
    glColor3f(0,0,0);

    glFlush();

    char winner = check_round_winner();
    reset_ball_positions(winner);
    reset_player_positions();
    reset_scores();
}

void print_drawn_text(){
    /*
        If the scores was equal write drawn on screen
    */

    glColor3f(1, 0.5, 0);

    // set the text position
    glRasterPos2d(0,0.5);

    // print the string "player 1 won!" or "player 2 won!"
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'D');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');

    // reset Color to default black
    glColor3f(0,0,0);

    glFlush();
    char winner = check_round_winner();
    reset_ball_positions(winner);
    reset_player_positions();
    reset_scores();

}

void print_winner(char player){
    /*
        choose which player won
    */
    if( score[0] < score[1]){
        print_winner_text(player);
    } else if(score[1] > score[0]){
        print_winner_text(player);
    } else {
        print_drawn_text();
    }
}

void end_game(char player){
    /*
        If any players score go beyond 9 end the game and restart it

        player is 1 or 2 charactar
    */

   print_winner(player);

}

int check_player_win_lose(int index){
    /*
        check weather the player win or lose the round 

        return 1 if the ball hits the sides
    */
    // if it reach the borders
    if (BALL_POSITION[index][0] >= BORDER){
    
        reset_ball_positions('r');
        reset_ball(DEBUG);
        if (score[1] +1 > 9)
            end_game('1');
        else 
            score[1] += 1;
    
        return 1;

    } else if(BALL_POSITION[index][0] <= -1* BORDER){

        reset_ball_positions('l');
        reset_ball(DEBUG);
 
        if(score[0] + 1 > 9)
            end_game('2');
        else
            score[0] +=1;

        return 1;
    } else 
        return 0;
}

void check_ball_conditions(){
    /*
        check all the conditions 
        ball hits the boundaries or another player

    */

    for(int i=0; i<15; i++){
        if( check_ball_hit_upper_bound(i))
            break;
    }

    for(int i=0; i<15;i++){
        if(check_player_win_lose(i))
            break;
    }

    check_ball_hit_player();


}
void display_ball(){
    /*
        display the ball and move its position
    */
   glColor3f(0.5, 0.5, 0.5);
   glBegin(GL_POLYGON);

   for(int i = 0; i < 15;i++){

        glVertex2f(BALL_POSITION[i][0],
           BALL_POSITION[i][1]);

       print_ball_positions(BALL_POSITION[i][0], BALL_POSITION[i][1], i, DEBUG);
   }
   glEnd();
    
    // check if the conditions
    check_ball_conditions();

    // animate the ball moving
    change_ball_position();

   glColor3f(0, 0.0, 0.0);

}

void display_game_window(){
    /*
        There is a square that the game is happening within it
    */
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1 * BORDER, -1 * BORDER);
        glVertex2f(-1 * BORDER, BORDER);
        glVertex2f(BORDER, BORDER);
        glVertex2f(BORDER, -1 * BORDER);
    glEnd();

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
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[1] + 48 );
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '-');

    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[0] + 48);

    // reset Color to default black
    glColor3f(0,0,0);

}

void menu_callback(int id){
    /*
        Menu callback function
    */
    switch (id)
    {
    case 0:
        exit(0);
        break;
    case 1:
        reset_ball_positions('r');
        reset_player_positions();
        reset_scores();
        break;
    default:
        break;
    }

}
void sub_menu_callback(int id){
    /*
        the submenu for changing the game level to easy/medium/hard
    */
    switch (id)
    {
    case SUBMENU_LEVEL_EASY:
        GAME_SPEED = 1;
        break;
    case SUBMENU_LEVEL_MEDIUM:
        GAME_SPEED = 2;
        break;
    case SUBMENU_LEVEL_HARD:
        GAME_SPEED = 3;
        break;

    default:
        break;
    }
}

void create_menu(char title1[], char title2[], char title3[]){
    /*
        Create the menu
        title1 must be "exit" or other synonyms
        title2 must be "reset game" or other its synonyms
        title3 must be "game level" or other its synonyms

        the conditions above for title is because each menu job is to do the requested works
    */

    // first we create the submenu for it
    int submenu_level = glutCreateMenu(sub_menu_callback);
    glutAddMenuEntry("Easy", SUBMENU_LEVEL_EASY);
    glutAddMenuEntry("Medium", SUBMENU_LEVEL_MEDIUM);
    glutAddMenuEntry("Hard", SUBMENU_LEVEL_HARD);


    glutCreateMenu(menu_callback);
    glutAddMenuEntry(title1, MENU_EXIT);
    glutAddMenuEntry(title2, MENU_START_OVER);
    glutAddSubMenu(title3, submenu_level);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

}
