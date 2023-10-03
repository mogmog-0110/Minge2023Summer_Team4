#include "oEnemy.h"


Enemy::~Enemy()
{
}


bool Enemy::isCollisional(eObjectType eType) {


	switch (eType)
	{
	case eNone:
		//値設定なし
		return GameObject::isCollisional();
		break;
	case eBullet:
		//自弾か敵弾かで処理を変える（未実装）
		return GameObject::isCollisional();
		break;
	case ePlayer:
		//両方にダメージ
		return GameObject::isCollisional();
		break;
	case eEnemy:
	case eDebris:
	default:
		//反応なし
		return false;
		break;
	}

}
