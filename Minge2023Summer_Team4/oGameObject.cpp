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

void GameObject::draw(Vec2 offset) const
{
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
