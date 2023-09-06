#include "oGameObject.h"

GameObject::GameObject()
{
	hitbox = Circle{ pos,50 };
	collisionalTimer = Timer{ 1s, StartImmediately::No };
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
	if (collisionalTimer.isRunning() == false) hitbox.draw({Palette::Tomato, 0.5});
	else hitbox.draw({ Palette::Royalblue, 0.5 });

	//ついでにデバッグ用
	debugfont(Format(hp)).drawAt(pos + offset + Vec2{0,30}, {Palette::Navy,0.5});
}

Figure GameObject::GetHitbox() {
	return hitbox;
}

int GameObject::GetDamage() {
	return damage;
}

bool GameObject::isCollisional()
{
	return !collisionalTimer.isRunning();
}

void GameObject::onCollisionResponse(int damage)
{
	collisionalTimer.restart();
}

void GameObject::calcDamage(int damage)
{
}
