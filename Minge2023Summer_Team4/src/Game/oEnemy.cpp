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

void Enemy::setUpAnimation()
{

	// 敵の種類によってセットするアニメーションを変える。
	if (textureStr == U"Kuro")
	{
		const Texture& texture = TextureAsset(textureStr);
	}
	else if (textureStr == U"Worm" || textureStr == U"BigSpider")
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを32x32ピクセルの領域に分割
		auto regions = splitImage(texture, 32 * EXPORT_SCALE, 32 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"right"] = { regions[0], regions[1], regions[2], regions[3], regions[4], regions[5], regions[6], regions[7]};
		animations[U"left"] = { regions[8], regions[9], regions[10], regions[11], regions[12], regions[13], regions[14], regions[15]};
	}
	else if (textureStr == U"EvilEye")
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを32x32ピクセルの領域に分割
		auto regions = splitImage(texture, 32 * EXPORT_SCALE, 32 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"right"] = { regions[0], regions[1], regions[2], regions[3], regions[4], regions[5], regions[6]};
		animations[U"left"] = { regions[7], regions[8], regions[9], regions[10], regions[11], regions[12], regions[13]};
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
	else {
		this->currentDirection = U"left";
	}
}
