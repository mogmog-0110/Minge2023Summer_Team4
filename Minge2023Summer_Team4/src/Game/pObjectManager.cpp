# include "pObjectManager.h"
# include "pObjectAppearanceManager.h"

ObjectManager::ObjectManager()
{
	Player::create(1000, 10, U"", Circle(30), Vec2(300,400), 400);
	myPlayer = Player::getInstance();
	createEnemy();
	createDebris();

	/*
	myDebrises.push_back(Debris{ 2000, 100, U"", Circle(50), {500,0}, {0,0},{0,0} });
	myDebrises.push_back(Debris{ 2000, 100, U"", Circle(50), {400,400}, {0,0},{0,0} });

	myEnemies.push_back(Enemy{ 1000,10,U"",Rect(50),{-100,-100},{0,0},{0,0} });

	myBullets.push_back(Bullet{ false, 1,200,U"",Circle(20),{0,200},{0,200},{0,0} });*/
}

ObjectManager::~ObjectManager()
{
	
}

void ObjectManager::update()
{
	this->myPlayer->update();
	this->testdebris.update();

	//以下　新型
	for (size_t i = 0; i < myDebrises.size(); i++)
	{
		myDebrises[i]->update();
	}
	for (size_t i = 0; i < myBullets.size(); i++)
	{
		myBullets[i]->update();
	}
	for (size_t i = 0; i < myEnemies.size(); i++)
	{
		myEnemies[i]->update();
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
			if (myDebrises[i]->isCollisional() && myDebrises[i]->getHitbox().intersects(myPlayer->getHitbox()))
			{
				myPlayer->onCollisionResponse(myDebrises[i]->getDamage());
				myDebrises[i]->onCollisionResponse(myPlayer->getDamage());
			}
		}

		for (size_t i = 0; i < myBullets.size(); i++)
		{
			if (myBullets[i]->isCollisional() &&
				myBullets[i]->getHitbox().intersects(myPlayer->getHitbox()) &&
				myBullets[i]->isPlayerBullet() == false)
			{
				myPlayer->onCollisionResponse(myBullets[i]->getDamage());
				myBullets[i]->onCollisionResponse(myPlayer->getDamage());
			}
		}

		for (size_t i = 0; i < myEnemies.size(); i++)
		{
			if (myEnemies[i]->isCollisional() && myEnemies[i]->getHitbox().intersects(myPlayer->getHitbox()))
			{
				myPlayer->onCollisionResponse(myEnemies[i]->getDamage());
				myEnemies[i]->onCollisionResponse(myPlayer->getDamage());
			}
		}
	}
}


void ObjectManager::draw(Vec2 offset) const
{
	this->testdebris.draw(offset, true);
	//以下　新型
	for (size_t i = 0; i < myDebrises.size(); i++) myDebrises[i]->draw(offset, true);
	for (size_t i = 0; i < myBullets.size(); i++) myBullets[i]->draw(offset, true);
	for (size_t i = 0; i < myEnemies.size(); i++) myEnemies[i]->draw(offset, true);
	

	this->myPlayer->draw(offset, true);
}

void ObjectManager::createEnemy()
{
	//　敵は100体まで自動補充
	while(myEnemies.size() < 100)
	{
		Enemy* newEnemy = ObjectAppearanceManager::createNewObject<Enemy>(eEnemy, 1000, 10, U"", Rect(50), { -100,-100 }, { 0,0 }, { 0,0 });
		myEnemies << newEnemy;
	}
}

void ObjectManager::createDebris()
{
	//　デブリは100体まで自動補充
	while (myDebrises.size() < 100)
	{
		Debris* newDebris = ObjectAppearanceManager::createNewObject<Debris>(eDebris, 1000, 10, U"", Circle(50), { -100,-100 }, { 0,0 }, { 0,0 });
		myDebrises << newDebris;
	}
}
