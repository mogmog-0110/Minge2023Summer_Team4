#include "pObjectManager.h"

ObjectManager::ObjectManager()
{
	myPlayer = new Player();
}

ObjectManager::~ObjectManager()
{
	delete myPlayer;
}

void ObjectManager::update()
{
	this->myPlayer->update();
	this->testdebris.update();
}

void ObjectManager::collision() {
	if (this->myPlayer->isCollisional() == true) {
		if (testdebris.isCollisional() && testdebris.getHitbox().intersects(myPlayer->getHitbox()))
		{
			myPlayer->onCollisionResponse(testdebris.getDamage());
			testdebris.onCollisionResponse(myPlayer->getDamage());
		}

	}
}

void ObjectManager::draw(Vec2 offset) const
{
	this->testdebris.draw(offset, true);
	this->myPlayer->draw(offset, true);
}
