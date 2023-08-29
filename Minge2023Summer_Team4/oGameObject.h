#pragma once
#include "Define.h"
#include "oSuperObject.h"
#include "Figure.h"

class GameObject :
    public SuperObject
{
private:

protected:

	int hp;
	int damage;
	Vec2 pos;
	Figure hitbox;

	eObjectType myObjectType;

	virtual void move();

public:

	GameObject();
	~GameObject();

	void update();
	void draw(Vec2 offset) const;

	bool isCollisional();
	void onCollisionResponse(int damage);

	void calcDamage(int damage);

};

