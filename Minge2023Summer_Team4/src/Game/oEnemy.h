#pragma once
#include "oGameObject.h"
#include "../Define.h"
#include "oPlayer.h"

class Player;

class Enemy :
	public GameObject
{
private:
	int enemyLevel = 1; // 1～6の範囲
	double maxHp;
	double strength;

	bool isDeadAnimationPlaying;
	int animationFrame;
	int animationDuration;
	int animationSpeed = 10;

protected:
public:
	Enemy(int hp_, int damage_, String textureStr_,
		  Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(eEnemy, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_)
	{
		maxHp = hp;
		strength = maxHp + damage;
		determineLevel();
		calcAndSetExp();
		changeCoolTime(0.01s);
		setUpAnimation();
		setHasBullet();
	};

	~Enemy();

	void move() override;
	void update() override;
	
	void calcAndSetExp();
	double getStrength() const;

	void setHasBullet();
	BulletProperty createBulletProperty();
	void determineLevel();

	Array<Vec2> calculateDirection(int way);

	double bulletDelayElapsed = 0.0;  // 弾の生成遅延時間を計測するための変数
	bool hasBullet;

	void setUpAnimation();
	void updateDirection();
};
