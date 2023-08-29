﻿#include "stdafx.h"
#include "oPlayer.h"

Player::Player()
{
	speed = 500;
	hp = 100;
	damage = 100;
	pos = Vec2(Scene::Center());
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
}

void Player::draw() const
{
	this->texture.scaled(0.5).drawAt(pos);
}

void Player::draw(Vec2 offset) const
{
}