#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Weapon.h"


class Enemy : public SceneObject
{
public:
	Enemy(std::string type, float speed, int xBoundary, float startPos);
	~Enemy();

	int list_id;

	std::vector< std::vector<float>> getVertexArr();
	GLuint vertexbuffer;
	bool getEnemyStatus();// if enemy status is not active - erase enemy from the scene
	void setWeapon(Weapon* weapon);
	Weapon* getWeapon() const;
	void move();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

	glm::vec3 translateVec_;

private:
	float speed;
	float life;
	float armor;
	bool isActive = true;

	std::string type_;

	Weapon* weapon_;
	float startPos_;

	bool checkFlag = false;
	float max_z = 50.0;
	float min_z = -150.0;
	float max_y = 10.0;
	float min_y = 0.0;

	int z_coord = 0;
	double y_coord = 0.0;

	GLuint textureName_;

	std::vector< std::vector<float>> vertexArray_; //vertex array
	std::vector< glm::vec3 > normalArray_; // normals array
	std::vector< glm::uint > indexArray_;  // index array

	int xBoundary_;
	int xPos_;
};

