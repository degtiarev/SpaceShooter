#pragma once
#include <windows.h>
//#include <GL/glew.h> 
//#include <GL/freeglut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include "glm/glm.hpp"
#include <vector>
#include <memory>

class ParticlesClass
{
public:
	ParticlesClass();
	~ParticlesClass();

	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// x gravity
	float	yg;						// y gravity
	float	zg;						// z gravity

};

