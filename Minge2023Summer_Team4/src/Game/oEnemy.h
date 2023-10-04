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

	Enemy(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_)
		: GameObject(eObjectType::eEnemy, hp_, damage_, textureStr, hitbox_, pos_, vel_, { 0,0 })
	{
		changeCoolTime(0.1s);

		repullDecayRate = 20;
	};

	Enemy(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_)
		: GameObject(eObjectType::eEnemy, hp_, damage_, textureStr,hitbox_,pos_, vel_, acc_)
	{
		changeCoolTime(0.1s);
		repullDecayRate = 20;

	};

	~Enemy();

	void move() override;
};

