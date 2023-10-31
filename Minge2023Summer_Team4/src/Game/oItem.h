#pragma once
# include "../Define.h"
# include "oGameObject.h"
# include "oPlayer.h"

class Item
	:public GameObject
{
private:
	ItemType itemType;
	bool isActive;
	String currentDirection = U"None";

public:
	Item(int hp_, int damage_, String textureStr_,
		  Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(eItem, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_)
	{
	};

	~Item();

	// ゲッター
	ItemType getItemType() const;
	bool getIsActive() const;

	// セッター
	void setItemType(ItemType);
	void setActive(bool);
};
