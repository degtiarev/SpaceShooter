#include "Bullet.h"

Bullet::Bullet(std::string type, glm::mat4 position, bool friendly, int depth)
{
	this->type_ = type;
	if (type_ == "MachineGun") life_ = 50;
	if (type_ == "Laser") life_ = 200;

	this->position_ = position[3];
	this->friendly_ = friendly;
	this->depth_ = depth;
	privateInit();
}

Bullet::~Bullet()
{
}

glm::vec3 Bullet::getPosition()
{
	return position_;
}

std::vector< std::vector<float>> Bullet::getVertexArr()
{
	return vertexArray_;
}

void Bullet::privateInit()
{
	bullets = glGenLists(1);
	glNewList(bullets, GL_COMPILE);
	createBullets();
	glEndList();
}

void Bullet::privateRender()
{

	glCallList(bullets);
	glFlush();
}

void Bullet::privateUpdate()
{
	if (friendly_ == true)
		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -7.0f));
	else
		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 7.0f));

	life_--;
}

void Bullet::createBullets()
{

	auto x = position_.x;
	auto y = position_.y;
	auto z = position_.z;

	if (friendly_ == false)
		z = -depth_ + position_.z;

	float increment;
	glClearColor(0.0, 0.0, 0.0, 0.0);

	if (type_ == "MachineGun")
	{
		increment = 0.8f;
		glColor3f(1.00, 0.00, 0.00);
	}
	if (type_ == "Laser")
	{
		increment = 0.2f;
		glColor3f(1.00, 1.00, 0.00);
	}

	glBegin(GL_QUADS);
	//glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(x + increment, y + increment, z + increment); vertexArray_.push_back(std::vector<float>{x + increment, y + increment, z + increment});
	glVertex3f(x - increment, y + increment, z + increment); vertexArray_.push_back(std::vector<float>{x - increment, y + increment, z + increment});
	glVertex3f(x - increment, y - increment, z + increment); vertexArray_.push_back(std::vector<float>{x - increment, y - increment, z + increment});
	glVertex3f(x + increment, y - increment, z + increment); vertexArray_.push_back(std::vector<float>{x + increment, y - increment, z + increment});
	glEnd();

}
