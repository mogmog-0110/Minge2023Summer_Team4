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
	pos += (vel + velRepull) * Scene::DeltaTime(); //+ (0.5 * acc * Scene::DeltaTime() * Scene::DeltaTime());
	hitbox.moveBy((vel + velRepull) * Scene::DeltaTime());

	if (velRepull.length() > 50) velRepull.setLength(velRepull.length() * (1 - repullDecayRate * Scene::DeltaTime()));
}

