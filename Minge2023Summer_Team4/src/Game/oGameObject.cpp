#include "oGameObject.h"

GameObject::GameObject(eObjectType myType_, int hp_, int damage_, String textureStr_,
	Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_)
	:myObjectType(myType_), hp(hp_), damage(damage_), hitbox(hitbox_.setCenter(pos_)),
	pos(pos_),vel(vel_), acc(acc_), collisionalTimer(Timer{1s, StartImmediately::No}),
	SuperObject(TextureAsset(textureStr_))
{
	
}

GameObject::~GameObject()
{
}


//====================================================
//毎Tick実行するかんすう

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
	vel += acc * Scene::DeltaTime();
	pos += vel * Scene::DeltaTime(); //+ (0.5 * acc * Scene::DeltaTime() * Scene::DeltaTime());
	hitbox.moveBy(vel * Scene::DeltaTime());
}



//====================================================
//描画関連

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



//====================================================
//外部からの変数取得


Figure GameObject::getHitbox() {
	return hitbox;
}

int GameObject::getDamage() {
	return damage;
}



//====================================================
//接触関連

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

void GameObject::changeCoolTime(Duration cooltime) 
{
	collisionalTimer.set(cooltime);
}

//====================================================
//君は完璧で最強のゲッター関数


Vec2 GameObject::getPos() const
{
	return pos;
}

double GameObject::getSpeed() const
{
	return speed;
}



bool GameObject::isDead() {
	if (hp <= 0) return true;
	else if (pos.length() > 1000) return true;
	else return false;
}
