#pragma once
#include "Enemy.h"

Enemy::Enemy(std::string type, float speed, int xBoundary, float startPos)
{
	this->type_ = type;
	this->speed = speed;
	this->xBoundary_ = xBoundary;
	this->xPos_ = std::abs(xBoundary_ / 2);
	this->startPos_ = startPos * -1;

	privateInit();
}

Enemy::~Enemy()
{
}

std::vector<std::vector<float>> Enemy::getVertexArr()
{
	return vertexArray_;
}

bool Enemy::getEnemyStatus()
{
	return isActive;
}

void Enemy::setWeapon(Weapon * weapon)
{
	this->weapon_ = weapon;
}

Weapon * Enemy::getWeapon() const
{
	return this->weapon_;
}

void Enemy::move()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 5.0f));
}

void Enemy::privateInit()
{
	list_id = glGenLists(1);
	glNewList(list_id, GL_COMPILE);//begin new list

	glColor3f(1.0f, 0.0f, 0.0f);
	float size = 5.0f;

	glBegin(GL_QUADS);
	glNormal3f(5.0f, 5.0f, -512.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, startPos_); vertexArray_.push_back(std::vector<float>{ -size, -size, startPos_ });
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, startPos_);	vertexArray_.push_back(std::vector<float>{ size, -size, startPos_ });
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, startPos_);   vertexArray_.push_back(std::vector<float>{ size, size, startPos_});
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, startPos_);  vertexArray_.push_back(std::vector<float>{ -size, size, startPos_});

	glEnd();

	glEndList();//end new list

	shader.initShaders("../shaders/brick");

}

void Enemy::privateRender()
{
	shader.enable();

	glCallList(list_id);

	shader.disable();
}

void Enemy::privateUpdate()
{
	//move object

	float max_x = xBoundary_;
	float min_x = xBoundary_*-1;

	matrix_ = glm::translate(glm::mat4(), glm::vec3(xPos_, max_y, (speed*0.5f) * z_coord));

	// Z-direction
	z_coord++;

	// X-direction
	if (checkFlag == false) xPos_++;
	else xPos_--;

	if (xPos_ == max_x) checkFlag = true;
	if (xPos_ == min_x) checkFlag = false;
}