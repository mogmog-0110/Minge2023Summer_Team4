#pragma once
# include "../Define.h"
# include "../Figure.h"
# include "oGameObject.h"
# include "oDebris.h"
# include "oBullet.h"
# include "oEnemy.h"
# include "oPlayer.h"

class Player;

class ObjectAppearanceManager
{
private:
	int debugNum = 0;
	Timer testTimer1{ 0.5s,StartImmediately::Yes };

	// シングルトンにするためコンストラクタとでコンストラクタはprivateに
	ObjectAppearanceManager();
	~ObjectAppearanceManager();

public:

	template <typename T>
	static T* createNewObject
	(eObjectType myType_, int hp_, int damage_, String textureStr_,
		Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_);

	static Vec2 generateRandomPos();
};

// テンプレート関数の実装はヘッダーファイル内で行う必要がある。
template <typename T>
T* ObjectAppearanceManager::createNewObject(
	eObjectType myType_, int hp_, int damage_, String textureStr_,
	Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_)
{
	switch (myType_)
	{
	case eEnemy:
		return new T(1000, 10, U"", hitbox_, ObjectAppearanceManager::generateRandomPos(), { 0,0 }, { 0,0 });
	case eBullet:
		return new T(1000, 10, U"", hitbox_, { 0, 200 }, { 0,200 }, { 0,0 });
	case eDebris:
		return new T(1000, 10, U"", hitbox_, ObjectAppearanceManager::generateRandomPos(), { 0,0 }, { 0,0 });
	}

	// ここで適切なポインタを返さない場合、コンパイルエラーが発生。
	return nullptr;
}
