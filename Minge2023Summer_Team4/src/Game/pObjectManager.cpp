# include "pObjectManager.h"
# include "pObjectAppearanceManager.h"

ObjectManager::ObjectManager()
{
	Player::create(1000, 10, U"", Circle(30), Vec2(300,400), 400);
	myPlayer = Player::getInstance();
	//createEnemy();
	createDebris();
}

ObjectManager::~ObjectManager()
{
	
}

void ObjectManager::update()
{
	myPlayer->update();
	updateObjList(myDebrises);
	updateObjList(myPlayerBullets);
	updateObjList(myEnemyBullets);
	updateObjList(myEnemies);

	if (!DebugBulletTimer.isRunning() && MouseL.pressed())
	{
		Vec2 elementVector = (Cursor::PosF() - Scene::CenterF()).setLength(1);
		createPlayerBullet(myPlayer->getPos() + elementVector.setLength(50), elementVector.setLength(1000), { 1,1 });
		DebugBulletTimer.restart();
	}
}


void ObjectManager::collision() {
	if (this->myPlayer->isCollisional()) {
		checkCollisions(myPlayer, myDebrises);
		checkCollisions(myPlayer, myEnemyBullets);
		checkCollisions(myPlayer, myEnemies);
	}

	checkCollisionsBetweenArrays(myDebrises, myPlayerBullets);
	checkCollisionsBetweenArrays(myDebrises, myEnemyBullets);
	checkCollisionsBetweenArrays(myEnemies, myPlayerBullets);
	checkCollisionsBetweenArrays(myDebrises, myEnemies);

	// 敵同士の押し出し処理
	for (size_t i = 0; i < myEnemies.size(); ++i) {
		for (size_t j = i + 1; j < myEnemies.size(); ++j) {
			checkCollision(myEnemies[i], myEnemies[j]);
		}
	}

	// デブリ同士の押し出しandダメージ処理
	for (size_t i = 0; i < myDebrises.size(); ++i) {
		for (size_t j = i + 1; j < myDebrises.size(); ++j) {
			checkCollision(myDebrises[i], myDebrises[j]);
		}
	}

	cleanUp(myPlayerBullets, myPlayer->getPos());
	cleanUp(myDebrises);
	cleanUp(myEnemies);
}

void ObjectManager::draw(Vec2 offset) const
{

	for (size_t i = 0; i < myDebrises.size(); i++) myDebrises[i]->draw(offset, true);
	for (size_t i = 0; i < myPlayerBullets.size(); i++) myPlayerBullets[i]->draw(offset, true);
	for (size_t i = 0; i < myEnemyBullets.size(); i++) myEnemyBullets[i]->draw(offset, true);
	for (size_t i = 0; i < myEnemies.size(); i++) myEnemies[i]->draw(offset, true);

	this->myPlayer->draw(offset, true);
}

void ObjectManager::createEnemy()
{
	//　敵は100体生成
	while(myEnemies.size() < 100)
	{
		GameObject* newEnemy = ObjectAppearanceManager::createNewObject(eEnemy, 1000, 10, U"", Rect(50), ObjectAppearanceManager::generateRandomPos(), {50 , 50}, {1 , 1});
		if (newEnemy) {
			myEnemies << static_cast<Enemy*>(newEnemy);
		}

	}
}

Enemy* ObjectManager::createEnemyFromData(WaveData waveData)
{
	String name = waveData.enemyName;
	int hp = enemyDatas[name].hp * waveData.statusModifier;
	int damage = enemyDatas[name].damage * waveData.statusModifier;
	String texture = enemyDatas[name].textureStr;
	Figure hitbox = enemyDatas[name].hitbox;
	double speed = enemyDatas[name].speed * waveData.statusModifier;
	Vec2 spawnPos = { waveData.spawnPos.x + Random(50), waveData.spawnPos.y + Random(50) };

	GameObject* newEnemy = ObjectAppearanceManager::createNewObject(eEnemy, hp, damage, texture, hitbox, spawnPos, { speed, speed }, { 1, 1 });
	return static_cast<Enemy*>(newEnemy);
}

void ObjectManager::createDebris()
{
	//　デブリは100体まで自動補充
	while (myDebrises.size() < 100)
	{
		GameObject* newDebris = ObjectAppearanceManager::createNewObject(eDebris, 1000, 10, U"", Circle(50), ObjectAppearanceManager::generateRandomPos(), { 0,0 }, { 0,0 });
		if (newDebris) {
			myDebrises << static_cast<Debris*>(newDebris);
		}
	}
}

void ObjectManager::createPlayerBullet(Vec2 pos_, Vec2 vel_, Vec2 acc_)
{
	GameObject* newPlayerBullet = ObjectAppearanceManager::createNewObject(ePlayerBullet, 1, 100, U"", Circle{ 10 }, pos_, vel_, acc_);
	if (newPlayerBullet) {
		myPlayerBullets << static_cast<Bullet*>(newPlayerBullet);
	}
}

HashTable<String, EnemyData> ObjectManager::loadEnemyData(const String& filepath)
{
	const CSV csv{ filepath };

	if (not csv) {
		throw Error{ U"Failed to load " + filepath };
	}

	HashTable<String, EnemyData> enemyDatas;
	for (size_t row = 0; row < csv.rows(); ++row) {
		EnemyData enemy;
		enemy.name = csv[row][0];
		enemy.hp = Parse<int>(csv[row][1]);
		enemy.damage = Parse<int>(csv[row][2]);
		enemy.textureStr = csv[row][3];
		enemy.hitbox = ObjectManager::parseFigure(csv[row][4]);
		enemy.speed = Parse<double>(csv[row][5]);

		enemyDatas[enemy.name] = enemy; // エネミー名をキーとして、その情報をマップに保存

		Logger << enemy.name;
	}

	return enemyDatas;
}

Array<WaveData> ObjectManager::loadWaveData(const String& filepath)
{
	const CSV csv{ filepath };

	if (not csv) {
		throw Error{ U"Failed to load " + filepath };
	}

	Array<WaveData> waveDatas;
	for (size_t row = 0; row < csv.rows(); ++row) {
		WaveData wave;
		wave.spawnTime = Parse<double>(csv[row][0]);
		wave.enemyName = csv[row][1];
		wave.spawnPos = Parse<Vec2>(csv[row][2]);
		wave.statusModifier = Parse<double>(csv[row][3]);
		wave.spawnCount = Parse<int>(csv[row][4]);
		waveDatas.push_back(wave);
	}
		return waveDatas;
}

Figure ObjectManager::parseFigure(const String& str)
{
	if (str.starts_with(U"Rect")) {
		int size = Parse<int>(str.substr(5, str.length() - 6)); // ()内の数字を取得
		return Rect(size);
	}
	else if (str.starts_with(U"Circle")) {
		int radius = Parse<int>(str.substr(7, str.length() - 8)); // ()内の数字を取得
		return Circle(radius);
	}
	else {
		throw Error{ U"Unknown Figure Type: " + str };
	}
}
