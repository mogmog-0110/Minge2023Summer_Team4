#include "stdafx.h"
#include "oGameObject.h"

void GameObject::move()
{
}

GameObject::GameObject()
{
	hitbox = Circle{ pos,50 };
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	hitbox = Circle{ pos,50 };
}

void GameObject::draw(Vec2 offset,bool isHitboxDraw) const
{
	if (isHitboxDraw) drawHitbox(offset);
	drawObject(offset);
}

void GameObject::drawObject(Vec2 offset) const
{
}

void GameObject::drawHitbox(Vec2 offset) const
{
	hitbox.draw({ Palette::Tomato, 0.5});
}

bool GameObject::isCollisional()
{
	return false;
}

void GameObject::onCollisionResponse(int damage)
{
}

void GameObject::calcDamage(int damage)
{
}
