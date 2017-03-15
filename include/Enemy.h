#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Enemy : public SceneObject
{
public:
	Enemy();
	~Enemy();

	float curentZ = 10;
	float curentY = 10;
	bool isUp = true;

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	float speed_;
	float life_;
	float armor_;
};

