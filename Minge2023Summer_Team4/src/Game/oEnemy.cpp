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
	pos += (vel + velRepull) * Scene::DeltaTime();

	hitbox.setCenter(pos);
}

void Enemy::calcAndSetExp()
{
	int expPoints = 0;
	int strength = getStrength();

	// 基本経験値に強さの一定割合を加える
	expPoints = 10 + static_cast<int>(strength * 0.5);

	// 強さが特定の閾値を超えた場合、ボーナス経験値を追加
	if (strength > 20) {
		expPoints += 5;
	}
	if (strength > 40) {
		expPoints += 5;
	}
	if (strength > 60) {
		expPoints += 5;
	}
	if (strength > 80) {
		expPoints += 5;
	}
	if (strength > 100) {
		expPoints += 5;
	}

	setExp(expPoints);
}

int Enemy::getStrength() const
{
	return hp + damage;
}

