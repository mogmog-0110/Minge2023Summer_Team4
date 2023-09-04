#include "stdafx.h"
#include "oGameObject.h"

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

void GameObject::move()
{
}



void GameObject::draw(Vec2 offset,bool isHitboxDraw) const
{
	this->texture.drawAt(offset);
	if (isHitboxDraw) drawHitbox(offset);
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
