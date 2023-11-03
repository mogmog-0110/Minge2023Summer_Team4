﻿#include "oBullet.h"

Bullet::~Bullet()
{
}

void Bullet::update()
{
	GameObject::update();
	move();

	if (bulletType == BulletType::SpecialD && bulletPhase > 0)
	{
		static Timer brustKeepTimer(0.5s, StartImmediately::No);
		if (bulletPhase == 1)
		{
			brustKeepTimer.start();
			bulletPhase++;
		}
		else if (brustKeepTimer.isRunning() == false)
		{
			hp = 0;
		}
	}
}

void Bullet::move()
{
	switch (bulletType)
	{
	case BulletType::SpecialA:
		if (bulletPhase == 0)
		{
			tipPos += vel * Scene::DeltaTime();
			Vec2 quadWidth = (tipPos - pos).rotated(90_deg).setLength(5);
			hitbox = Quad{ pos + quadWidth, pos - quadWidth, tipPos - quadWidth, tipPos + quadWidth };
			if ((tipPos - pos).length() > 200) bulletPhase++;
		}
		else
		{
			tipPos += vel * Scene::DeltaTime();
			pos += vel * Scene::DeltaTime();
			hitbox.moveBy(vel * Scene::DeltaTime());
		}

		break;
	case BulletType::SpecialB:

		break;
	case BulletType::SpecialC:
		break;
	case BulletType::SpecialD:
		if (vel.length() > 1)
		{
			//クソコード
			vel.setLength(vel.length() * 0.93);
		}
		break;
	}

	if (bulletType != BulletType::SpecialA)
	{
		pos += vel * Scene::DeltaTime();
		hitbox.setCenter(pos);
	}

}

void Bullet::draw(Vec2 offset, bool isHitboxDraw) const
{
	if (bulletType == BulletType::SpecialA)
	{
		texture.resized((tipPos - pos).length(), 50)
			.rotatedAt(Vec2{ 0,25 },
				(tipPos-pos).y > 0 ? acos((tipPos - pos).x / (tipPos - pos).length()) :
					Math::TwoPi - acos((tipPos - pos).x / (tipPos - pos).length())).draw(pos - offset);
	}
	else GameObject::draw(offset, isHitboxDraw);

}

bool Bullet::isDead(Vec2 playerPos_) {

	Vec2 scPos = pos - playerPos_;

	if (hp <= 0) return true;
	if (abs(scPos.x) > Scene::Width() / 2) return true;
	if (abs(scPos.y) > Scene::Height() / 2) return true;
	return false;
}

void Bullet::setUpAnimation()
{
	if (textureStr == U"NormalBullet")
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを16x16ピクセルの領域に分割
		auto regions = splitImage(texture, 16 * EXPORT_SCALE, 16 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"left"] = { regions[0], regions[1], regions[2], regions[3] };
	}
	else if (textureStr == U"LaserBullet")
	{
		//setTexture(textureStr);
	}
	else if (textureStr == U"WideBullet")
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを32x32ピクセルの領域に分割
		auto regions = splitImage(texture, 32 * EXPORT_SCALE, 32 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"left"] = { regions[0], regions[1], regions[2], regions[3] };
	}
	else if (textureStr == U"PrasmaBullet")
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを64x64ピクセルの領域に分割
		auto regions = splitImage(texture, 64 * EXPORT_SCALE, 64 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"left"] = { regions[0], regions[1], regions[2], regions[3] };
	}
	else if (textureStr == U"MineBullet")
	{
		const Texture& texture = TextureAsset(textureStr);

		// テクスチャを16x16ピクセルの領域に分割
		auto regions = splitImage(texture, 16 * EXPORT_SCALE, 16 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"left"] = { regions[0], regions[1], regions[2], regions[3] };

	}
	else
	{
		const Texture& texture = TextureAsset(U"EnemyBullet");
		// テクスチャを16x16ピクセルの領域に分割
		auto regions = splitImage(texture, 16 * EXPORT_SCALE, 16 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"left"] = { regions[0], regions[1], regions[2], regions[3] };
	}
}

void Bullet::onCollisionResponse(int damage)
{

	if (bulletType == BulletType::SpecialA)
	{

	}
	else if (bulletType == BulletType::SpecialD) {
		if (bulletPhase == 0)
		{
			hitbox = Circle(exproRange);
			this->damage = damage;
			hitbox.setCenter(pos);
			bulletPhase++;
			myEffectManager->create_spliteEffect(pos, U"Effect3", 0.3, exproRange+100);
		}
	}
	else GameObject::onCollisionResponse(damage);
}

void Bullet::onCollisionResponse(Vec2 RepullPos)
{
	GameObject::onCollisionResponse(RepullPos);
}

// getter

BulletType Bullet::getBulletType()
{
	return this->bulletType;
}

bool Bullet::isBulletSelfDamage()
{
	return (bulletType == BulletType::SpecialD);
}

// setter

void Bullet::setBulletType(BulletType bulletType)
{
	this->bulletType = bulletType;
	if (bulletType == BulletType::SpecialA) tipPos = pos;
}

void Bullet::setLevel(int)
{
	this->level = level;
}

void Bullet::setExproRange(int range)
{
	this->exproRange = range;
}
