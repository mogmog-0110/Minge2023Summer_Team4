#include "oGameObject.h"

GameObject::GameObject()
	:myObjectType(eObjectType::none), hp(1), damage(1), pos({ 0,0 }),
	Spd({ 0,0 }), Acc({ 0,0 }), hitbox(Circle{ pos,50 }), collisionalTimer(Timer{ 1s, StartImmediately::No })
{
}

GameObject::GameObject(eObjectType myType_, int hp_, int damage_, Vec2 pos_, Vec2 Spd_, Vec2 Acc_ = {0,0})
	:myObjectType(myType_), hp(hp_), damage(damage_), pos(pos_),
	Spd(Spd_), Acc(Acc_), hitbox(Circle{pos,50}), collisionalTimer(Timer{1s, StartImmediately::No})
{
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
	pos += (Spd * Scene::DeltaTime()); //+ (0.5 * Acc * Scene::DeltaTime() * Scene::DeltaTime());
	hitbox.moveBy(Spd * Scene::DeltaTime());
}



void GameObject::draw(Vec2 offset,bool isHitboxDraw) const
{
	this->texture.drawAt(offset);
	if (isHitboxDraw) drawHitbox(offset);
}


void GameObject::drawHitbox(Vec2 offset) const
{
	//hitbox.draw({ Palette::Tomato, 0.5});
	if (collisionalTimer.isRunning() == false) hitbox.movedBy(offset).draw({Palette::Tomato, 0.5});
	else hitbox.movedBy(offset).draw({Palette::Royalblue, 0.5});

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
	hp -= damage;
}

void GameObject::calcDamage(int damage)
{
}
