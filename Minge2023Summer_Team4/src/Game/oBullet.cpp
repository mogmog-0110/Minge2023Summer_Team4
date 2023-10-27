﻿#include "oBullet.h"

Bullet::~Bullet()
{
}

void Bullet::update()
{
	move();

}

void Bullet::move()
{
	pos += vel * Scene::DeltaTime();
	hitbox.setCenter(pos);
}

bool Bullet::isDead(Vec2 playerPos_) {

	Vec2 scPos = pos - playerPos_;

	if (hp <= 0) return true;
	if (abs(scPos.x) > Scene::Width() / 2) return true;
	if (abs(scPos.y) > Scene::Height() / 2) return true;
	return false;
}

// getter

BulletType Bullet::getBulletType()
{
	return this->bulletType;
}

// setter

void Bullet::setBulletType(BulletType bulletType)
{
	this->bulletType = bulletType;
}

void Bullet::setLevel(int)
{
	this->level = level;
}


