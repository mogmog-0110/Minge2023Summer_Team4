#include "pSuperObject.h"

SuperObject::SuperObject()
{
}

SuperObject::~SuperObject()
{
}

void SuperObject::update()
{
}

void SuperObject::draw(Vec2 offset) const
{
	texture.drawAt(offset);
}
