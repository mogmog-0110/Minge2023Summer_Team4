# include "pObjectManager.h"
# include "pObjectAppearanceManager.h"

ObjectManager::ObjectManager()
{
	Player::create(1000, 10, U"", Circle(30), Vec2(300,400), 400);
	myPlayer = Player::getInstance();

}


ObjectManager::~ObjectManager()
{
	
}

void ObjectManager::update()
{
	this->myPlayer->update();
	//this->testdebris.update();

	createEnemy();
	createDebris();

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

	if (DebugBulletTimer.isRunning() == false && KeySpace.pressed()) {
		Vec2 elementVector = (Cursor::PosF() - Scene::CenterF()).setLength(1);

		createBullet(true, myPlayer->getPos() + elementVector.setLength(50), elementVector.setLength(600), {0,0});
		DebugBulletTimer.restart();
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
					myDebrises[j]->onCollisionResponse(myDebrises[i]->getPos());
					myDebrises[i]->onCollisionResponse(myDebrises[j]->getPos());
				}

			}

			for (size_t i = 0; i < myPlayerBullets.size(); i++)
			{
					if (myPlayerBullets[i]->isCollisional() &&
						myPlayerBullets[i]->getHitbox().intersects(myDebrises[j]->getHitbox()))
					{
						myDebrises[j]->onCollisionResponse(myPlayerBullets[i]->getDamage());
						myPlayerBullets[i]->onCollisionResponse(myDebrises[j]->getDamage());
					}
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
			}

			for (size_t i = 0; i < myEnemyBullets.size(); i++)
			{
				if (myEnemyBullets[i]->isCollisional() &&
					myEnemyBullets[i]->getHitbox().intersects(myPlayerBullets[j]->getHitbox()) &&
					myEnemyBullets[i]->isPlayerBullet() == true)
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

	/*
	for (size_t j = 0; j < myEnemyBullets.size(); j++) {

		if (this->myEnemyBullets[j]->isCollisional() == true) {

			for (size_t i = 0; i < myEnemyBullets.size(); i++)
			{
				if (i == j) continue;
			}

			for (size_t i = 0; i < myEnemies.size(); i++)
			{

			}
		}
	}
	*/
	for (size_t j = 0; j < myEnemies.size(); j++)
	{
		for (size_t i = 0; i < myEnemies.size(); i++)
		{
			if (i == j) continue;
			if (myEnemies[i]->isCollisional() &&
				myEnemies[i]->getHitbox().intersects(myEnemies[j]->getHitbox()))
			{
				myEnemies[j]->onCollisionResponse(myEnemies[i]->getPos());
				myEnemies[i]->onCollisionResponse(myEnemies[j]->getPos());
			}
		}
	}
	

	int i = 0;
	for (auto itBullet = myPlayerBullets.begin(); itBullet != myPlayerBullets.end();)
	{
		if (myPlayerBullets[i]->isDead(myPlayer->getPos()))
		{
			delete myPlayerBullets[i];
			myPlayerBullets.erase(itBullet);
			break;
		}
		++itBullet;
		++i;
	}

	i = 0;
	for (auto itDebris = myDebrises.begin(); itDebris != myDebrises.end();)
	{
		if (myDebrises[i]->isDead())
		{
			delete myDebrises[i];
			myDebrises.erase(itDebris);
			break;
		}
		++itDebris;
		++i;
	}


	i = 0;
	for (auto itEnemy = myEnemies.begin(); itEnemy != myEnemies.end();)
	{
		if (myEnemies[i]->isDead())
		{
			delete myEnemies[i];
			myEnemies.erase(itEnemy);
			break;
		}
		++itEnemy;
		++i;
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
		Enemy* newEnemy = ObjectAppearanceManager::createNewObject<Enemy>(eEnemy, 1000, 10, U"", Rect(50), { 0,0 }, { 50 ,0 }, { 1 , 1 });
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

void ObjectManager::createBullet(bool isPlayerBullet, Vec2 pos_, Vec2 vel_, Vec2 acc_)
{
	Bullet* newBullet = ObjectAppearanceManager::createNewObject(eBullet, 1, 100, U"", Circle{ 10 }, pos_, vel_, acc_, isPlayerBullet);

	if (isPlayerBullet == true) myPlayerBullets << newBullet;
	else myEnemyBullets << newBullet;

}

void ObjectManager::createBullet(ObjectInitData OID)
{
	Bullet* newBullet = ObjectAppearanceManager::createNewObject(OID);

	if (OID.isPlayerBullet_ == true) myPlayerBullets << newBullet;
	else myEnemyBullets << newBullet;

}
