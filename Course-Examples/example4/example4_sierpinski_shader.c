
// fragment shading of sphere model
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
// #include <iostream>
#include "math.h"
// #include "vec2.h"
// #include "mat2.h"
#pragma comment(lib,"glew32.lib")

#include <GL/gl.h>
#define NoP 50000
GLuint InitShader(char *, char *);
void mydisplay();

struct points {
    GLfloat x, y, z;
};
void init();
void Sierpinski(points Num[]);

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//|GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sierpinski 3D");
    glewInit();
    init();
    //glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(mydisplay);
    glutMainLoop();
}
void init()
{
    points Num[NoP];
    Sierpinski(Num);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//set the color for clearing the display
    glPointSize(2); // set the point size
    // Creating a program object containing shader files
    GLuint program;
    program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);
    //Creating a buffer object containing Sirepinski verteces data
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Num), Num, GL_STATIC_DRAW);
    //Make a conncetion between data in object buffer and "vPosition in vertex shader
    GLuint location = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);//BUFFER_OFFSET(0));
}




void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //the clear call will affect the color buffer
    glDrawArrays(GL_POINTS, 0, NoP);//Rendering verteces data
    glFlush(); //Empty all commands buffer, causing all issued commands to be executed as quickly as they are accepted by the actual rendering engine
}
static char * ReadShaderSource(char * ShaderFile){
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
GLuint InitShader(char * vShaderFile, char * fShaderFile){
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
void Sierpinski(points Num[])
{
    int j;
    points Vertices[4] = { { -1.0,
    -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 0.0, 1.0, -1.0 }, { 0.0, 0.0,} };
    Num[0].x = 0;
    Num[0].y = 0;
    Num[0].z = 0;

    for (int i = 1; i<NoP; i++){
        j = rand() % 4;
        Num[i].x = (Vertices[j].x +
        Num[i - 1].x) / 2;
        Num[i].y = (Vertices[j].y +
        Num[i - 1].y) / 2;
        Num[i].z = (Vertices[j].z +
        Num[i - 1].z) / 2;
    }
}
