#pragma once
#include "../Define.h"
#include "../oSuperObject.h"
#include "../Figure.h"
#include "pObjectAppearanceManager.h"


class GameObject :
    public SuperObject
{
private:
	Timer collisionalTimer;
	//String textureStr;

	const Font debugfont{ 15 };

protected:

	ObjectAppearanceManager& OAM;

	int hp = 1;
	int damage = 1;

	Vec2 pos;
	Vec2 vel;
	Vec2 acc;

	Figure hitbox;

	eObjectType myObjectType;

	void updateCommon();
	void drawHitbox(Vec2 offset) const;


public:

	GameObject(ObjectAppearanceManager& OAM_, eObjectType, int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 });

	~GameObject();

	void update();
	virtual void move();

	virtual void draw(Vec2 offset, bool isHitboxDraw) const;

	Figure GetHitbox();
	int GetDamage();
	bool isCollisional();
	void onCollisionResponse(int damage);
	void calcDamage(int damage);

};

