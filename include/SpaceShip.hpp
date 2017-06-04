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
#include "Model.h"

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

	glm::vec3 getPos() const;
	float getRadius() const;


	void reload();
	void setWeapon(std::string weaponName);
	std::string getCurrentWeapon();
	int getLaserAmountBullets();
	int getMashineGunAmountBullets();
	bool shoot();

	float getLife();
	float getArmor();

	void setLife(float damage);
	void setArmor(float damage);


	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;

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
	std::string currentWeaponType;

	std::shared_ptr<ParticlesEngineClass> particles_ptr;
	GLuint particleTexture_;

	std::vector< std::vector<float>> vertexArray_;

	int laserAmountBullets;
	int mashineGunAmountBullets;

	std::shared_ptr< Model> myModel;

};

