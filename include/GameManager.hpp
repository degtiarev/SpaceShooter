#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "SpaceShip.hpp"
#include "Enemy.h"
#include "Camera.hpp"
#include "Bullet.h"
#include "Skybox.h"
#include "Water.h"

class GameManager : public SceneObject
{
public:
	GameManager();
	~GameManager();

	std::shared_ptr<Camera> getCam();
	std::shared_ptr<SpaceShip> getSpaceShip();
	std::shared_ptr<Enemy> getEnemy();
	std::shared_ptr<Skybox> getSkybox();

	std::vector< std::shared_ptr<Bullet> > bulletsArr_;
	std::vector< std::shared_ptr<Bullet> > enemyBulletsArr_;

	void addEnemies();
	void weaponFire();
	void enemyFire(std::shared_ptr<Enemy> enemy_);

	template <typename T1, typename T2, typename T3>

	inline bool findCollisions(T1 obj1, T2 obj2, T3 Depth) {
		return true;
	}

protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

private:
	std::shared_ptr<BattleField> bf1_;
	std::shared_ptr<BattleField> bf2_;
	std::shared_ptr<SpaceShip> spaceship_;
	std::shared_ptr<Enemy> enemy_;
	std::shared_ptr<Camera> cam_;
	std::shared_ptr<Bullet> bullets_;
	std::shared_ptr<Skybox> skybox_;
	std::shared_ptr<Water> water_;

	std::vector <std::shared_ptr<Enemy>> enemyArr_;
	std::vector <std::shared_ptr<Enemy>> attackingEnemyArr_;

	const int battlefieldWidth_ = 32;
	const int battlefieldHeight_ = 0;
	const int battlefieldDepth_ = 512;
};

