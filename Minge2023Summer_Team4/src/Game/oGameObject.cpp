#include "oGameObject.h"

GameObject::GameObject(ObjectAppearanceManager& OAM_, eObjectType myType_, int hp_, int damage_, String textureStr_,
	Figure hitbox_, Vec2 pos_, Vec2 Spd_, Vec2 Acc_)
	:myObjectType(myType_), hp(hp_), damage(damage_), hitbox(hitbox_.setCenter(pos_)),
	pos(pos_),Spd(Spd_), Acc(Acc_), collisionalTimer(Timer{1s, StartImmediately::No}),
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
	Spd += Acc * Scene::DeltaTime();
	pos += Spd * Scene::DeltaTime(); //+ (0.5 * Acc * Scene::DeltaTime() * Scene::DeltaTime());
	hitbox.moveBy(Spd * Scene::DeltaTime());
}



//====================================================
//描画関連

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



//====================================================
//外部からの変数取得

Figure GameObject::GetHitbox() {
	return hitbox;
}

int GameObject::GetDamage() {
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
