#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "SpaceShip.hpp"
#include "Camera.hpp"
#include "Enemy.h"


class GameManager : public SceneObject
{
	public:
		GameManager();
		~GameManager();
    
    std::shared_ptr<Camera> getCam();

  protected:
    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
    std::shared_ptr<BattleField> bf_;
    std::shared_ptr<SpaceShip> spaceship_;
	std::shared_ptr<Enemy> enemy_;
    std::shared_ptr<Camera> cam_;
};

