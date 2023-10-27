#pragma once
#include "oGameObject.h"
#include "../Define.h"
# include "oPlayer.h"


class Bullet :
    public GameObject
{
private:

	BulletType bulletType;
	int level;

protected:
public:

	Bullet(eObjectType bulletType, int hp_, int damage_, String textureStr_,
		   Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(bulletType, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_), bulletType(BulletType::Normal)
	{
		changeCoolTime(0.1s);
	};

	~Bullet();

	void update() override;
	void move() override;

	bool isDead(Vec2 playerPos_);


	// getter
	BulletType getBulletType();

	// setter
	void setBulletType(BulletType);
	void setLevel(int);
};

