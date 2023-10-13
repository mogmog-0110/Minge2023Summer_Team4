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



	static Bullet* createNewObject
	(eObjectType myType_, int hp_, int damage_, String textureStr_,
	Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_, bool isPlayerBullet_);

	static Bullet* createNewObject(ObjectInitData);

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
		return new T(hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_);
	case eBullet:
		return new T(1000, 10, U"", hitbox_, pos_, vel_, acc_);
	case eDebris:
		return new T(hp_, damage_, textureStr_, hitbox_, ObjectAppearanceManager::generateRandomPos(), vel_, acc_);
	}

	// ここで適切なポインタを返さない場合、コンパイルエラーが発生。
	return nullptr;
}

