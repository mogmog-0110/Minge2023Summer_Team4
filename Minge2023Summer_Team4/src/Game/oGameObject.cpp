#include "oGameObject.h"

GameObject::GameObject()
{
	pos = Vec2{0,0};
	hitbox = Circle{ pos,50 };
	Spd = Vec2{0,0};
}

GameObject::GameObject(Vec2 pos_, Vec2 Spd_)
{
	pos = pos_;
	hitbox = Circle{ pos,50 };
	Spd = Spd_;
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	updateCommon();
	move();
}

void GameObject::updateCommon()
{

}

void GameObject::move()
{
	pos += (Spd * Scene::DeltaTime());// +(0.5 * acc * Scene::DeltaTime() * Scene::DeltaTime())
	hitbox.moveBy(Spd * Scene::DeltaTime());
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
