#pragma once
# include "oGameObject.h"
# include "../Define.h"

class Ghost :
	public GameObject
{
private:
public:
	Ghost(int hp_, int damage_, String textureStr_,
		   Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(eDebris, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_)
	{
		setupAnimations();
	};

	~Ghost();
	void update(const Vec2& playerPos, const String& playerDirection);
	void draw(Vec2 offset) const;

	void animationDraw(Vec2 offset) const;

	void setupAnimations();
};
