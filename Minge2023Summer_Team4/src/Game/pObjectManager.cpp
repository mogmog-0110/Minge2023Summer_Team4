#include "pObjectManager.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::update()
{
	this->player.update();
	this->testdebris.update();
}

void ObjectManager::draw() const
{
	this->testdebris.draw({ 0,0 }, true);
	this->player.draw({0,0},true);
}
