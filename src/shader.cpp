#define _CRT_SECURE_NO_WARNINGS
#include "ShaderTest.h"

//
// Global handles for the currently active program object, with its two shader objects
//
GLuint ProgramObject = 0;
GLuint VertexShaderObject = 0;
GLuint FragmentShaderObject = 0;
GLuint prog;

//
// Get the location of a uniform variable
//
static
GLint getUniLoc(GLuint program, const GLchar *name)
{
	GLint loc;

	loc = glGetUniformLocation(program, name);

	if (loc == -1)
		printf("No such uniform named \"%s\"\n", name);

	printOpenGLError();  // Check for OpenGL errors
	return loc;
}

//
// Print out the information log for a shader object
//
static
void printShaderInfoLog(GLuint shader)
{
	int infologLength = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	printOpenGLError();  // Check for OpenGL errors

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

	printOpenGLError();  // Check for OpenGL errors

	if (infologLength > 0)
	{
		infoLog = (GLchar *)malloc(infologLength);
		if (infoLog == NULL)
		{
			printf("ERROR: Could not allocate InfoLog buffer\n");
			exit(1);
		}
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		printf("Shader InfoLog:\n%s\n\n", infoLog);
		free(infoLog);
	}
	printOpenGLError();  // Check for OpenGL errors
}


//
// Print out the information log for a program object
//
static
void printProgramInfoLog(GLuint program)
{
	int infologLength = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	printOpenGLError();  // Check for OpenGL errors

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);

	printOpenGLError();  // Check for OpenGL errors

	if (infologLength > 0)
	{
		infoLog = (GLchar *)malloc(infologLength);
		if (infoLog == NULL)
		{
			printf("ERROR: Could not allocate InfoLog buffer\n");
			exit(1);
		}
		glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);
		printf("Program InfoLog:\n%s\n\n", infoLog);
		free(infoLog);
	}
	printOpenGLError();  // Check for OpenGL errors
}


static
int shaderSize(char *fileName, EShaderType shaderType)
{
	//
	// Returns the size in bytes of the shader fileName.
	// If an error occurred, it returns -1.
	//
	// File name convention:
	//
	// <fileName>.vert
	// <fileName>.frag
	//
	int fd;
	char name[100];
	int count = -1;

	strcpy(name, fileName);

	switch (shaderType)
	{
	case EVertexShader:
		strcat(name, ".vert");
		break;
	case EFragmentShader:
		strcat(name, ".frag");
		break;
	default:
		printf("ERROR: unknown shader file type\n");
		exit(1);
		break;
	}

	//
	// Open the file, seek to the end to find its length
	//
#ifdef WIN32 /*[*/
	fd = _open(name, _O_RDONLY);
	if (fd != -1)
	{
		count = _lseek(fd, 0, SEEK_END) + 1;
		_close(fd);
	}
#else /*][*/
	fd = open(name, O_RDONLY);
	if (fd != -1)
	{
		count = lseek(fd, 0, SEEK_END) + 1;
		close(fd);
	}
#endif /*]*/

	return count;
}


static
int readShader(char *fileName, EShaderType shaderType, char *shaderText, int size)
{
	//
	// Reads a shader from the supplied file and returns the shader in the
	// arrays passed in. Returns 1 if successful, 0 if an error occurred.
	// The parameter size is an upper limit of the amount of bytes to read.
	// It is ok for it to be too big.
	//
	FILE *fh;
	char name[100];
	int count;

	strcpy(name, fileName);

	switch (shaderType)
	{
	case EVertexShader:
		strcat(name, ".vert");
		break;
	case EFragmentShader:
		strcat(name, ".frag");
		break;
	default:
		printf("ERROR: unknown shader file type\n");
		exit(1);
		break;
	}

	//
	// Open the file
	//
	fh = fopen(name, "r");
	if (!fh)
		return -1;

	//
	// Get the shader from a file.
	//
	fseek(fh, 0, SEEK_SET);
	count = (int)fread(shaderText, 1, size, fh);
	shaderText[count] = '\0';

	if (ferror(fh))
		count = 0;

	fclose(fh);
	return count;
}


