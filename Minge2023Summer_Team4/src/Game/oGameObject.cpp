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
	//hitbox.draw({ Palette::Tomato, 0.5});
	if (btest==false) hitbox.draw({ Palette::Tomato, 0.5 });
	else hitbox.draw({ Palette::Royalblue, 0.5 });
}

Figure GameObject::GetHitbox() {
	return hitbox;
}

int GameObject::GetDamage() {
	return damage;
}

bool GameObject::isCollisional()
{
	return true;
}

void GameObject::onCollisionResponse(int damage)
{
	btest = true;
}

void GameObject::calcDamage(int damage)
{
}
