#pragma once
#include "oGameObject.h"
#include "../Define.h"


class Enemy :
    public GameObject
{
private:
protected:
public:

	Enemy(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_)
		: GameObject(eObjectType::eEnemy, hp_, damage_, textureStr, hitbox_, pos_, vel_, { 0,0 }) {};

	Enemy(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_)
		: GameObject(eObjectType::eEnemy, hp_, damage_, textureStr,hitbox_,pos_, vel_, acc_) {};

	~Enemy();

	bool isCollisional(eObjectType eType = eNone);

};

