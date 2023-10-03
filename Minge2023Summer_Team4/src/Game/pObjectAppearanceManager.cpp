#include "pObjectAppearanceManager.h"

ObjectAppearanceManager::ObjectAppearanceManager()
{
}

ObjectAppearanceManager::~ObjectAppearanceManager()
{
}

Vec2 ObjectAppearanceManager::generateRandomPos()
{
	// プレイヤーの座標を取得
	Player* myPlayer = Player::getInstance();
	Vec2 playerPos = myPlayer->getPos();

	// プレイヤーを中心とした一定の湧き範囲の設定
	Circle circleA{ playerPos, 2000 };

	//ただしこの円内では湧かない
	Circle circleB{ playerPos, 700 };

	Vec2 randomPos;
	while (true)
	{
		// 湧き範囲内のランダムな座標を取得
		randomPos = RandomVec2(circleA);

		//プレイヤーから一定の距離離れていればおけ

		if (!(circleB.intersects(randomPos)))
		{
			break;
		}
	}

	return randomPos;
}

Bullet* ObjectAppearanceManager::createNewObject
(eObjectType myType_, int hp_, int damage_, String textureStr_,
Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_, bool isPlayerBullet_)
{
	switch (myType_)
	{
	case eBullet:
		return new Bullet(isPlayerBullet_, 1000, 10, U"", hitbox_, pos_, vel_, acc_);
	}

	// ここで適切なポインタを返さない場合、コンパイルエラーが発生。
	return nullptr;
}
