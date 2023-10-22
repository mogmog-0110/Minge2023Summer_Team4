#pragma once
#include "oGameObject.h"
#include "../Define.h"
#include "oPlayer.h"

class Player;

class Enemy :
    public GameObject
{
private:
protected:
public:

	Enemy(int hp_, int damage_, String textureStr_,
		  Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(eEnemy, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_)
	{
		calcAndSetExp();
		changeCoolTime(0.1s);
	};

	~Enemy();

	void move() override;

	void calcAndSetExp();
	int getStrength() const;
};

