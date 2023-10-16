#pragma once
#include "oGameObject.h"
#include "../Define.h"


class Bullet :
    public GameObject
{
private:
protected:
public:

	Bullet(eObjectType bulletType, int hp_, int damage_, String textureStr_,
		   Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(bulletType, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_)
	{
		changeCoolTime(0.1s);
	};

	~Bullet();

	void move() override;

	bool isDead(Vec2 playerPos_);
};

