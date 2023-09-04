#include "stdafx.h"
#include "oPlayer.h"

Player::Player()
{
	speed = 500;
	hp = 100;
	damage = 100;
	pos = Vec2(Scene::Center());
	hitbox = Circle{ pos,30 };
}

Player::~Player()
{
}

void Player::move()
{
	Vec2 newPos(0, 0);
	const double deltaTime = Scene::DeltaTime();

	Vec2 V2move = { 0,0 };

	if (KeyW.pressed())
	{
		V2move.y -= 1;
	}
	if (KeyA.pressed())
	{
		V2move.x -= 1;
	}
	if (KeyS.pressed())
	{
		V2move.y += 1;
	}
	if (KeyD.pressed())
	{
		V2move.x += 1;
	}

	pos += V2move.setLength(1) * speed * deltaTime;
	hitbox = Circle{ pos,30 };
}

void Player::draw(Vec2 offset, bool isHitboxDraw) const
{
	this->texture.scaled(0.5).drawAt(pos + offset);
	if (isHitboxDraw) drawHitbox(offset);
}
