#include "oEnemy.h"


Enemy::~Enemy()
{
}

void Enemy::move()
{
	// プレイヤーの座標の取得
	Player* myPlayer = Player::getInstance();
	Vec2 playerPos = myPlayer->getPos();

	Vec2 elementVector = (pos - playerPos).setLength(1);

	vel = elementVector.setLength(vel.length()) * (-1);
	pos += vel * Scene::DeltaTime();

	hitbox.setCenter(pos);
}

