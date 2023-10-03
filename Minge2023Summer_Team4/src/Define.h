#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.11
# include "Figure.h"

// シーンの名前
enum class SceneList {
	Title,
	Game,
	Result
};

// 共有するデータ
struct GameData
{
	int something;
};

using App = SceneManager<SceneList, GameData>;

enum eObjectType {
	ePlayer,
	eEnemy,
	eBullet,
	eDebris,
	eNone,
};


// 使い方わからん by Shiggy
struct ObjectInitData
{
	eObjectType myType = eNone;
	int hp = 1;
	int damage = 1;
	String textureStr = U"";
	Figure hitbox = Circle(20);
	Vec2 pos = Vec2{ 0,0 };
	Vec2 vel = Vec2{ 0,0 };
	Vec2 acc = Vec2{ 0,0 };

	bool isPlayerBullet_ = false;

	ObjectInitData(eObjectType myType_) :myType(myType_) {};
};
