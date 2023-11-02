# include "oItem.h"

Item::~Item()
{

}

void Item::setUpAnimation()
{
	if (textureStr == U"Experience")
	{
		const Texture& expTexture = TextureAsset(U"Experience");

		// テクスチャを16x16ピクセルの領域に分割
		auto regions = splitImage(expTexture, 16 * EXPORT_SCALE, 16 * EXPORT_SCALE);

		// 各向きごとのアニメーションフレームを設定
		animations[U"left"] = { regions[0], regions[1], regions[2], regions[3] };
	}
	else
	{
		setMagicBookTexture();
	}
}

void Item::setMagicBookTexture()
{
	setTexture(textureStr);
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
