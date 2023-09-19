#include "pObjectManager.h"

ObjectManager::ObjectManager(ObjectAppearanceManager* OAM_, EventManager* EM_)
  : OAM(OAM_)
{
	myPlayer = new Player(1000, 10, U"", Circle(30), Vec2(300,400), 400);
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
