#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ParticlesEngineClass.h"
#include "SceneObject.hpp"
#include "Weapon.h"
#include "MachineGun.h"
#include "Laser.h"
#include "Bullets.h"

class SpaceShip : public SceneObject
{
public:
	SpaceShip();
	~SpaceShip();
	int list_id;

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void moveBackward();
	void moveForward();
	std::vector< std::vector<float>> getVertexArr();

	float posX;
	float posY;
	float posZ;

	float boundaryX;
	float boundaryY;

	void setWeapon(Weapon* weapon_);
	Weapon* getWeapon() const;
	void changeWeapon(Weapon* weapon_);
	void reload();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();
	void getSpaceShipPosition();

private:
	float speed_;
	float life_;
	float armor_;

	GLuint textureName_;

	std::shared_ptr<ParticlesEngineClass> particles_ptr;
	std::vector< std::vector<float>> vertexArray_;
	Weapon* weapon;

};

