﻿#pragma once
# include "../Define.h"
# include "../Figure.h"
#include "oGameObject.h"
#include "oDebris.h"
#include "oBullet.h"
#include "oEnemy.h"
#include "oPlayer.h"

class Player;

class ObjectAppearanceManager
{
private:
	int debugNum = 0;
	Timer testTimer1{ 0.5s,StartImmediately::Yes };

	Array<Debris> DebrisQueue = {};
	Array<Bullet> BulletQueue = {};
	Array<Enemy> EnemyQueue = {};

	// シングルトンにするためコンストラクタとでコンストラクタはprivateに
	ObjectAppearanceManager();
	~ObjectAppearanceManager();

public:

	template <typename T>
	static T createNewObject
	(eObjectType myType_, int hp_, int damage_, String textureStr_,
		Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_);

	Vec2 generateRamdomPos();
};
