﻿# include "pObjectManager.h"
# include "pObjectAppearanceManager.h"

ObjectManager::ObjectManager()
{
	Player::create(1000, 10, U"", Circle(30), Vec2(300,400), 400);
	myPlayer = Player::getInstance();
	createEnemy();
	createDebris();

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
	for (size_t i = 0; i < myPlayerBullets.size(); i++)
	{
		myPlayerBullets[i]->update();
	}
	for (size_t i = 0; i < myEnemyBullets.size(); i++)
	{
		myEnemyBullets[i]->update();
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
		
		for (size_t i = 0; i < myDebrises.size(); i++)
		{
			if (myDebrises[i]->isCollisional() && myDebrises[i]->getHitbox().intersects(myPlayer->getHitbox()))
			{
				myPlayer->onCollisionResponse(myDebrises[i]->getDamage());
				myDebrises[i]->onCollisionResponse(myPlayer->getDamage());
			}
		}

		for (size_t i = 0; i < myPlayerBullets.size(); i++)
		{
		/*	if (myPlayerBullets[i]->isCollisional() &&
				myPlayerBullets[i]->getHitbox().intersects(myPlayer->getHitbox()) &&
				myPlayerBullets[i]->isPlayerBullet() == false)
			{
				myPlayer->onCollisionResponse(myPlayerBullets[i]->getDamage());
				myPlayerBullets[i]->onCollisionResponse(myPlayer->getDamage());
			}*/
		}

		for (size_t i = 0; i < myEnemyBullets.size(); i++)
		{
			if (myEnemyBullets[i]->isCollisional() &&
				myEnemyBullets[i]->getHitbox().intersects(myPlayer->getHitbox()) &&
				myEnemyBullets[i]->isPlayerBullet() == false)
			{
				myPlayer->onCollisionResponse(myEnemyBullets[i]->getDamage());
				myEnemyBullets[i]->onCollisionResponse(myPlayer->getDamage());
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

	for (size_t j = 0; j < myDebrises.size(); j++)
	{
		if (this->myDebrises[j]->isCollisional() == true) {

			for (size_t i = 0; i < myDebrises.size(); i++)
			{
				if (i == j) continue;
				if (myDebrises[i]->isCollisional() &&
					myDebrises[i]->getHitbox().intersects(myDebrises[j]->getHitbox()) )
				{
					myDebrises[j]->onCollisionResponse(myDebrises[i]->getDamage());
					myDebrises[i]->onCollisionResponse(myDebrises[j]->getDamage());
				}

			}


			for (size_t i = 0; i < myPlayerBullets.size(); i++)
			{
				/*	if (myPlayerBullets[i]->isCollisional() &&
						myPlayerBullets[i]->getHitbox().intersects(myDebrises[j]->getHitbox()) &&
						myPlayerBullets[i]->isPlayerBullet() == false)
					{
						myDebrises[j]->onCollisionResponse(myPlayerBullets[i]->getDamage());
						myPlayerBullets[i]->onCollisionResponse(myDebrises[j]->getDamage());
					}*/
			}

			for (size_t i = 0; i < myEnemyBullets.size(); i++)
			{
				if (myEnemyBullets[i]->isCollisional() &&
					myEnemyBullets[i]->getHitbox().intersects(myDebrises[j]->getHitbox()) &&
					myEnemyBullets[i]->isPlayerBullet() == false)
				{
					myDebrises[j]->onCollisionResponse(myEnemyBullets[i]->getDamage());
					myEnemyBullets[i]->onCollisionResponse(myDebrises[j]->getDamage());
				}
			}

			for (size_t i = 0; i < myEnemies.size(); i++)
			{
				/*
				* if (myEnemies[i]->isCollisional() && myEnemies[i]->getHitbox().intersects(myDebrises[j]->getHitbox()))
				{
					myDebrises[j]->onCollisionResponse(myEnemies[i]->getDamage());
					myEnemies[i]->onCollisionResponse(myDebrises[j]->getDamage());
				}
				*/
			}

		}
	}

	for (size_t j = 0; j < myPlayerBullets.size(); j++) {
		if (this->myPlayerBullets[j]->isCollisional() == true) {

			for (size_t i = 0; i < myPlayerBullets.size(); i++)
			{
				if (i == j) continue;
				/*	if (myPlayerBullets[i]->isCollisional() &&
						myPlayerBullets[i]->getHitbox().intersects(myPlayerBullets[j]->getHitbox()) &&
						myPlayerBullets[i]->isPlayerBullet() == false)
					{
						myPlayerBullets[j]->onCollisionResponse(myPlayerBullets[i]->getDamage());
						myPlayerBullets[i]->onCollisionResponse(myPlayerBullets[j]->getDamage());
					}*/
			}

			for (size_t i = 0; i < myEnemyBullets.size(); i++)
			{
				if (myEnemyBullets[i]->isCollisional() &&
					myEnemyBullets[i]->getHitbox().intersects(myPlayerBullets[j]->getHitbox()) &&
					myEnemyBullets[i]->isPlayerBullet() == false)
				{
					myPlayerBullets[j]->onCollisionResponse(myEnemyBullets[i]->getDamage());
					myEnemyBullets[i]->onCollisionResponse(myPlayerBullets[j]->getDamage());
				}
			}

			for (size_t i = 0; i < myEnemies.size(); i++)
			{
				
				if (myEnemies[i]->isCollisional() && myEnemies[i]->getHitbox().intersects(myPlayerBullets[j]->getHitbox()))
				{
					myPlayerBullets[j]->onCollisionResponse(myEnemies[i]->getDamage());
					myEnemies[i]->onCollisionResponse(myPlayerBullets[j]->getDamage());
				}
				
			}

		}
	}


}


void ObjectManager::draw(Vec2 offset) const
{
	this->testdebris.draw(offset, true);
	//以下　新型
	for (size_t i = 0; i < myDebrises.size(); i++) myDebrises[i]->draw(offset, true);
	for (size_t i = 0; i < myPlayerBullets.size(); i++) myPlayerBullets[i]->draw(offset, true);
	for (size_t i = 0; i < myEnemyBullets.size(); i++) myEnemyBullets[i]->draw(offset, true);
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
