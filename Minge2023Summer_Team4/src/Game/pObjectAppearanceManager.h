#pragma once
# include "../Define.h"
#include "oGameObject.h"
#include "oDebris.h"



class ObjectAppearanceManager
{
private:
	int debugNum = 0;
	Array<Debris> objectDebrisQueue;

public:
	ObjectAppearanceManager();
	~ObjectAppearanceManager();

	void createNewObject
	(eObjectType myType_, int hp_, int damage_, String textureStr_,
		Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_);

	void carryOutNewObject(Array<Debris> &myDebrises_);

	void debugCount();
	void debug();
};
