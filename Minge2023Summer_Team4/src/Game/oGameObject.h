#pragma once
#include "../Define.h"
#include "../oSuperObject.h"
#include "../Figure.h"

class GameObject :
    public SuperObject
{
private:

protected:

	int hp;
	int damage;

	Vec2 pos;
	Vec2 Spd;
	Vec2 Acc;

	Figure hitbox;

	eObjectType myObjectType;

	
	void drawHitbox(Vec2 offset) const;


public:

	GameObject();
	GameObject(Vec2 pos_, Vec2 Spd_);

	~GameObject();

	void update();
	void updateCommon();
	virtual void move();

	virtual void draw(Vec2 offset, bool isHitboxDraw) const;
	
	bool isCollisional();
	void onCollisionResponse(int damage);
	void calcDamage(int damage);

};

