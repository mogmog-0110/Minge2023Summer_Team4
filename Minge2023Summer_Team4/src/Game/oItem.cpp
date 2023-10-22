# include "oItem.h"

Item::~Item()
{

}

void Item::update()
{
}

// ゲッター関数
ItemType Item::getItemType() const
{
	return this->itemType;
}

bool Item::getIsActive() const
{
	return this->isActive;
}

//　セッター関数
void Item::setItemType(ItemType itemType)
{
	this->itemType = itemType;
}

void Item::setActive(bool boolean)
{
	isActive = boolean;
}
