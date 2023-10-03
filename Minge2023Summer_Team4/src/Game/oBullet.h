#pragma once
#include "oGameObject.h"
#include "../Define.h"


class Bullet :
    public GameObject
{
private:
protected:
	bool bPlayerBullet = false;
public:

	Bullet(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_)
		: GameObject(eObjectType::eBullet, hp_, damage_, textureStr, hitbox_, pos_, vel_, acc_)
	{
		changeCoolTime(0.1s);
	};

	Bullet(bool isPlayerBullet_, int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_)
		: bPlayerBullet(isPlayerBullet_), GameObject(eObjectType::eBullet, hp_, damage_, textureStr,hitbox_,pos_, vel_, acc_)
	{
		changeCoolTime(0.1s);
	};

	~Bullet();

	//void changeIsPlayerBullet(bool b) { bPlayerBullet = b; };
	bool isPlayerBullet() { return bPlayerBullet; };

};

