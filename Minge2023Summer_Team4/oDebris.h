#pragma once
#include "oGameObject.h"
class Debris :
    public GameObject
{
private:
protected:
public:
	Debris();
	~Debris();
	void draw(Vec2 offset) const;
};

