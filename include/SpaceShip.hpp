#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SceneObject.hpp"

class SpaceShip : public SceneObject
{
public:
	SpaceShip();
	~SpaceShip();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	float speed_;
	float life_;
	float armor_;

};

