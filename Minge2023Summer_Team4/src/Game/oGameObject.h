#pragma once
#include "../Define.h"
#include "../oSuperObject.h"
#include "../Figure.h"

class GameObject :
    public SuperObject
{
private:
	bool btest = false;
	Timer collisionalTimer { 1s, StartImmediately::No };

protected:

	int hp;
	int damage;

	Vec2 pos = { 0,0 };
	Vec2 Spd = { 0,0 };
	Vec2 Acc = { 0,0 };

	Figure hitbox;

	eObjectType myObjectType;

	virtual void move();
	void drawHitbox(Vec2 offset) const;


public:

	GameObject();
	~GameObject();

	void update();
	virtual void draw(Vec2 offset, bool isHitboxDraw) const;

	Figure GetHitbox();
	int GetDamage();
	bool isCollisional();
	void onCollisionResponse(int damage);
	void calcDamage(int damage);

};

