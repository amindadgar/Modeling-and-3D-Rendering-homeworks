/*
    Shader based Ping Pong game
    By seyed mohammad Amin Dadgar
    Wed 22, Dec 2021

*/
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "initFunctions.h"


static char * ReadShaderSource(char * ShaderFile);
GLuint init_shader_program(char * vShaderFile, char * fShaderFile);
void init();
void display_objects(int info);


#define MAX_WINDOW_WIDTH 640
#define MAX_WINDOW_HEGHT 480



// to enable debugging assign any number rather than zero to this in the main function
// variable from initFunctions.c
extern int DEBUG;

// to change the speed of the game ( changing game difficulty )
// variable from initFunctions.c
extern int GAME_SPEED;


// initialize the name of shader files
char VERTEX_SHADER[13] = "vshader.glsl";
char FRAGMENT_SHADER[13] = "fshader.glsl";


// this variable is an exported variable from initFunctions.c 
extern float BALL_POSITION[15][2];

void init_shaders();
void keyboardCallbackFunction(unsigned char key, int x, int y);


int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(MAX_WINDOW_WIDTH, MAX_WINDOW_HEGHT);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Shader based Ping Pong");
    init();

    init_shaders();
    glutKeyboardFunc(keyboardCallbackFunction);

    glutMainLoop();
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

void init(){
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

}

void init_shaders(){
    glewInit();


    //set the color for clearing the display
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glPointSize(2); // set the point size

    // Creating a program object containing shader files
    GLuint program;
    program = init_shader_program(VERTEX_SHADER, FRAGMENT_SHADER);
    glUseProgram(program);

    //Creating a buffer object containing vertices data
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BALL_POSITION), BALL_POSITION, GL_STATIC_DRAW);


    //Make a conncetion between data in object buffer and "vPosition in vertex shader
    GLuint location = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);

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


static char * ReadShaderSource(char * ShaderFile){
/*
    just read the shader file and return it as an array of char
    This function is taken from course-examples example4

*/

    FILE *fp;
    fp = fopen(ShaderFile, "rt");
    if (!fp) return NULL;
    long size = 0;

    while (!feof(fp)){
        fgetc(fp);
        size++;
    }

    size--;//EOF should not be counted
    fseek(fp, 0, SEEK_SET);
    char * buf = new char[size + 1];
    fread(buf, 1, size, fp);
    buf[size] = 0;// string is NULL terminated
    fclose(fp);
    return buf;
}


GLuint init_shader_program(char * vShaderFile, char * fShaderFile){
    /*
        compile and attach the shader program
        This function is taken from course-examples example4
    */

    char * svs, *sfs;
    GLuint program, VertexShader, FragmentShader;
    program = glCreateProgram();
    VertexShader = glCreateShader(GL_VERTEX_SHADER);


    svs = ReadShaderSource(vShaderFile);

    glShaderSource(VertexShader, 1, (const GLchar **)&svs, NULL);
    glCompileShader(VertexShader);
    // reading GLSL compiler error messages for vertex shader
    GLint compiled;
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled){
        printf("/n failed to compile");
        GLint logSize;
        glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &logSize);
        char * logMsg = new char[logSize];
        glGetShaderInfoLog(VertexShader, logSize, NULL, logMsg);
        printf("\n %s", logMsg);
        delete[] logMsg;
        getchar();
        exit(EXIT_FAILURE);
    }


    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    sfs = ReadShaderSource(fShaderFile);
    glShaderSource(FragmentShader, 1, (const GLchar **)&sfs, NULL);
    glCompileShader(FragmentShader);
    // reading GLSL compiler error messages for fragment shader
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled){
        printf("\n failed to compile");
        GLint logSize2;
        glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &logSize2);
        char * logMsg2 = new char[logSize2];

        glGetShaderInfoLog(FragmentShader, logSize2, NULL, logMsg2);
        printf("\n %s", logMsg2);
        delete[] logMsg2;
        getchar();
        exit(EXIT_FAILURE);
    }
    glAttachShader(program, VertexShader);
    glAttachShader(program, FragmentShader);
    glLinkProgram(program);
    // reading GLSL linker error messages for program object
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    
    if (!linked){
        printf("/n failed to link");
        GLint logSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
        char * logMsg = new char[logSize];
        glGetProgramInfoLog(program, logSize, NULL, logMsg);
        printf("\n %s", logMsg);
        delete[] logMsg;
        getchar();
        exit(EXIT_FAILURE);
    }
    return program;
}
