#include "pObjectManager.h"

ObjectManager::ObjectManager(ObjectAppearanceManager* OAM_, EventManager* EM_)
  : OAM(OAM_)
{
	myPlayer = new Player(1000, 10, U"", Circle(30), Vec2(300,400), 400);
	
	myDebrises.push_back(Debris{ 2000, 100, U"", Circle(50), {200,200}, {0,0},{0,0} });
	myDebrises.push_back(Debris{ 2000, 100, U"", Circle(50), {400,400}, {0,0},{0,0} });

	
}

ObjectManager::~ObjectManager()
{
	delete myPlayer;
}

void ObjectManager::update()
{
	this->myPlayer->update();
	this->testdebris.update();
	//以下　新型
	for (size_t i = 0; i < myDebrises.size(); i++)
	{
		myDebrises[i].update();
	}
}

void ObjectManager::collision() {
	if (this->myPlayer->isCollisional() == true) {
		if (testdebris.isCollisional() && testdebris.getHitbox().intersects(myPlayer->getHitbox()))
		{
			myPlayer->onCollisionResponse(testdebris.getDamage());
			testdebris.onCollisionResponse(myPlayer->getDamage());
		}
		
		//以下　新型
		for (size_t i = 0; i < myDebrises.size(); i++)
		{
			if (myDebrises[i].isCollisional() && myDebrises[i].getHitbox().intersects(myPlayer->getHitbox()))
			{
				myPlayer->onCollisionResponse(myDebrises[i].getDamage());
				myDebrises[i].onCollisionResponse(myPlayer->getDamage());
			}
		}
	}
}

void ObjectManager::draw(Vec2 offset) const
{
	this->testdebris.draw(offset, true);
	//以下　新型
	for (size_t i = 0; i < myDebrises.size(); i++)
	{
		myDebrises[i].draw(offset, true);
	}

	this->myPlayer->draw(offset, true);
}
