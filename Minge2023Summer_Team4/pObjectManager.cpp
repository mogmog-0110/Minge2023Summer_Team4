#include "pObjectManager.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::update()
{
	this->player.move();
}

void ObjectManager::draw() const
{
	this->player.draw();
}
