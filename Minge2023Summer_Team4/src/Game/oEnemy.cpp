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
	if (enemyLevel >= 1)
	{
		expPoints += 50;
	}
	if (enemyLevel>= 2)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 3)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 4)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 5)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 6)
	{
		expPoints += 50;
	}
	setExp(expPoints);
}

int Enemy::getStrength() const
{
	return maxHp + damage;
}

void Enemy::setHasBullet()
{
	if (textureStr == U"Kuro" || textureStr == U"EvilEye" || textureStr == U"Worm")
	{
		hasBullet = true;
	}
	else
	{
		hasBullet = false;
	}
}

BulletProperty Enemy::createBulletProperty()
{
	BulletProperty bp;

	if (hasBullet)
	{
		bp.damage = damage;
		switch (enemyLevel)
		{
		case 1:
			bp.way = 1;
			bp.speed = 300;
			bp.delay = 3.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 2:
			bp.way = 1;
			bp.speed = 500;
			bp.delay = 2.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 3:
			bp.way = 1;
			bp.speed = 800;
			bp.delay = 1.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 4:
			bp.way = 3;
			bp.speed = 300;
			bp.delay = 3.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 5:
			bp.way = 3;
			bp.way = 700;
			bp.delay = 1.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 6:
			bp.way = 5;
			bp.speed = 500;
			bp.delay = 2.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 7:
			bp.way = 7;
			bp.speed = 500;
			bp.delay = 3.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 8:
			bp.way = 7;
			bp.speed = 1000;
			bp.delay = 2.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 9:
			bp.way = 9;
			bp.speed = 800;
			bp.delay = 3.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 10:
			bp.way = 9;
			bp.speed = 1000;
			bp.delay = 1.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 11:
			bp.way = 12;
			bp.speed = 1000;
			bp.delay = 1.0;
			bp.direction = calculateDirection(bp.way);
			break;
		case 12:
			bp.way = 12;
			bp.speed = 1200;
			bp.delay = 0.5;
			bp.direction = calculateDirection(bp.way);
			break;
		}
		return bp;
	}
}

void Enemy::determineLevel()
{
	int strength = getStrength();
	if (strength >= 100)
	{
		enemyLevel = 1;
	}
	else if (strength >= 200)
	{
		enemyLevel = 2;
	}
	else if (strength >= 400)
	{
		enemyLevel = 3;
	}
	else if (strength >= 700)
	{
		enemyLevel = 4;
	}
	else if (strength >= 1100)
	{
		enemyLevel = 5;
	}
	else if (strength >= 1600)
	{
		enemyLevel = 6;
	}
	else if (strength >= 2200)
	{
		enemyLevel = 7;
	}
	else if (strength >= 2900)
	{
		enemyLevel = 8;
	}
	else if (strength >= 3700)
	{
		enemyLevel = 9;
	}
	else if (strength >= 4600)
	{
		enemyLevel = 10;
	}
	else if (strength >= 5600)
	{
		enemyLevel = 11;
	}
	else if (strength >= 6800)
	{
		enemyLevel = 12;
	}
}

Array<Vec2> Enemy::calculateDirection(int way)
{
	Array<Vec2> bulletVectors;
	Player* myPlayer = Player::getInstance();

	if (way == 12)
	{
		// 12wayの場合は全方向に弾を飛ばす
		for (int i = 0; i < 12; ++i) {
			double angle = i * (360.0 / 12);  // 30度ごと
			bulletVectors.push_back(Vec2(Cos(angle), Sin(angle)));
		}
	}
	else
	{
		// それ以外の場合はplayerPosに向かって弾を飛ばす
		Vec2 toPlayer = (myPlayer->getPos() - pos).setLength(1);  // 基本ベクトル
		double angleOffset = 15.0;  // 基本ベクトルからの角度オフセット
		bulletVectors.push_back(toPlayer);  // 中央の弾
		for (int i = 1; i <= way / 2; ++i) {
			// 左右に弾を追加
			bulletVectors.push_back(toPlayer.rotated(-angleOffset * i));
			bulletVectors.push_back(toPlayer.rotated(angleOffset * i));
		}
	}
	return bulletVectors;
}
