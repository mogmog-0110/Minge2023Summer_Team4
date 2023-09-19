#pragma once
#include "oGameObject.h"
#include "../Define.h"


class Bullet :
    public GameObject
{
private:
protected:
	bool isPlayerBullet = false;
public:

	Bullet(bool isPlayerBullet_, int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_)
		: isPlayerBullet(isPlayerBullet_), GameObject(eObjectType::eBullet, hp_, damage_, textureStr, hitbox_, pos_, vel_, { 0,0 }) {};

	Bullet(bool isPlayerBullet_, int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_)
		: isPlayerBullet(isPlayerBullet_), GameObject(eObjectType::eBullet, hp_, damage_, textureStr,hitbox_,pos_, vel_, acc_) {};

	~Bullet();
};

