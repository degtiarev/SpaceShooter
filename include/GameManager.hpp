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
#include "Bullets.h"

class GameManager : public SceneObject
{
public:
	GameManager();
	~GameManager();

	std::shared_ptr<Camera> getCam();
	std::shared_ptr<SpaceShip> getSpaceShip();
	std::shared_ptr<Enemy> getEnemy();

	void addEnemies();
	void weaponFire();
	void enemyFire(std::shared_ptr<Enemy> enemy_);

	template <typename T1, typename T2, typename T3>

	inline bool findCollisions(T1 obj1, T2 obj2, T3 Depth) {

		GLfloat distance;
		float radius1;
		float radius2;

		float xMax1 = 0.0f;
		float xMin1 = 0.0f;

		float yMax1 = 0.0f;
		float yMin1 = 0.0f;

		float xMax2 = 0.0f;
		float xMin2 = 0.0f;

		float yMax2 = 0.0f;
		float yMin2 = 0.0f;

		//float zMax = 0.0f;
		//float zMin = 0.0f;

		auto eps = 1e-5;

		//position for the first object (x,y,z)
		auto object1PosX = obj1->getMatrix()[3].x;
		auto object1PosY = obj1->getMatrix()[3].y;
		auto object1PosZ = obj1->getMatrix()[3].z;

		//position for the second object (x,y,z)
		auto object2PosX = obj2->getMatrix()[3].x;
		auto object2PosY = obj2->getMatrix()[3].y;
		auto object2PosZ = obj2->getMatrix()[3].z;

		std::vector<glm::vec3> vertexArr;

		for (auto& vertex : obj1->getVertexArr()) {

			auto x = vertex[0];
			auto y = vertex[1];
			auto z = vertex[2];

			if (x > xMax1) xMax1 = x;
			if (x < xMin1) xMin1 = x;

			if (y > yMax1) yMax1 = y;
			if (y < yMin1) yMin1 = y;
		}

		for (auto& vertex : obj2->getVertexArr()) {
			auto x = vertex[0];
			auto y = vertex[1];
			auto z = vertex[2];

			if (x > xMax2) xMax2 = x;
			if (x < xMin2) xMin2 = x;

			if (y > yMax2) yMax2 = y;
			if (y < yMin2) yMin2 = y;
		}

		float centX1, centY1, centZ1, centX2, centY2, centZ2;
		if ((xMin1 + xMax1) / 2 < eps) centX1 = 0;
		else centX1 = (xMin1 + xMax1) / 2;

		if ((yMin1 + yMax1) / 2 < eps) centY1 = 0;
		else centY1 = (yMin1 + yMax1) / 2;

		if ((xMin2 + xMax2) / 2 < eps) centX2 = 0;
		else centX2 = (xMin2 + xMax2) / 2;

		if ((yMin2 + yMax2) / 2 < eps) centY2 = 0;
		else centY2 = (yMin2 + yMax2) / 2;

		float distanceX1 = 0.0f;
		float xVarMax1 = std::abs(xMax1) - std::abs(centX1);
		float xVarMin1 = std::abs(xMin1) - std::abs(centX1);

		if (xVarMax1 > xVarMin1) distanceX1 = xVarMax1;
		else distanceX1 = xVarMin1;

		float distanceY1 = 0.0f;
		float yVarMax1 = std::abs(yMax1) - std::abs(centY1);
		float yVarMin1 = std::abs(yMin1) - std::abs(centY1);

		if (yVarMax1 > yVarMin1) distanceY1 = yVarMax1;
		else distanceY1 = yVarMin1;

		if (distanceX1 > distanceY1) radius1 = distanceX1;
		else radius1 = distanceY1;
		/******************************************************************************************/
		float distanceX2 = 0.0f;
		float xVarMax2 = std::abs(xMax2) - std::abs(centX2);
		float xVarMin2 = std::abs(xMin2) - std::abs(centX2);

		if (xVarMax2 > xVarMin2) distanceX2 = xVarMax2;
		else distanceX2 = xVarMin2;

		float distanceY2 = 0.0f;
		float yVarMax2 = std::abs(yMax2) - std::abs(centY2);
		float yVarMin2 = std::abs(yMin2) - std::abs(centY2);

		if (yVarMax2 > yVarMin2) distanceY2 = yVarMax2;
		else distanceY2 = yVarMin2;

		if (distanceX2 > distanceY2) radius2 = distanceX2;
		else radius2 = distanceY2;

		if (object2PosZ < Depth - radius1) 	return false;
	};

protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

private:
	std::shared_ptr<BattleField> bf_;
	std::shared_ptr<SpaceShip> spaceship_;
	std::shared_ptr<Enemy> enemy_;
	std::shared_ptr<Camera> cam_;
	std::shared_ptr<Bullets> bullets_;

	std::vector< std::shared_ptr<Bullets> > bulletsArr_;
	std::vector< std::shared_ptr<Bullets> > enemyBulletsArr_;

	std::vector <std::shared_ptr<Enemy>> enemyArr_;
	std::vector <std::shared_ptr<Enemy>> attackingEnemyArr_;

	const int battlefieldWidth_ = 32;
	const int battlefieldHeight_ = 0;
	const int battlefieldDepth_ = 512;

	int enemyCounter_ = 0;
};

