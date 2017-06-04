#pragma once
#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "SceneObject.hpp"
#include "Shader1.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>


class Sphere : public SceneObject
{
public:
	Sphere();
	~Sphere();


protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

	glm::vec3 translateVec_;



private:

	Shader myShader;

};