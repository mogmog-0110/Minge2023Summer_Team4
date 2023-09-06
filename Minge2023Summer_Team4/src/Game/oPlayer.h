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

	void update() override;
	void move() override;

	void draw(Vec2 offset, bool isHitboxDraw) const override;
};

