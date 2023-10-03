#include "oDebris.h"

Debris::~Debris()
{
}

bool Debris::isCollisional(eObjectType eType) {

	switch (eType)
	{
	case eNone:
		//値設定なし
		return GameObject::isCollisional();
		break;
	case ePlayer:
	case eDebris:
		//跳ね返りありダメージあり（未実装）
		return GameObject::isCollisional();
		break;
	case eBullet:
		//両方にダメージ
		return GameObject::isCollisional();
		break;
	case eEnemy:
	default:
		//反応なし
		return false;
		break;
	}
}
