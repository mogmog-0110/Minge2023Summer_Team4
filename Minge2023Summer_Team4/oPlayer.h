#pragma once
#include "oGameObject.h"

class Player :
    public GameObject
{
private:
	const Texture texture{ U"💩"_emoji };
	double speed;

protected:

public:
	Player();
	~Player();

	void move() override;

	void drawObject(Vec2 offset) const override;
};

