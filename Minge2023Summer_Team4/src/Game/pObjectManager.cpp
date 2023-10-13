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

	// createEnemy();
	createEnemyFromCSV();

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
					myDebrises[j]->onCollisionResponse(myDebrises[i]->getDamage());
					myDebrises[i]->onCollisionResponse(myDebrises[j]->getDamage());
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

	for (size_t j = 0; j < myEnemies.size(); j++)
	{
		for (size_t i = 0; i < myEnemies.size(); i++)
		{

		}
	}
	*/

	int i = 0;
	for (auto itBullet = myPlayerBullets.begin(); itBullet != myPlayerBullets.end();)
	{
		if (myPlayerBullets[i]->isDead(myPlayer->getPos()))
		{
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
		Enemy* newEnemy = ObjectAppearanceManager::createNewObject<Enemy>(eEnemy, 1000, 10, U"", Rect(50), { -100,-100 }, { 150 ,150 }, { 1 , 1 });
		myEnemies << newEnemy;
	}
}

void ObjectManager::createEnemyFromCSV()
{
	// 蓄積時間
	extern double accumulatedTime;

	int key = static_cast<int>(accumulatedTime);
	if (waveInfo.contains(key))
	{
		String enemyName = waveInfo[key].enemyName;
		Vec2 spawnPos = { waveInfo[key].spawnLocation.x + Random(200), waveInfo[key].spawnLocation.y + Random(200) };
		double statusMultiplier = waveInfo[key].statusMultiplier;
		int enemyCount = waveInfo[key].enemyCount;

		// waveInfoのenemyNameと一致する敵データにアクセスするための添字を検索。
		int index;
		for (index = 0; enemyInfo[index].enemyName == enemyName; ++index){}
		EnemyData eI = enemyInfo[index];

		int hp = eI.hp * statusMultiplier;
		int damage = eI.damage * statusMultiplier;
		String textureName = eI.textureName;
		Figure hitbox = Rect(50);
		double speed = eI.speed * statusMultiplier;

		for (int i = 0; i < enemyCount; ++i)
		{
			Enemy* newObject = ObjectAppearanceManager::createNewObject<Enemy>(eEnemy, hp, damage, textureName, hitbox, spawnPos, {speed, speed}, {1, 1});
			myEnemies << newObject;
		}
		// waveInfo.erase(key);
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

void ObjectManager::readWaveCSV(int currentWave)
{

	// CSVファイルの読み取り

	String filename = U"wave" + Format(currentWave) + U".csv";
	String filePath = U"../src/Game/csvFile/" + filename;

	const CSV csv{filePath};

	if (not csv) // もし読み込みに失敗したら
	{
		throw Error{ U"Failed to load" + filePath };
	}

	for (size_t row = 0; row < csv.rows(); ++row)
	{
		WaveData wI;
		int hashKey = Parse<int>(csv[row][0]);

		wI.spawnLocation = Parse<Vec2>(csv[row][1]);
		wI.enemyName = csv[row][2];
		wI.statusMultiplier = Parse<double>(csv[row][3]);
		wI.enemyCount = Parse<int>(csv[row][4]);

		waveInfo.emplace(hashKey, wI);
	}
}

void ObjectManager::readEnemyCSV()
{
	// CSVファイルの読み取り
	const CSV csv{ U"../src/Game/csvFile/enemy.csv"};

	if (not csv) // もし読み込みに失敗したら
	{
		throw Error{ U"Failed to load `enemy.csv`" };
	}

	for (size_t row = 0; row < csv.rows(); ++row)
	{
		EnemyData eI;

		eI.enemyName = csv[row][0];
		eI.hp = Parse<int>(csv[row][1]);
		eI.damage = Parse<int>(csv[row][2]);
		eI.textureName = csv[row][3];

		int size = Parse<int>(csv[row][5]);

		// 一番愚直な方法
		if (csv[row][4] == U"Rect")
		{
			eI.hitbox = Rect(size);
		}
		else if (csv[row][4] == U"Circle")
		{
			eI.hitbox = Circle(size);
		}
		
		eI.speed = Parse<double>(csv[row][6]);

		/*String hashKey = U"enemy1";
		eI.hp = 1000;
		eI.damage = 10;
		eI.textureName = U"";
		eI.hitbox = Rect(50);
		eI.speed = 150;*/

		enemyInfo.push_back(eI);
		
	}
}
