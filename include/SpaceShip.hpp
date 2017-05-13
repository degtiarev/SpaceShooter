#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ParticlesEngineClass.h"
#include "SceneObject.hpp"
#include "Bullet.h"

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


	void reload();
	void setWeapon(std::string weaponName);
	std::string getWeapon();
	int getLaserAmountBullets();
	int getMashineGunAmountBullets();
	bool shoot();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();
	void getSpaceShipPosition();

private:
	float speed_;

	GLuint textureName_;
	std::string currentWeaponType;


	std::shared_ptr<ParticlesEngineClass> particles_ptr;
	std::vector< std::vector<float>> vertexArray_;

	int laserAmountBullets;
	int mashineGunAmountBullets;

};

