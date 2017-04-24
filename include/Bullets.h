#pragma once
#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Weapon.h"
#include <string>

class Bullets : public SceneObject
{
public:
	Bullets(Weapon* weapon, glm::mat4 position, bool friendly, int depth);
	~Bullets();
	glm::vec3 getPosition();

	int life_;
	std::vector< std::vector<float>> getVertexArr();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	std::string type_;
	glm::vec3 position_;
	bool friendly_;
	int depth_;

	std::vector< std::vector<float>> vertexArray_; //vertex array
};