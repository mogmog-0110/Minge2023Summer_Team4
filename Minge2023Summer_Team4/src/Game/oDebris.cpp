#include "oDebris.h"

Debris::Debris()
{
	//for test
	pos = Vec2{ 200,200 };
	hitbox = Circle{ pos,50 };
	Spd = Vec2{ 100,100 };

}

Debris::~Debris()
{
}

