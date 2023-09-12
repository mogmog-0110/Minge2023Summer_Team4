#pragma once
#include "../Define.h"
#include "../Figure.h"
#include "oPlayer.h"
#include "oDebris.h"

class ObjectManager
{
private:

public:
	ObjectManager();
	~ObjectManager();

	Player* myPlayer;
	Debris testdebris{ { 200,200 }, { 100,50 } };


	void update();
	void collision();
	void draw(Vec2 offset) const;
};
