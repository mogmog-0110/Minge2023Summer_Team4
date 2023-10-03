#include "oDebris.h"

Debris::~Debris()
{
}

bool Debris::isCollisional(eObjectType eType) {

	return GameObject::isCollisional();

}
