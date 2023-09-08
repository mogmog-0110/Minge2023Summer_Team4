#pragma once
#include "oGameObject.h"
#include "../Define.h"
class Debris :
    public GameObject
{
private:
protected:
public:
	Debris() : GameObject() {};
	Debris(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 Spd_, Vec2 Acc_) : GameObject(eObjectType::debris, hp_, damage_, textureStr,hitbox_,pos_, Spd_, Acc_) {};
	~Debris();
	//void draw(Vec2 offset, bool isHitboxDraw) const;
};

