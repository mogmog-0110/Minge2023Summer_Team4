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
	Player(int hp_, int damage_, Vec2 pos_, double speed_);
	~Player();

	void update() override;
	void move() override;

	void draw(Vec2 offset, bool isHitboxDraw) const override;
};

