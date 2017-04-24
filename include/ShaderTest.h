#ifndef _SHADER_TEST_H_
#define _SHADER_TEST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#ifdef WIN32 /*[*/
#include <io.h>
#endif /*]*/

//#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

////////////////
// Structures //
////////////////

//
// Shader types
//
typedef enum {
    EVertexShader,
    EFragmentShader,
} EShaderType;


//
// Which models to render
//
typedef enum {
    EModelFirst  = 0,
    EModelCube   = 0,
    EModelTeapot = 1,
    EModelSphere = 2,
    EModelTorus  = 3,
    EModelLast   = 3,
} EModelType;

//////////////////////
// Global variables //
//////////////////////

extern EModelType gleModel;

////////////////
// Prototypes //
////////////////

// draw.c
void drawCube(void);

// shader.c
int readShaderSource(char *fileName, GLchar **vertexShader, GLchar **fragmentShader);
int installBrickShaders(const GLchar *brickVertex, const GLchar *brickFragment);
int installFixedFuncShaders(const GLchar *fixedVertex, const GLchar *fixedFragment);
int installPhongShaders(const GLchar *fixedVertex, const GLchar *fixedFragment);
int installShaders(const GLchar *fixedVertex, const GLchar *fixedFragment);

int initRedShader();
int initFixedFuncShader();
int initPhongShader();
int initBrickShader();

int printOglError(char *file, int line);

#define printOpenGLError() printOglError(__FILE__, __LINE__)

#endif //_SHADER_TEST_H_