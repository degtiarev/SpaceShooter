#pragma once
#include "SceneObject.hpp"
#include <string>
class Weapon :public SceneObject
{
public:
	Weapon(std::string name, int ammo);
	virtual ~Weapon();

	int getAmmo();
	void addAmmo();
	std::string getName();

	virtual void shoot();
	virtual float getDamage() const = 0;
	virtual int getRange() const = 0;

protected:
	int				ammo;

private:
	std::string		name;

};

