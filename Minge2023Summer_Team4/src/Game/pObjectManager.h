#pragma once
#include "../Define.h"
#include "../Figure.h"
#include "oPlayer.h"
#include "oDebris.h"

class ObjectManager
{
private:
	Player player{ 1000, 10,U"",Circle(30), Vec2(300,400), 400};
	Debris testdebris{ 2000,100,U"",Circle(50), {200,200}, {50,25},{-50,0}};

public:
	ObjectManager();
	~ObjectManager();

	void update();
	void collision();
	void draw() const;
};
