#include "Weapon.h"



Weapon::Weapon(std::string name_, int ammo_)
{
	this->ammo = ammo_;
	this->name = name_;
}


Weapon::~Weapon()
{
}

int Weapon::getAmmo()
{
	return this->ammo;
}

void Weapon::addAmmo()
{
	this->ammo += 10;
}

std::string Weapon::getName()
{
	return this->name;
}

void Weapon::shoot()
{
	this->ammo -= 1;
}
