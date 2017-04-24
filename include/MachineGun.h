#pragma once

#include "Weapon.h"

class MachineGun : public Weapon
{

public:
	MachineGun(int ammo) : Weapon("MachineGun", ammo) { }

	float getDamage() const { return 100; }
	int getRange() const { return 50; }

};
