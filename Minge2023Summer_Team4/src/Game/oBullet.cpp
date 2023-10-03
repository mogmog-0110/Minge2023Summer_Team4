#include "oBullet.h"

Bullet::~Bullet()
{
}

bool Bullet::isCollisional(eObjectType eType) {

	if (bPlayerBullet == true)
	{
		switch (eType)
		{
		case eNone:
			//値設定なし
			return GameObject::isCollisional();
			break;
		case eEnemy:
		case eDebris:
			//両方にダメージ
			return GameObject::isCollisional();
			break;
		case ePlayer:
		case eBullet:
		default:
			//反応なし
			return false;
			break;
		}
	}
	else
	{
		switch (eType)
		{
		case eNone:
			//値設定なし
			return GameObject::isCollisional();
			break;
		case ePlayer:
		case eDebris:
			//両方にダメージ
			return GameObject::isCollisional();
			break;
		case eEnemy:
		case eBullet:
		default:
			//反応なし
			return false;
			break;
		}
	}	
}
