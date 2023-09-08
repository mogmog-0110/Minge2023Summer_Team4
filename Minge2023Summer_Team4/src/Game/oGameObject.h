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

	int hp = 0;
	int damage = 1;

	Vec2 pos;
	Vec2 Spd;
	Vec2 Acc;

	Figure hitbox;

	eObjectType myObjectType;

	void updateCommon();
	void drawHitbox(Vec2 offset) const;


public:

	GameObject();
	GameObject(Vec2 pos_, Vec2 Spd_);

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

