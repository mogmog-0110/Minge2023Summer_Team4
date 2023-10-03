#include "oBullet.h"

Bullet::~Bullet()
{
}

bool Bullet::isCollisional(eObjectType eType) {

	return GameObject::isCollisional();

}
