#pragma once
# include "oGameObject.h"
# include "../Define.h"

class Ghost :
	public GameObject
{
private:
	Vec2 pos = Scene::Center();
	int animationFrame = 0;
	double animationTimer = 0.0;
	double animationInterval = 0.1;  // アニメーションの更新間隔
	String currentDirection = U"right";
	HashTable<String, Array<TextureRegion>> ghostAnimations;

public:
	Ghost(int hp_, int damage_, String textureStr_,
		   Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(eDebris, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_)
	{
		setupAnimations();
	};

	~Ghost();
	void update(const Vec2& playerPos, const String& playerDirection);
	void draw(Vec2) const;

	void setupAnimations();
	void updateAnimation();
};
