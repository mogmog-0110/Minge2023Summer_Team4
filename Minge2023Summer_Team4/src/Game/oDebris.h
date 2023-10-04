#pragma once
#include "oGameObject.h"
#include "../Define.h"


class Debris :
    public GameObject
{
private:
protected:
public:

	Debris(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_)
		: GameObject(eObjectType::eDebris, hp_, damage_, textureStr, hitbox_, pos_, vel_, { 0,0 })
	{
		changeCoolTime(0.1s);
		repullDecayRate = 0.5;
	};

	Debris(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_)
		: GameObject(eObjectType::eDebris, hp_, damage_, textureStr,hitbox_,pos_, vel_, acc_)
	{
		changeCoolTime(0.1s);
	};

	~Debris();

	bool isDead(Vec2 playerPos_ = {0,0}) {
		if (hp <= 0) return true;
		if ((pos - playerPos_).length() > 3000) return true;
		else return false;
	}
};

