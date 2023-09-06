#pragma once
#include "../Define.h"
#include "../Figure.h"
#include "oPlayer.h"
#include "oDebris.h"

class ObjectManager
{
private:
	Player player;
	Debris testdebris;

public:
	ObjectManager();
	~ObjectManager();

	void update();
	void collision();
	void draw() const;
};
