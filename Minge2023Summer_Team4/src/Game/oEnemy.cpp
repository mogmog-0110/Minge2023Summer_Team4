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

void Enemy::update()
{
	GameObject::update();
	updateDirection();

	if (deathPhase > 0)
	{
		static Timer deathBoomTimer{ 0.2s, StartImmediately::Yes };
		static Timer deathEffectTimer{ 5s, StartImmediately::Yes };

		if (!deathBoomTimer.isRunning())
		{
			myEffectManager->create_spliteEffect(pos + RandomVec2(Random(100)), U"Effect1", 0.15, Random(100));
			myEffectManager->create_spliteEffect(pos + RandomVec2(Random(100)), U"Effect2", 0.15, Random(100));
			mySoundPlayer->playEffect(effectHit2);
			mySoundPlayer->playEffect(effectHitDebris);
		}
		if (!deathEffectTimer.isRunning()) {
			hp = 0;
			mySoundPlayer->playEffect(effectBossDeathSound1);
			mySoundPlayer->playEffect(effectBossDeathSound2);

		}
	}

}

void Enemy::onCollisionResponse(int damage)
{
	if (isDeathDelay)
	{
		if (deathPhase == 0)
		{
			GameObject::onCollisionResponse(damage);
			if (hp <= 0) {
				deathPhase++;
				hp = 1;
				this->damage = 0;
				speed = 10;
				mySoundPlayer->playEffect(effectBossDeathSound3);
			}
		}
	}
	else GameObject::onCollisionResponse(damage);

}

void Enemy::onCollisionResponse(Vec2 RepullPos)
{
	GameObject::onCollisionResponse(RepullPos);
}

void Enemy::calcAndSetExp()
{
	int expPoints = 0;

	// 基本経験値に強さの一定割合を加える
	expPoints = 10 + static_cast<int>(strength * 0.3);

	// 強さが特定の閾値を超えた場合、ボーナス経験値を追加
	if (enemyLevel >= 1)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 2)
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
	if (enemyLevel >= 7)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 8)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 9)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 10)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 11)
	{
		expPoints += 50;
	}
	if (enemyLevel >= 12)
	{
		expPoints += 50;
	}
	setExp(expPoints);
}

double Enemy::getStrength() const
{
	return strength;
}

void Enemy::setHasBullet()
{
	if (textureStr == U"Kuro" || textureStr == U"EvilEye" || textureStr == U"Worm" || textureStr == U"BigSpider")
	{
		hasBullet = true;
	}
	else
	{
		hasBullet = false;
	}
}

void Enemy::setDeathDelay()
{
	if (textureStr == U"Kuro" || textureStr == U"BigRat" || textureStr == U"BigSpider")
	{
		isDeathDelay = true;
	}
	else
	{
		isDeathDelay = false;
	}
}



void Enemy::determineLevel()
{
	int strength = getStrength() / 2; 

	if (strength >= 40000)
	{
		enemyLevel = 12;
	}
	else if (strength >= 30000)
	{
		enemyLevel = 11;
	}
	else if (strength >= 20000)
	{
		enemyLevel = 10;
	}
	else if (strength >= 15000)
	{
		enemyLevel = 9;
	}
	else if (strength >= 10000)
	{
		enemyLevel = 8;
	}
	else if (strength >= 7500)
	{
		enemyLevel = 7;
	}
	else if (strength >= 5000)
	{
		enemyLevel = 6;
	}
	else if (strength >= 3000)
	{
		enemyLevel = 5;
	}
	else if (strength >= 1500)
	{
		enemyLevel = 4;
	}
	else if (strength >= 1000)
	{
		enemyLevel = 3;
	}
	else if (strength >= 500)
	{
		enemyLevel = 2;
	}
	else if (strength >= 100)
	{
		enemyLevel = 1;
	}
	else
	{
		// strength が 100 未満の場合の処理（必要に応じて）
		enemyLevel = 0;
	}
}

