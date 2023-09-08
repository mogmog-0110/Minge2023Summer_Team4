#pragma once
#include "oGameObject.h"
class Debris :
    public GameObject
{
private:
protected:
public:
	Debris() : GameObject() {};
	Debris(eObjectType myType, int hp_, int damage_, Vec2 pos_, Vec2 Spd_, Vec2 Acc_) : GameObject(myType, hp_, damage_, pos_, Spd_, Acc_) {};
	~Debris();
	//void draw(Vec2 offset, bool isHitboxDraw) const;
};

