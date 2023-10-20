# include "oItem.h"

Item::~Item()
{

}

// ゲッター関数
ItemType Item::getItemType() const
{
	return this->itemType;
}

//　セッター関数
void Item::setItemType(ItemType itemType)
{
	this->itemType = itemType;
}
