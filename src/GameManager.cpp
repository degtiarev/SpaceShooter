#include "GameManager.hpp"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
	// Set default OpenGL states
	glEnable(GL_CULL_FACE);

	// Adding the camera to the scene
	cam_.reset(new Camera());
	this->addSubObject(cam_);
	//  matrix_.translate(0.0f, 0.0f, -99.0f);
	skybox_.reset(new Skybox(cam_));
	this->addSubObject(skybox_);

	bf_.reset(new BattleField());
	this->addSubObject(bf_);

	spaceship_.reset(new SpaceShip());
	this->addSubObject(spaceship_);

	enemy_.reset(new Enemy("ordinary", 1, battlefieldWidth_, battlefieldDepth_));
	enemy_->setWeapon(new MachineGun(9999));
	attackingEnemyArr_.push_back(enemy_);
	this->addSubObject(enemy_);

}

void GameManager::privateRender()
{
	// Nothing to render
}

void GameManager::privateUpdate()
{
	// Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
	// to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
	this->matrix_ = cam_->getMatrix();

	//bullets remove
	for (int i = 0; i < bulletsArr_.size(); i++)
	{
		if (bulletsArr_.at(i)->life_ == 0)
		{
			this->removeSubObject(bulletsArr_.at(i));
			bulletsArr_.erase(bulletsArr_.begin() + i--);
		}
	}
	//Enemy fire
	for (int i = 0; i < attackingEnemyArr_.size(); i++)
	{
		enemyFire(attackingEnemyArr_.at(i));
	}

	for (int i = 0; i < enemyBulletsArr_.size(); i++)
	{

		if ((enemyBulletsArr_.at(i)->life_ == 0))
		{
			this->removeSubObject(enemyBulletsArr_.at(i));
			enemyBulletsArr_.erase(enemyBulletsArr_.begin() + i--);
		}
		else if (enemyBulletsArr_.at(i)->getPosition().z > battlefieldDepth_)
		{
			this->removeSubObject(enemyBulletsArr_.at(i));
			enemyBulletsArr_.erase(enemyBulletsArr_.begin() + i--);//removing from array
		}
	}

	//Enemy remove
	for (int i = 0; i < enemyArr_.size(); i++)
	{
		auto boundary = enemyArr_.at(i)->getMatrix()[3].z;

		if (boundary > battlefieldDepth_)
		{
			this->removeSubObject(enemyArr_.at(i));
			enemyArr_.erase(enemyArr_.begin() + i--);
		}

		if (findCollisions(spaceship_, enemyArr_.at(i), battlefieldDepth_))
		{
			this->removeSubObject(enemyArr_.at(i));
			enemyArr_.erase(enemyArr_.begin() + i--);
		}

	}

	for (int i = 0; i < attackingEnemyArr_.size(); i++)
	{
		auto boundary = attackingEnemyArr_.at(i)->getMatrix()[3].z;

		if (boundary > battlefieldDepth_)
		{
			this->removeSubObject(attackingEnemyArr_.at(i));
			attackingEnemyArr_.erase(attackingEnemyArr_.begin() + i--);
		}
	}

	for (int i = 0; i < enemyBulletsArr_.size(); i++)
	{
		auto boundary = enemyBulletsArr_.at(i)->getMatrix()[3].z;

		if (boundary > battlefieldDepth_)
		{
			this->removeSubObject(enemyBulletsArr_.at(i));
			enemyBulletsArr_.erase(enemyBulletsArr_.begin() + i--);
		}
	}

}

std::shared_ptr<Camera> GameManager::getCam()
{
	return cam_;
}

std::shared_ptr<SpaceShip> GameManager::getSpaceShip()
{
	return spaceship_;
}

std::shared_ptr<Enemy> GameManager::getEnemy()
{
	return enemy_;
}

std::shared_ptr<Skybox> GameManager::getSkybox()
{
	return skybox_;
}

void GameManager::addEnemies()
{
	//for (int i = 0; i < 50; i++) {

	float speed = static_cast <float> (rand() % 7 + 1);
	int xStartPos = rand() % 32 + 20;
	//random start position
	enemy_ = std::make_shared<Enemy>(*(new Enemy("ordinary", speed, xStartPos, battlefieldDepth_)));

	// Every 2'th enemy has a weapon
	if (enemyCounter_ == 2)
	{
		enemy_->setWeapon(new MachineGun(9999));
		attackingEnemyArr_.push_back(enemy_);
		this->addSubObject(enemy_);
		enemyArr_.push_back(enemy_);
		enemyCounter_ = 0;
	}
	else
	{
		this->addSubObject(enemy_);
		enemyArr_.push_back(enemy_);
		enemyCounter_++;
	}
	//}
}

void GameManager::weaponFire()
{
	auto weapon = spaceship_->getWeapon();

	if (weapon->getAmmo() > 0)
	{
		auto position = spaceship_->getMatrix();

		weapon->shoot();																			// Lower ammo count of weapon
		bullets_ = std::make_shared<Bullets>(*(new Bullets(weapon, position, true, battlefieldDepth_)));		// "Create" bullet

		this->addSubObject(bullets_);														// Add bullets to the scene
		bulletsArr_.push_back(bullets_);
	}
}

void GameManager::enemyFire(std::shared_ptr<Enemy> enemy_)
{
	auto weapon = enemy_->getWeapon();

	if (weapon->getAmmo() > 0)
	{
		auto position = enemy_->getMatrix();

		weapon->shoot();																			// Lower ammo count of weapon
		bullets_ = std::make_shared<Bullets>(*(new Bullets(weapon, position, false, battlefieldDepth_)));		// "Create" bullet

		this->addSubObject(bullets_);														// Add bullets to the scene
		enemyBulletsArr_.push_back(bullets_);
	}

}

