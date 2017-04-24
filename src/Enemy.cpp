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



				//GLuint VertexArrayID;
				//glGenVertexArrays(1, &VertexArrayID);
				//glBindVertexArray(VertexArrayID);

				////list_id = glGenLists(1);
				////glNewList(list_id, GL_COMPILE);//begin new list
				//static const GLfloat g_vertex_buffer_data[] = {
				//	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
				//	-1.0f,-1.0f, 1.0f,
				//	-1.0f, 1.0f, 1.0f, // triangle 1 : end

				//	1.0f, 1.0f,-1.0f, // triangle 2 : begin
				//	-1.0f,-1.0f,-1.0f,
				//	-1.0f, 1.0f,-1.0f, // triangle 2 : end

				//	1.0f,-1.0f, 1.0f,
				//	-1.0f,-1.0f,-1.0f,
				//	1.0f,-1.0f,-1.0f,

				//	1.0f, 1.0f,-1.0f,
				//	1.0f,-1.0f,-1.0f,
				//	-1.0f,-1.0f,-1.0f,

				//	-1.0f,-1.0f,-1.0f,
				//	-1.0f, 1.0f, 1.0f,
				//	-1.0f, 1.0f,-1.0f,

				//	1.0f,-1.0f, 1.0f,
				//	-1.0f,-1.0f, 1.0f,
				//	-1.0f,-1.0f,-1.0f,

				//	-1.0f, 1.0f, 1.0f,
				//	-1.0f,-1.0f, 1.0f,
				//	1.0f,-1.0f, 1.0f,

				//	1.0f, 1.0f, 1.0f,
				//	1.0f,-1.0f,-1.0f,
				//	1.0f, 1.0f,-1.0f,

				//	1.0f,-1.0f,-1.0f,
				//	1.0f, 1.0f, 1.0f,
				//	1.0f,-1.0f, 1.0f,

				//	1.0f, 1.0f, 1.0f,
				//	1.0f, 1.0f,-1.0f,
				//	-1.0f, 1.0f,-1.0f,

				//	1.0f, 1.0f, 1.0f,
				//	-1.0f, 1.0f,-1.0f,
				//	-1.0f, 1.0f, 1.0f,

				//	1.0f, 1.0f, 1.0f,
				//	-1.0f, 1.0f, 1.0f,
				//	1.0f,-1.0f, 1.0f
				//};
				////glEndList();//end new list

				//glGenBuffers(1, &vertexbuffer);
				//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
				//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

				//matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 5.0f, -5.0f));

}

void Enemy::privateRender()
{
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textureName_);

	glCallList(list_id);

	//glColor3f(1.0f, 1.0f, 0.0f);
	//float size = 5.0f;

	//glBegin(GL_TRIANGLES);
	//glNormal3f(5.0f, 5.0f, -512.0f);

	//glVertex3f(-5.0f, height_, zStart_);
	//glVertex3f(5.0f, height_, zStart_);
	//glVertex3f(5.0f, height_ + 5.0f, zStart_);

	//glEnd();

	//matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 15.0f, z_coord));
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	////
	//glDisableVertexAttribArray(0);

	//glDisable(GL_TEXTURE_2D);

}

void Enemy::privateUpdate()
{
	//move object

	//if (checkFlag == false) {
	//	z_coord -= 1.0;
	//	//y_coord -= 1.0;
	//}
	//if (checkFlag == true) {
	//	z_coord += 1.0;
	//	//y_coord += 1.0;
	//}
	////std::vector<float>pos {x,y,z};
	//if (z_coord <= min_z){ //&& y_coord <= min_y) {
	//	checkFlag = true;
	//}
	//if (z_coord >= max_z){ //&& y_coord >= max_y) {
	//	checkFlag = false;
	//}
	//matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 15.0f, z_coord));
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