BulletProperty Enemy::createBulletProperty()
{
	BulletProperty bp;
	bp.damage = damage/2;

	switch (enemyLevel)
	{
	case 1:
		bp.way = 1; bp.speed = 100; bp.delay = 3.0; break;
	case 2:
		bp.way = 1; bp.speed = 100; bp.delay = 2.0; break;
	case 3:
		bp.way = 1; bp.speed = 200; bp.delay = 1.0; break;
	case 4:
		bp.way = 3; bp.speed = 250; bp.delay = 3.0; break;
	case 5:
		bp.way = 3; bp.speed = 300; bp.delay = 1.0; break;
	case 6:
		bp.way = 5; bp.speed = 350; bp.delay = 2.0; break;
	case 7:
		bp.way = 7; bp.speed = 400; bp.delay = 3.0; break;
	case 8:
		bp.way = 7; bp.speed = 400; bp.delay = 2.0; break;
	case 9:
		bp.way = 9; bp.speed = 400; bp.delay = 1.0; break;
	case 10:
		bp.way = 9; bp.speed = 400; bp.delay = 0.6; break;
	case 11:
		bp.way = 12; bp.speed = 500; bp.delay = 0.5; break;
	case 12:
		bp.way = 12; bp.speed = 500; bp.delay = 0.3; break;
	default:
		// enemyLevelが0または想定外の値の場合の処理（必要に応じて）
		bp.way = 1; bp.speed = 300; bp.delay = 3.0; break;
	}

	bp.direction = calculateDirection(bp.way);
	return bp;
}

Array<Vec2> Enemy::calculateDirection(int way)
{
	Array<Vec2> bulletVectors;
	Player* myPlayer = Player::getInstance();

	if (way == 12)
	{
		for (int i = 0; i < 12; ++i) {
			double angle = i * (360.0 / 12) * Math::Pi / 180.0;  // 30度ごとにラジアンに変換
			bulletVectors.push_back(Vec2(Cos(angle), Sin(angle)));
		}
	}
	else
	{
		Vec2 toPlayer = (myPlayer->getPos() - pos).setLength(1);
		double angleOffset = 15.0 * Math::Pi / 180.0;  // ラジアンに変換
		bulletVectors.push_back(toPlayer);
		for (int i = 1; i <= way / 2; ++i) {
			bulletVectors.push_back(toPlayer.rotated(-angleOffset * i));
			bulletVectors.push_back(toPlayer.rotated(angleOffset * i));
		}
	}
	return bulletVectors;
}

void Enemy::setUpAnimation()
{
	// 敵の種類によってセットするアニメーションを変える。
	if (textureStr == U"Kuro")
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを32x32ピクセルの領域に分割
		auto regions = splitImage(texture, 32 * EXPORT_SCALE, 32 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"right"] = { regions[0], regions[1], regions[2], regions[3], regions[4], regions[5], regions[6], regions[7] };
		animations[U"left"] = { regions[8], regions[9], regions[10], regions[11], regions[12], regions[13], regions[14], regions[15] };
	}
	else if (textureStr == U"Worm" || textureStr == U"BigSpider")
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを32x32ピクセルの領域に分割
		auto regions = splitImage(texture, 32 * EXPORT_SCALE, 32 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"right"] = { regions[0], regions[1], regions[2], regions[3], regions[4], regions[5], regions[6], regions[7] };
		animations[U"left"] = { regions[8], regions[9], regions[10], regions[11], regions[12], regions[13], regions[14], regions[15] };
	}
	else if (textureStr == U"EvilEye")
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを32x32ピクセルの領域に分割
		auto regions = splitImage(texture, 32 * EXPORT_SCALE, 32 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"right"] = { regions[0], regions[1], regions[2], regions[3], regions[4], regions[5], regions[6] };
		animations[U"left"] = { regions[7], regions[8], regions[9], regions[10], regions[11], regions[12], regions[13] };
	}
	else
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを16x16ピクセルの領域に分割
		auto regions = splitImage(texture, 16 * EXPORT_SCALE, 16 * EXPORT_SCALE);

		//　各向きごとのアニメーションフレームを設定
		animations[U"right"] = { regions[0], regions[1], regions[2], regions[3] };
		animations[U"left"] = { regions[4], regions[5], regions[6], regions[7] };
	}
}

void Enemy::updateDirection()
{
	// 敵の位置とプレイヤーの位置の差を取得
	Player* myPlayer = Player::getInstance();
	double diff = myPlayer->getPos().x - this->pos.x;

	// 差に基づいてcurrentDirectionを更新
	if (diff > 0) {
		this->currentDirection = U"right";
	}
	else
	{
		this->currentDirection = U"left";
	}
}
