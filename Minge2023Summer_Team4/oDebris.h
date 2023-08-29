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
	void drawObject(Vec2 offset) const;
};

