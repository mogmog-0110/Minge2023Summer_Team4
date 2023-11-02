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

public:
	Item(int hp_, int damage_, String textureStr_,
		  Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_ = { 0,0 })
		: GameObject(eItem, hp_, damage_, textureStr_, hitbox_, pos_, vel_, acc_)
	{
		setUpAnimation();

	};

	~Item();

	void drawAnimation(Vec2) const override;
	void setUpAnimation();
	void setMagicBookTexture();

	// ゲッター
	ItemType getItemType() const;
	bool getIsActive() const;

	// セッター
	void setItemType(ItemType);
	void setActive(bool);
};
