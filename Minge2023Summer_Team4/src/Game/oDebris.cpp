#include "oDebris.h"

Debris::~Debris()
{
}

bool Debris::isDead(Vec2 playerPos_) {
	if ((pos - playerPos_).length() > 1800) {
		isItemDropable = false;
		return true;
	}
	else if (hp <= 0) return true;
	else return false;
}
