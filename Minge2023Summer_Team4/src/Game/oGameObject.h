#pragma once
#include "../Define.h"
#include "../oSuperObject.h"
#include "../Figure.h"


class GameObject :
    public SuperObject
{
private:

	Timer collisionalTimer;

	const Font debugfont{ 15 };

protected:

	eObjectType objType;
	int hp = 1;
	int damage = 1;
	double speed;
	String textureStr;
	Figure hitbox;
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;

	// 経験値
	int expPoints;

	Texture texture;

	Vec2 velRepull = {0,0};
	double repullDecaySpeed = 100;

	bool isMoving = false;

	void updateCommon();
	void drawHitbox(Vec2 offset) const;

	//アイテムが落ちるかどうかの設定。HPが0になる意外の特殊死亡ではfalseになる。なおアイテムがドロップしないオブジェクトタイプでは参照されない。
	bool isItemDropable = true;


public:

	GameObject(eObjectType type, int hp_, int damage_, String textureStr_,
			   Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: objType(type), hp(hp_), damage(damage_), textureStr(textureStr_),
		hitbox(hitbox_), pos(pos_), vel(vel_), acc(acc_){}

	~GameObject();

	void update();
	virtual void move();

	virtual void draw(Vec2 offset, bool isHitboxDraw) const;

	bool isCollisional();
	void onCollisionResponse(int damage);
	void onCollisionResponse(Vec2 RepullPos);
	void calcDamage(int damage);
	void changeCoolTime(Duration);

	bool isDead(Vec2 playerPos_ = {0,0});
	bool isItemDrop();
	//実質ゲッター関数

	//ゲッター関数
	Vec2 getPos() const;
	double getSpeed() const;
	int getDamage();
	Figure getHitbox();
	eObjectType getObjType() const;
	int getHp() const;
	int getExp() const;

	//セッター関数
	void setSpeed(double);
	void setPos(Vec2);
	void setVelocity(Vec2);
	void setAcceleration(Vec2);
	void setTexture(String);
	void setExp(int);
};

