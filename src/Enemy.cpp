#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::privateInit()
{
	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 10.0f, -5.0f));
}

void Enemy::privateRender()
{
	glColor3f(0.0f, 0.2f, 0.0f);
	float size = 5.0f;
	glBegin(GL_TRIANGLES);
	// Near Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);

	glEnd();
}

void Enemy::privateUpdate()
{

	if (curentY >= 25)
		isUp = false;

	if (curentY <= 10)
		isUp = true;

	if (isUp)
	{
		curentY += 0.02f;
		//curentZ++;
	}

	else
	{
		curentY -= 0.02f;
		//curentZ--;
	}

	//std::cout << curentY << " " << curentZ << std::endl;

	matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, curentY, -5));
}
