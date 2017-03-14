#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::privateInit()
{
}

void Enemy::privateRender()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	float size = 5.0f;
	glBegin(GL_QUADS);
	// Near Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);
	glEnd();
}

void Enemy::privateUpdate()
{
}