/*public*/
int readShaderSource(char *fileName, GLchar **vertexShader, GLchar **fragmentShader)
{
	int vSize, fSize;

	//
	// Allocate memory to hold the source of our shaders.
	//
	vSize = shaderSize(fileName, EVertexShader);
	fSize = shaderSize(fileName, EFragmentShader);

	if ((vSize == -1) || (fSize == -1))
	{
		printf("Cannot determine size of the shader %s\n", fileName);
		return 0;
	}

	*vertexShader = (GLchar *)malloc(vSize);
	*fragmentShader = (GLchar *)malloc(fSize);

	//
	// Read the source code
	//
	if (!readShader(fileName, EVertexShader, *vertexShader, vSize))
	{
		printf("Cannot read the file %s.vert\n", fileName);
		return 0;
	}

	if (!readShader(fileName, EFragmentShader, *fragmentShader, fSize))
	{
		printf("Cannot read the file %s.frag\n", fileName);
		return 0;
	}

	return 1;
}


int installShaders(const GLchar *vertexShader,
	const GLchar *fragmentShader)
{
	GLuint VS, FS;   // handles to objects
	GLint  vertCompiled, fragCompiled;    // status values
	GLint  linked;

	// Create a vertex shader object and a fragment shader object

	VS = glCreateShader(GL_VERTEX_SHADER);
	FS = glCreateShader(GL_FRAGMENT_SHADER);

	// Load source code strings into shaders

	glShaderSource(VS, 1, &vertexShader, NULL);
	glShaderSource(FS, 1, &fragmentShader, NULL);

	// Compile the vertex shader, and print out
	// the compiler log file.

	glCompileShader(VS);
	printOpenGLError();  // Check for OpenGL errors
	glGetShaderiv(VS, GL_COMPILE_STATUS, &vertCompiled);
	printShaderInfoLog(VS);

	// Compile the fragment shader, and print out
	// the compiler log file.

	glCompileShader(FS);
	printOpenGLError();  // Check for OpenGL errors
	glGetShaderiv(FS, GL_COMPILE_STATUS, &fragCompiled);
	printShaderInfoLog(FS);

	if (!vertCompiled || !fragCompiled)
		return 0;

	// Create a program object and attach the two compiled shaders

	prog = glCreateProgram();
	glAttachShader(prog, VS);
	glAttachShader(prog, FS);

	// Link the program object and print out the info log

	glLinkProgram(prog);
	printOpenGLError();  // Check for OpenGL errors
	glGetProgramiv(prog, GL_LINK_STATUS, &linked);
	printProgramInfoLog(prog);

	if (!linked)
		return 0;

	// Install program object as part of current state

	glUseProgram(prog);

	return 1;
}

int initRedShader()
{
	return 1;
}

int initFixedFuncShader()
{
	glUniform3f(getUniLoc(prog, "ObjColor"), 0.0, 1.0, 0.0);
	glUniform3f(getUniLoc(prog, "LightPosition"), 0.0, 1.0, 4.0);

	return 1;
}

int initPhongShader()
{
	glUniform3f(getUniLoc(prog, "ObjColor"), 0.0, 1.0, 0.0);
	glUniform3f(getUniLoc(prog, "LightPosition"), 0.0, 1.0, 4.0);

	return 1;
}

int initBrickShader()
{
	glUniform3f(getUniLoc(prog, "BrickColor"), 1.0, 0.3, 1.0);
	glUniform3f(getUniLoc(prog, "MortarColor"), 0.85, 0.86, 0.84);
	glUniform2f(getUniLoc(prog, "BrickSize"), 0.50, 0.35);
	glUniform2f(getUniLoc(prog, "BrickPct"), 0.90, 0.85);
	glUniform3f(getUniLoc(prog, "LightPosition"), 0.0, 0.0, 4.0);

	return 1;
}
