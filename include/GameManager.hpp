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
#include "Sphere.h"


class GameManager : public SceneObject
{
public:
	GameManager();
	~GameManager();

	int count = 0;
	int score_ = 0;


	std::shared_ptr<Camera> getCam();
	std::shared_ptr<SpaceShip> getSpaceShip();
	std::shared_ptr<Enemy> getEnemy();
	std::shared_ptr<Skybox> getSkybox();

	std::vector< std::shared_ptr<Bullet> > bulletsArr_;
	std::vector< std::shared_ptr<Bullet> > enemyBulletsArr_;

	void addEnemies();
	void weaponFire();
	void enemyFire(std::shared_ptr<Enemy> enemy_);

	void setCurrentTime(float time);

	bool findCollSpaceShipVsEnemy(std::shared_ptr<SpaceShip> spaceship, std::shared_ptr<Enemy> enemy);
	bool findCollEnemyVsBullets(std::shared_ptr<Enemy> enemy, std::shared_ptr<Bullet> bullets);
	bool findCollSpaceShipVsBullets(std::shared_ptr<SpaceShip> spaceship, std::shared_ptr<Bullet> bullets);
	//bool findCollAmmoVsBullets(std::shared_ptr<AmmoGun> ammo, std::shared_ptr<Bullets> bullets);

	void handleCollEnemyVsBullets(std::vector <std::shared_ptr<Bullet>> bulletsArr, std::vector <std::shared_ptr<Enemy>> enemyArr);
	//void handleCollAmmoVsBullets(std::shared_ptr<AmmoGun> ammo, std::vector<std::shared_ptr<Bullets>> bulletsArr);
	void handleCollSpaceshipVsBullets(std::shared_ptr<SpaceShip> spaceship, std::vector<std::shared_ptr<Bullet>> bulletsArr);



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
	std::shared_ptr<Sphere> sphere_;

	std::vector <std::shared_ptr<Enemy>> enemyArr_;
	std::vector <std::shared_ptr<Enemy>> attackingEnemyArr_;

	const int battlefieldWidth_ = 32;
	const int battlefieldHeight_ = 0;
	const int battlefieldDepth_ = 512;

	int enemyCounter_ = 0;


	void Shoot();

	float currentTime;
	float nextEnemy;
	int secondsForEnemy = 5;
	int nextScoreUpdate;
	float nextShooting;
	const float secondsForShooting = 0.2f;
	float nextShootingSpaceshipMashineGune;
	const float secondsForShootingSpaceshipMashineGune = 0.1f;
	float nextShootingSpaceshipLaser;
	const float secondsForShootingSpaceshipLaser = 0.05f;

};

