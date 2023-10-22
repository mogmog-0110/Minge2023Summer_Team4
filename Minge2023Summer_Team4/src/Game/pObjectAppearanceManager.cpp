#include "pObjectAppearanceManager.h"

ObjectAppearanceManager::ObjectAppearanceManager()
{
}

ObjectAppearanceManager::~ObjectAppearanceManager()
{
}

Vec2 ObjectAppearanceManager::generateRandomPos()
{
	Vec2 playerPos = Player::getInstance()->getPos();

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

GameObject* ObjectAppearanceManager::createNewObject(
	eObjectType myType,
	int hp, int damage, String textureStr,
	Figure hitbox, Vec2 pos, Vec2 vel, Vec2 acc
)
{
	switch (myType) {
	case eEnemy:
		return new Enemy(hp, damage, textureStr, hitbox, pos, vel, acc);
	case eDebris:
		return new Debris(hp, damage, textureStr, hitbox, pos, vel, acc);
	case ePlayerBullet:
		return new Bullet(ePlayerBullet, hp, damage, textureStr, hitbox, pos, vel, acc);
	case eEnemyBullet:
		return new Bullet(eEnemyBullet, hp, damage, textureStr, hitbox, pos, vel, acc);
	case eItem:
		return new Item(1, 0, textureStr, hitbox, pos, {0, 0}, {0, 0});
	default:
		// 不明なObjectTypeが指定された場合
		return nullptr;
	}
}
