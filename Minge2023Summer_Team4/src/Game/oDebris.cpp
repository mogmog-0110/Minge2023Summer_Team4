#include "oDebris.h"

Debris::~Debris()
{
}

void Debris::calcAndSetExp()
{
	int expPoints;
	int strength = hp + damage;

	// 基本経験値に強さの一定割合を加える
	expPoints = 10 + static_cast<int>(strength * 0.5);

	// 強さが特定の閾値を超えた場合、ボーナス経験値を追加
	if (strength > 20) {
		expPoints += 5;
	}
	if (strength > 40) {
		expPoints += 5;
	}
	if (strength > 60) {
		expPoints += 5;
	}
	if (strength > 80) {
		expPoints += 5;
	}
	if (strength > 100) {
		expPoints += 5;
	}

	setExp(expPoints);
 }

bool Debris::isDead(Vec2 playerPos_) {
	if ((pos - playerPos_).length() > 1800) {
		isItemDropable = false;
		return true;
	}
	else if (hp <= 0) return true;
	else return false;
}

// テクスチャをセットアップする関数
void Debris::setUpTexture()
{
	int r = hitbox.getCircle().r;
	if(r == 30) texture = TextureAsset(U"RockS");
	if(r == 65) texture = TextureAsset(U"RockM");
	if(r == 100) texture = TextureAsset(U"RockL");
}
