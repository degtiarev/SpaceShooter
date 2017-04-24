#pragma once

#include "Weapon.h"

class Laser : public Weapon
{

public:
	Laser(int ammo) : Weapon("Laser", ammo) { }

	float getDamage() const { return 100; }
	int getRange() const { return 100; }

};
