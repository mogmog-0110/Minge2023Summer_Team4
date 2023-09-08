#pragma once
#include "oGameObject.h"
class Debris :
    public GameObject
{
private:
protected:
public:
	Debris() : GameObject() {};
	Debris(Vec2 pos_, Vec2 Spd_) : GameObject(pos_, Spd_) {};
	~Debris();
	//void draw(Vec2 offset, bool isHitboxDraw) const;
};

