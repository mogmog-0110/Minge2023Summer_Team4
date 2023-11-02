#pragma once
#include "oGameObject.h"
#include "../Define.h"
#include "oPlayer.h"

class Player;

class Enemy :
	public GameObject
{
private:

	int enemyLevel; // 1～6の範囲
	bool hasBullet;
	double maxHp;

protected:
public:

	Enemy(int hp_, int damage_, String textureStr_,
		  Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(eEnemy, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_)
	{
		calcAndSetExp();
		changeCoolTime(0.01s);
		maxHp = hp;
	};

	~Enemy();

	void move() override;

	void calcAndSetExp();
	int getStrength() const;

	void setHasBullet();
	BulletProperty createBulletProperty();
	void determineLevel();

	Array<Vec2> calculateDirection(int way);

	double bulletDelayElapsed = 0.0;  // 弾の生成遅延時間を計測するための変数
};
