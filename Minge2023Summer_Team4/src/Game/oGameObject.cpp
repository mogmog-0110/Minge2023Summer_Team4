#include "oGameObject.h"

GameObject::GameObject()
{
	pos = Vec2{0,0};
	hitbox = Circle{ pos,50 };
	Spd = Vec2{0,0};
	collisionalTimer = Timer{ 1s, StartImmediately::No };
}

GameObject::GameObject(Vec2 pos_, Vec2 Spd_)
{
	pos = pos_;
	hitbox = Circle{ pos,50 };
	Spd = Spd_;
	collisionalTimer = Timer{ 1s, StartImmediately::No };
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
	this->texture.drawAt(-offset);
	if (isHitboxDraw) drawHitbox(-offset);
}


void GameObject::drawHitbox(Vec2 offset) const
{
	//hitbox.draw({ Palette::Tomato, 0.5});
	if (collisionalTimer.isRunning() == false) hitbox.movedBy(offset).draw({Palette::Tomato, 0.5});
	else hitbox.movedBy(offset).draw({Palette::Royalblue, 0.5});

	//ついでにデバッグ用
	debugfont(Format(hp)).drawAt(pos + offset + Vec2{0,30}, {Palette::Navy,0.5});
}

Figure GameObject::getHitbox() {
	return hitbox;
}

int GameObject::getDamage() {
	return damage;
}

bool GameObject::isCollisional()
{
	return !collisionalTimer.isRunning();
}

void GameObject::onCollisionResponse(int damage)
{
	collisionalTimer.restart();
	hp -= damage;
}

void GameObject::calcDamage(int damage)
{
}

Vec2 GameObject::getPos() const
{
	return pos;
}

double GameObject::getSpeed() const
{
	return speed;
}
