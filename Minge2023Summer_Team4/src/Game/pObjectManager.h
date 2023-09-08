#pragma once
#include "../Define.h"
#include "../Figure.h"
#include "oPlayer.h"
#include "oDebris.h"

class ObjectManager
{
private:
	Player player{ 1000,10,Scene::Center(),400 };
	Debris testdebris{ eObjectType::debris,1000,10, { 200,200 }, { 50,25 },{-50,0} };

public:
	ObjectManager();
	~ObjectManager();

	void update();
	void collision();
	void draw() const;
};
