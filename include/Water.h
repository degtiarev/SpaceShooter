#pragma once
#include <windows.h>
#include <iostream>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader1.hpp"
#include "SceneObject.hpp"
#include "Skybox.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SOIL.h"


class Water : public SceneObject
{
public:
	Water(std::shared_ptr<Skybox> skybox_);
	~Water();
protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

	// Get methods
	glm::vec3 getPos() const;
	glm::vec3 getStep() const;

	void createArrays();

private:
	Shader shader_;
	//Shader shaderOutside_;

	std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
	std::vector<unsigned int> indexArray_;
	std::vector<glm::vec2 > textureArray_;

	std::shared_ptr<Skybox> skybox_;
	GLuint waterTexture_;

	glm::vec3 step_;
	glm::vec3 pos_;

	int width_;
	int length_;

	float waveTime_;
	float waveFreq_;
	float waveHeight_;
	float waveWidth_;

	void shaderRender(std::shared_ptr<Skybox> skybox, std::vector<unsigned int> indexArray);



};