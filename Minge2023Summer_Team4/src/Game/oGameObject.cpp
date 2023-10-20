#include "oGameObject.h"
#include "oPlayer.h"

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
	if (velRepull.length() > 0.01) velRepull.setLength(velRepull.length() - repullDecaySpeed * Scene::DeltaTime());

}

void GameObject::move()
{
	// プレイヤーの座標の取得
	Player* myPlayer = Player::getInstance();
	Vec2 playerPos = myPlayer->getPos();

	Vec2 elementVector = (pos - playerPos).setLength(1);

	vel = elementVector.setLength(vel.length()) * (-1);
	pos += (vel + velRepull) * Scene::DeltaTime();

    setPos(pos);

}


//====================================================
//描画関連

void GameObject::draw(Vec2 offset, bool isHitboxDraw) const
{
	this->texture.drawAt(-offset); // offsetを減算
	if (isHitboxDraw) drawHitbox(-offset);
}


void GameObject::drawHitbox(Vec2 offset) const
{
	if (collisionalTimer.isRunning() == false)
		hitbox.movedBy(offset).draw({ Palette::Tomato, 0.5 });
	else
		hitbox.movedBy(offset).draw({ Palette::Royalblue, 0.5 });

	//ついでにデバッグ用
	debugfont(Format(hp)).drawAt(this->pos + offset + Vec2{ 0,30 }, { Palette::Navy,0.5 });
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

void GameObject::onCollisionResponse(Vec2 RepullPos)
{
	//collisionalTimer.restart();
	velRepull = (pos - RepullPos).setLength(vel.length() == 0 ? 100 : vel.length());

}

void GameObject::calcDamage(int damage)
{
}

void GameObject::changeCoolTime(Duration cooltime) 
{
	collisionalTimer.set(cooltime);
}

bool GameObject::isDead(Vec2 playerPos_) {
	if (hp <= 0) return true;
	else return false;
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

eObjectType GameObject::getObjType() const
{
	return objType;
}

int GameObject::getHp() const
{
	return hp;
}

void GameObject::setSpeed(double speed)
{
	vel = { speed, speed };
}

void GameObject::setPos(Vec2 newPos)
{
	pos = newPos;
	hitbox.setCenter(newPos);
}

void GameObject::setTexture(String textureStr)
{
	texture = Texture{ textureStr };
}
