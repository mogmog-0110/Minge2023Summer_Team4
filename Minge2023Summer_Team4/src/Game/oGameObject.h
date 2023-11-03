#pragma once
#include "../Define.h"
#include "../oSuperObject.h"
#include "../Figure.h"
#include "pEffectManager.h"


class GameObject :
    public SuperObject
{
private:

	Timer collisionalTimer;

	Timer blinkTimer1 = Timer{ 0.5s,StartImmediately::Yes };
	Timer blinkTimer2 = Timer{ 0.1s,StartImmediately::Yes };;

	const Font debugfont{ 15 };

protected:

	eObjectType objType;
	double hp = 1;
	double previousHp;
	int damage = 1;
	double speed;
	String textureStr;
	Figure hitbox;
	int size = hitbox.getCircle().r * 3;
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
		
	// 経験値
	int expPoints;

	double damageDelayElapsed = 0.0; // 経過時間の保持

	Texture texture;

	Vec2 velRepull = {0,0};
	double repullDecaySpeed = 100;

	bool isMoving = false;

	// アニメーション関連のメンバ変数
	double animationTimer = 0.0;
	double animationInterval = 0.1;  // アニメーションフレームの更新間隔
	size_t animationFrame = 0;
	String currentDirection = U"left";
	HashTable<String, Array<TextureRegion>> animations;

	void updateCommon();
	void drawHitbox(Vec2 offset) const;
	void updateAnimation();

	//アイテムが落ちるかどうかの設定。HPが0になる意外の特殊死亡ではfalseになる。なおアイテムがドロップしないオブジェクトタイプでは参照されない。
	bool isItemDropable = true;

	EffectManager* myEffectManager;

	bool isBlinkShift = false;


public:

	GameObject(eObjectType type, int hp_, int damage_, String textureStr_,
			   Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: objType(type), hp(hp_), damage(damage_), textureStr(textureStr_),
		hitbox(hitbox_), pos(pos_), vel(vel_), acc(acc_)
	{
		hitbox.setCenter(pos);
		myEffectManager = EffectManager::getInstance();
	}

	~GameObject();

	void update();
	virtual void move();

	virtual void draw(Vec2 offset, bool isHitboxDraw) const;

	virtual void drawAnimation(Vec2 offset) const;

	bool isCollisional();
	void onCollisionResponse(int damage);
	void onCollisionResponse(Vec2 RepullPos);
	void calcDamage(int damage);
	void changeCoolTime(Duration);

	bool isDead(Vec2 playerPos_ = {0,0});

	//実質ゲッター関数
	bool isItemDrop();
	bool isBulletSelfDamage();

	//ゲッター関数
	Vec2 getPos() const;
	double getSpeed() const;
	int getDamage();
	Figure getHitbox();
	eObjectType getObjType() const;
	double getHp() const;
	int getExp() const;

	//セッター関数
	void setSpeed(double);
	void setPos(Vec2);
	void setVelocity(Vec2);
	void setAcceleration(Vec2);
	void setTexture(String);
	void setExp(int);
};

