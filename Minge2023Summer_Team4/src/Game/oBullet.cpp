#include "oBullet.h"

Bullet::~Bullet()
{
}

bool Bullet::isDead(Vec2 playerPos_) {

	Vec2 scPos = pos - playerPos_;

	if (hp <= 0) return true;
	else if (abs(scPos.x) > Scene::Width() / 2) return true;
	else if (abs(scPos.y) > Scene::Height() / 2) return true;
	else return false;
}
