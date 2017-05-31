#include "SpaceShip.hpp"
#include "SOIL.h"
#include <iostream>

SpaceShip::SpaceShip()
{
	this->currentWeaponType = "MachineGun";
	laserAmountBullets = 100;
	mashineGunAmountBullets = 100;
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::moveRight()
{
	matrix_ = glm::translate(matrix_, glm::vec3(5.0f, 0.0f, 0.0f));
}

void SpaceShip::moveLeft()
{
	matrix_ = glm::translate(matrix_, glm::vec3(-5.0f, 0.0f, 0.0f));
}

void SpaceShip::moveUp()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 5.0f, 0.0f));
}

void SpaceShip::moveDown()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -5.0f, 0.0f));
}

void SpaceShip::moveBackward()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 5.0f));
}

void SpaceShip::moveForward()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -5.0f));
}


void SpaceShip::setWeapon(std::string weaponName)
{
	this->currentWeaponType = weaponName;
}

std::string SpaceShip::getWeapon()
{
	return this->currentWeaponType;
}

int SpaceShip::getLaserAmountBullets()
{
	return this->laserAmountBullets;
}

int SpaceShip::getMashineGunAmountBullets()
{
	return this->mashineGunAmountBullets;
}

bool SpaceShip::shoot()
{
	if (currentWeaponType == "MachineGun" && mashineGunAmountBullets > 0)
	{
		mashineGunAmountBullets -= 1;
		return true;
	}

	if (currentWeaponType == "Laser"  && laserAmountBullets > 0)
	{
		laserAmountBullets -= 1;
		return true;
	}

	return false;
}

void SpaceShip::reload()
{
	if (currentWeaponType == "MachineGun")
		mashineGunAmountBullets = 100;

	if (currentWeaponType == "Laser")
		laserAmountBullets = 100;
}

void SpaceShip::privateInit()
{
	list_id = glGenLists(1);
	glNewList(list_id, GL_COMPILE);	//begin new list

	glColor3f(0.0f, 0.0f, 1.0f);
	float size = 5.0f;

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size); vertexArray_.push_back(std::vector<float>{ -size, -size, size});
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size); vertexArray_.push_back(std::vector<float>{size, -size, size});
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size); vertexArray_.push_back(std::vector<float>{ size, size, size});
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size); vertexArray_.push_back(std::vector<float>{-size, size, size});
	glEnd();

	glEndList();//end new list




	//model load
	//const aiScene* spaceShipModel = aiImportFile("../textures/SpaceShip.fbx",aiProcessPreset_TargetRealtime_MaxQuality);

	//texture initiation
	int width, height;
	unsigned char* img = SOIL_load_image("../textures/particle.png", &width, &height, 0, SOIL_LOAD_RGB);//color

	glGenTextures(1, &particleTexture_);
	glBindTexture(GL_TEXTURE_2D, particleTexture_);

	if (!img)
		std::cout << "Not loaded" << sizeof(img) << std::endl;

	if (particleTexture_ == NULL) {

		printf("Error in download '%s'", SOIL_last_result());
	}
	else {
		std::cout << "Texture loaded: " << "size " << sizeof(img) << " height " << height << " width " << width << std::endl;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

		SOIL_free_image_data(img);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	particles_ptr.reset(new ParticlesEngineClass(particleTexture_));
	this->addSubObject(particles_ptr);

	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 10.0f, -5.0f));

}

void SpaceShip::privateRender()
{
	glCallList(list_id);
}

void SpaceShip::privateUpdate()
{
}

void SpaceShip::getSpaceShipPosition()
{
}

