#pragma once
#include "../Define.h"
#include "../Figure.h"
#include "pObjectAppearanceManager.h"
#include "oPlayer.h"
#include "oDebris.h"

class ObjectManager
{
private:
	Player player{OAM, 1000, 10, U"", Circle(30), Vec2(300,400), 400};
	Debris testdebris{OAM, 2000, 100, U"", Circle(50), {200,200}, {0,0},{0,0}};

	ObjectAppearanceManager OAM;

public:
	ObjectManager(ObjectAppearanceManager& OAM_) : OAM(OAM_) {};
	~ObjectManager();

	void update();
	void collision();
	void draw() const;
};
