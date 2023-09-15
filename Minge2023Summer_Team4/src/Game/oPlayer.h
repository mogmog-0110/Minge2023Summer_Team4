#pragma once
#include "oGameObject.h"
#include "pObjectAppearanceManager.h"


class Player :
    public GameObject
{
private:
	const Texture tempTexture{ U"💩"_emoji };
	double speed;

protected:

public:
	Player(ObjectAppearanceManager& OAM_,int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, double speed_);
	~Player();

	void update() override;
	void move() override;

	void draw(Vec2 offset, bool isHitboxDraw) const override;
};

