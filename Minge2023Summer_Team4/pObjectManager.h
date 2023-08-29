#pragma once
#include "Define.h"
#include "oPlayer.h"

class ObjectManager
{
private:
	Player player;

public:
	ObjectManager();
	~ObjectManager();

	void update();
	void draw() const;
};
