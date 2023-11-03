#pragma once
#include "oGameObject.h"
#include "../Define.h"
# include "oPlayer.h"
# include "oEnemy.h"

class Bullet :
    public GameObject
{
private:

	BulletType bulletType ;
	int level;

	int bulletPhase = 0;
	Vec2 tipPos;//レーザー用

	// Mine用メンバ変数
	int exproRange;

	// Wide用メンバ変数

protected:
public:

	Bullet(eObjectType bulletType, int hp_, int damage_, String textureStr_,
		   Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(bulletType, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_), bulletType(BulletType::Normal)
	{
		changeCoolTime(0.1s);
		setUpAnimation();
	};

	~Bullet();

	void update() override;
	void move() override;


	void onCollisionResponse(int damage);
	void onCollisionResponse(Vec2 RepullPos);
	bool isBulletSelfDamage();

	bool isDead(Vec2 playerPos_);
	void setUpAnimation();


	// getter
	BulletType getBulletType();

	// setter
	void setBulletType(BulletType);
	void setLevel(int);
	void setExproRange(int);
};

