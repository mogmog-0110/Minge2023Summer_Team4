#include "oBullet.h"

Bullet::~Bullet()
{
}

void Bullet::update()
{
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
			Print << pos;
			Print << tipPos;
			tipPos += vel * Scene::DeltaTime();
			Vec2 quadWidth = (tipPos - pos).rotated(90_deg).setLength(10);
			hitbox = Quad{ pos + quadWidth, pos - quadWidth, tipPos - quadWidth, tipPos + quadWidth};

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

bool Bullet::isDead(Vec2 playerPos_) {

	Vec2 scPos = pos - playerPos_;

	if (hp <= 0) return true;
	if (abs(scPos.x) > Scene::Width() / 2) return true;
	if (abs(scPos.y) > Scene::Height() / 2) return true;
	return false;
}

void Bullet::onCollisionResponse(int damage)
{

	if (bulletType == BulletType::SpecialA)
	{

	}
	else if (bulletType == BulletType::SpecialD) {
 		if (bulletPhase == 0)
		{
			hitbox = Circle(250);
			hitbox.setCenter(pos);
			GameObject::damage = 10000;
			bulletPhase++;
		}
	}
	else GameObject::onCollisionResponse(damage);
}

void Bullet::onCollisionResponse(Vec2 RepullPos)
{
	GameObject::onCollisionResponse(RepullPos);\
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


