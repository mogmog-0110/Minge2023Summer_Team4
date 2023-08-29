#pragma once
#include "oGameObject.h"
class Bricks :
    public GameObject
{
private:
protected:
public:
	Bricks();
	~Bricks();
	void draw(Vec2 offset) const;
};

