#pragma once
#include "oGameObject.h"
#include "../Define.h"


class Debris :
    public GameObject
{
private:
protected:
public:

	Debris(int hp_, int damage_, String textureStr_,
		   Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(eDebris, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_)
	{
		calcAndSetExp();
		changeCoolTime(0.1s);
		setUpTexture();
	};

	~Debris();

	void calcAndSetExp();
	bool isDead(Vec2 playerPos_ = { 0,0 });

	void setUpTexture();
};

