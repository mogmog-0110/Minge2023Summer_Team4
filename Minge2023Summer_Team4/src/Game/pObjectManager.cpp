# include "pObjectManager.h"
# include "pObjectAppearanceManager.h"

ObjectManager::ObjectManager()
{
	// 初期ステータスの決定
	Player::create(100, 30, U"", Circle(24), Vec2(Scene::Center().x, Scene::Center().y), 200);
	myGhost = new Ghost(1000000, 0, U"Ghost", Circle(10), Vec2(Scene::Center().x - 60, Scene::Center().y - 60), { 300, 300 }, { 1, 1 });
	myPlayer = Player::getInstance();
	myEffectManager = EffectManager::getInstance();
	mySoundPlayer = SoundPlayer::getInstance();
	//createEnemy();
	currentState = BulletType::None;
	currentIndex = -1;
}

ObjectManager::~ObjectManager()
{
	Player::destroy();
}

void ObjectManager::update()
{
	collision();
	myPlayer->update();
	myGhost->update(myPlayer->getPos(), myPlayer->currentDirection);

	createDebris();
	updateObjList(myDebrises);
	updateObjList(myPlayerBullets);
	createEnemyBullet();
	updateObjList(myEnemyBullets);
	updateObjList(myEnemies);
	updateObjList(myItems);

	switchSpecialBullet();

	// 通常弾の発射
	if (!bulletTimer.isRunning() && (MouseL.pressed() || KeyV.pressed()))
	{
		createPlayerBullet();
		bulletTimer.restart();
	}

	// 特殊弾の発射
	if (!bulletTimer.isRunning() && (MouseR.pressed() || KeyB.pressed()) && myPlayer->availableBullet[selectedItemType] != 0)
	{
		Vec2 elementVector = (Cursor::PosF() - Scene::CenterF()).setLength(1);
		createSpecialBullet(myPlayer->getPos() + elementVector.setLength(50), elementVector.setLength(100), { 1,1 });
		bulletTimer.restart();
	}

	// プレイヤーとアイテムの衝突をチェック
	for (auto& item : myItems)
	{
		if (myPlayer->getHitbox().intersects(item->getHitbox())) {
			myPlayer->onItemPickUp(item);
		}
	}

	myPlayer->attractItems(myItems);

	// 不要になったアイテムをクリーンアップ
	cleanUp(myItems);

	// アイテムの上限数
	if (myItems.size() >= 100)
	{
		myItems.pop_front();
	}

	// バレットの上限数
	if (myPlayerBullets.size() >= 100)
	{
		myPlayerBullets.pop_front();
	}

	setDelayTimer();
}


void ObjectManager::collision() {
	if (this->myPlayer->isCollisional()) {
		checkCollisions(myPlayer, myDebrises);
		checkCollisions(myPlayer, myEnemyBullets);
		checkCollisions(myPlayer, myEnemies);
		checkCollisions(myPlayer, myItems);
	}

	for (size_t i = 0; i < myPlayerBullets.size(); ++i) {
		if (myPlayerBullets[i]->isBulletSelfDamage())
		{
			checkCollision(myPlayer, myPlayerBullets[i]);
		}
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

	/* // デブリ同士の押し出しandダメージ処理
	for (size_t i = 0; i < myDebrises.size(); ++i) {
		for (size_t j = i + 1; j < myDebrises.size(); ++j) {
			checkCollision(myDebrises[i], myDebrises[j]);
		}
	}*/

	cleanUp(myPlayerBullets, myPlayer->getPos());
	cleanUp(myDebrises, myPlayer->getPos());
	cleanUp(myEnemies);
	cleanUp(myEnemyBullets, myPlayer->getPos());
}

void ObjectManager::draw(Vec2 offset) const
{
	for (size_t i = 0; i < myItems.size(); i++) myItems[i]->draw(offset, false);
	for (size_t i = 0; i < myDebrises.size(); i++) myDebrises[i]->draw(offset, false);
	for (size_t i = 0; i < myPlayerBullets.size(); i++) myPlayerBullets[i]->draw(offset, false);
	for (size_t i = 0; i < myEnemyBullets.size(); i++) myEnemyBullets[i]->draw(offset, false);
	for (size_t i = 0; i < myEnemies.size(); i++) myEnemies[i]->draw(offset, false);

	this->myPlayer->draw(offset, false);
	this->myGhost->draw(offset);
}

void ObjectManager::createEnemy()
{
	//　敵は100体生成
	while (myEnemies.size() < 100)
	{
		GameObject* newEnemy = ObjectAppearanceManager::createNewObject(eEnemy, 1000, 10, U"Rat", Rect(50), ObjectAppearanceManager::generateRandomPos(), { 50 , 50 }, { 1 , 1 });
		if (newEnemy) {
			myEnemies << static_cast<Enemy*>(newEnemy);
		}

	}
}

Enemy* ObjectManager::createEnemyFromData(WaveData waveData)
{
	String name = waveData.enemyName;
	int hp = enemyDatas[name].hp * waveData.statusModifier * hellMode;
	int damage = enemyDatas[name].damage * waveData.statusModifier * 1 / 2 * hellMode;
	String textureStr = enemyDatas[name].textureStr;
	Figure hitbox = enemyDatas[name].hitbox;
	double speed = enemyDatas[name].speed * (waveData.statusModifier * 1 / 3);
	if (hellMode == 2)
	{
		speed = enemyDatas[name].speed * 2;
	}
	Vec2 spawnPos = { waveData.spawnPos.x + Random(50), waveData.spawnPos.y + Random(50) };

	GameObject* newEnemy = ObjectAppearanceManager::createNewObject(eEnemy, hp, damage, textureStr, hitbox, spawnPos + myPlayer->getPos(), { speed, speed }, { 1, 1 });
	return static_cast<Enemy*>(newEnemy);
}

void ObjectManager::createDebris()
{
	
	while (myDebrises.size() < 20)
	{
		int n = Random(1, 3);
		int hp;
		int hitbox;

		if (n == 1)
		{
			hitbox = 100;
			hp = 1500;
		}
		else if (n == 2)
		{
			hitbox = 65;
			hp = 1000;
		}
		else if (n == 3)
		{
			hitbox = 30;
			hp = 500;
		}

		GameObject* newDebris = ObjectAppearanceManager::createNewObject(eDebris, hp, 50, U"", Circle(hitbox), ObjectAppearanceManager::generateRandomPos(), { 0,0 }, { 0,0 });
		if (newDebris) {
			myDebrises << static_cast<Debris*>(newDebris);
		}
	}
}

void ObjectManager::createPlayerBullet()
{
	BulletProperty bp = myPlayer->createNormalProperty();
	Vec2 elementVector = (Cursor::PosF() - Scene::Center()).setLength(1);

	// 中心バレットの位置と速度を計算
	Vec2 centerPos = myPlayer->getPos() + elementVector.setLength(50);  // 初期位置をプレイヤーから50ピクセル離す
	Vec2 centerVel = elementVector.setLength(bp.speed);  // 速度をspeedにセット

	double angleOffset = 15.0 * Math::Pi / 180.0;  // ラジアンに変換
	// 中心バレットを作成
	createBullet(centerPos, centerVel, bp, Vec2(0, 0), BulletType::Normal);

	// 側面のバレットを作成
	for (int i = 1; i <= bp.way / 2; ++i)
	{
		Vec2 offsetPos, offsetVel;

		// 右側
		offsetVel = elementVector.rotated(angleOffset * i).setLength(bp.speed);
		offsetPos = myPlayer->getPos() + elementVector.setLength(50);
		createBullet(offsetPos, offsetVel, bp, Vec2(0, 0), BulletType::Normal);

		// 左側
		offsetVel = elementVector.rotated(-angleOffset * i).setLength(bp.speed);
		offsetPos = myPlayer->getPos() + elementVector.normalized().setLength(50);
		createBullet(offsetPos, offsetVel, bp, Vec2(0, 0), BulletType::Normal);
	}
}

void ObjectManager::createBullet(Vec2 pos, Vec2 vel, const BulletProperty& bp, Vec2 acc, BulletType type) {

	String textureStr;
	switch (type)
	{
	case BulletType::Normal:
		textureStr = U"NormalBullet";
		break;
	case BulletType::SpecialA:
		textureStr = U"LaserBullet";
		break;
	case BulletType::SpecialB:
		textureStr = U"WideBullet";
		break;
	case BulletType::SpecialC:
		textureStr = U"PrasmaBullet";
		break;
	case BulletType::SpecialD:
		textureStr = U"MineBullet";
		break;
	}

	GameObject* newBullet = ObjectAppearanceManager::createNewObject(ePlayerBullet, 1, bp.damage + myPlayer->getDamage(), textureStr, Circle{ bp.size }, pos, vel, acc);
	if (newBullet)
	{
		Bullet* newPlayerBullet = static_cast<Bullet*>(newBullet);
		newPlayerBullet->setBulletType(type);
		myPlayerBullets << newPlayerBullet;

		myEffectManager->create_spliteEffect(newPlayerBullet->getPos(), U"Effect4", 0.1, 100);
		mySoundPlayer->playEffect(effectShot);
	}
}

void ObjectManager::createEnemyBullet()
{
	for (size_t i = 0; i < myEnemies.size(); i++)
	{
		if (myEnemies[i]->hasBullet) {
			BulletProperty bp = myEnemies[i]->createBulletProperty();

			myEnemies[i]->bulletDelayElapsed += Scene::DeltaTime();

			if (myEnemies[i]->bulletDelayElapsed >= bp.delay)
			{
				for (const Vec2& dir : bp.direction)
				{
					Vec2 pos = myEnemies[i]->getPos();  // 敵の位置
					Vec2 vel = dir * bp.speed;  // 速度ベクトル
					Vec2 acc = { 1, 1 };  // 加速度ベクトル（必要に応じて設定）

					GameObject* newBullet = ObjectAppearanceManager::createNewObject(eEnemyBullet, 1, bp.damage, U"EnemyBullet", Circle{ 16 }, pos, vel, acc);
					if (newBullet) {
						Bullet* newEnemyBullet = static_cast<Bullet*>(newBullet);
						// 必要であれば、ここでnewEnemyBulletのプロパティを設定
						myEnemyBullets << newEnemyBullet;
					}
				}
				myEnemies[i]->bulletDelayElapsed = 0.0;  // 遅延時間をリセット
			}
		}
	}
}


void ObjectManager::createSpecialBullet(Vec2 pos, Vec2 vel, Vec2  acc)
{
	BulletProperty bp;

	switch (currentState)
	{
	case BulletType::SpecialA:
	{
		bp = myPlayer->createLaserProperty();

		// 中心のレーザー
		GameObject* tempBullet = ObjectAppearanceManager::createNewObject(ePlayerBullet, 1, bp.damage, U"LaserBullet", Circle{ 20 }, pos, vel.setLength(1000), acc);
		if (tempBullet) {
			Bullet* newBullet = static_cast<Bullet*>(tempBullet);
			newBullet->setBulletType(BulletType::SpecialA);
			myPlayerBullets << newBullet;
		}

		mySoundPlayer->playEffect(effectShotLaser2);

	}

	break;
	case BulletType::SpecialB:
	{
		bp = myPlayer->createWideProperty();
		for (int i = 0; i < 12; ++i) {
			double angle = i * (360.0 / 12) * Math::Pi / 180.0;  // 30度ごとにラジアンに変換
			Vec2 dir = { Cos(angle), Sin(angle) };
			Vec2 vel = dir.setLength(300);

			GameObject* tempBullet = ObjectAppearanceManager::createNewObject(ePlayerBullet, bp.hp, bp.damage + myPlayer->getDamage(), U"WideBullet", Circle{20}, myPlayer->getPos(), vel, acc);
			if (tempBullet) {
				Bullet* newBullet = static_cast<Bullet*>(tempBullet);
				newBullet->setBulletType(BulletType::SpecialB);
				myPlayerBullets << newBullet;
			}
		}

		myEffectManager->create_spliteEffect(myPlayer->getPos(), U"Effect2", 0.5, 100);
		mySoundPlayer->playEffect(effectShotWide2);
	} 
	break;
	case BulletType::SpecialC:
	{
		bp = myPlayer->createPrasmaProperty();
		GameObject* tempBullet = ObjectAppearanceManager::createNewObject(ePlayerBullet, bp.hp, bp.damage + myPlayer->getDamage(), U"PrasmaBullet", Circle{ bp.size }, pos, vel, acc);
		if (tempBullet) {
			Bullet* newBullet = static_cast<Bullet*>(tempBullet);
			newBullet->setBulletType(BulletType::SpecialC);
			myPlayerBullets << newBullet;
		}
		mySoundPlayer->playEffect(effectShotPrazma);
	}
	break;
	case BulletType::SpecialD:
	{
		bp = myPlayer->createMineProperty();
		GameObject* tempBullet = ObjectAppearanceManager::createNewObject(ePlayerBullet, 1, bp.damage + myPlayer->getDamage(), U"MineBullet", Circle{ 20 }, pos, vel.setLength(300), acc);
		if (tempBullet) {
			Bullet* newBullet = static_cast<Bullet*>(tempBullet);
			newBullet->setBulletType(BulletType::SpecialD);
			newBullet->setExproRange(bp.exproRange);
			myPlayerBullets << newBullet;
		}
		mySoundPlayer->playEffect(effectShotMinePop);

	}
	break;
	case BulletType::None:
	{
	}
	break;
	}
}

void ObjectManager::createItem(Vec2 pos, int expPoints)
{
	int randomNum = Random(400);

	// 300分の1の抽選で特殊弾のドロップ
	if (randomNum == 0)
	{
		randomNum = Random(1, 5);
		// ItemTypeと対応
		switch (randomNum)
		{
		case 1:
		{
			GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"NormalMagic", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
			if (tempItem) {
				Item* newItem = static_cast<Item*>(tempItem);
				newItem->setItemType(ItemType::NormalMagic);
				newItem->setActive(true);
				myItems << newItem;
			}
		}
		break;

		case 2:
		{
			GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"SpecialMagicA", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
			if (tempItem) {
				Item* newItem = static_cast<Item*>(tempItem);
				newItem->setItemType(ItemType::SpecialMagicA);
				newItem->setActive(true);
				myItems << newItem;
			}
		}
		break;

		case 3:
		{
			GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"SpecialMagicB", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
			if (tempItem) {
				Item* newItem = static_cast<Item*>(tempItem);
				newItem->setItemType(ItemType::SpecialMagicB);
				newItem->setActive(true);
				myItems << newItem;
			}
		}
		break;

		case 4:
		{
			GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"SpecialMagicC", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
			if (tempItem) {
				Item* newItem = static_cast<Item*>(tempItem);
				newItem->setItemType(ItemType::SpecialMagicC);
				newItem->setActive(true);
				myItems << newItem;
			}
		}
		break;

		case 5:
		{
			GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"SpecialMagicD", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
			if (tempItem) {
				Item* newItem = static_cast<Item*>(tempItem);
				newItem->setItemType(ItemType::SpecialMagicD);
				newItem->setActive(true);
				myItems << newItem;
			}
		}
		break;
		}
	}
	else
	{
		GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"Experience", Circle{ 10 }, pos, { 0, 0 }, { 0, 0 });
		if (tempItem) {
			Item* newItem = static_cast<Item*>(tempItem);
			newItem->setItemType(ItemType::ExpPoint);
			newItem->setExp(expPoints);
			newItem->setActive(true);
			myItems << newItem;
		}
	}
}

void ObjectManager::createItemConfirm(Vec2 pos, int ItemNum)
{
	if (ItemNum < 1)
	{
		ItemNum = Random(1, 5);
	}
	switch (ItemNum)
	{
	case 1:
	{
		GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"NormalMagic", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
		if (tempItem) {
			Item* newItem = static_cast<Item*>(tempItem);
			newItem->setItemType(ItemType::NormalMagic);
			newItem->setActive(true);
			myItems << newItem;
		}
	}
	break;

	case 2:
	{
		GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"SpecialMagicA", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
		if (tempItem) {
			Item* newItem = static_cast<Item*>(tempItem);
			newItem->setItemType(ItemType::SpecialMagicA);
			newItem->setActive(true);
			myItems << newItem;
		}
	}
	break;

	case 3:
	{
		GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"SpecialMagicB", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
		if (tempItem) {
			Item* newItem = static_cast<Item*>(tempItem);
			newItem->setItemType(ItemType::SpecialMagicB);
			newItem->setActive(true);
			myItems << newItem;
		}
	}
	break;

	case 4:
	{
		GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"SpecialMagicC", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
		if (tempItem) {
			Item* newItem = static_cast<Item*>(tempItem);
			newItem->setItemType(ItemType::SpecialMagicC);
			newItem->setActive(true);
			myItems << newItem;
		}
	}
	break;

	case 5:
	{
		GameObject* tempItem = ObjectAppearanceManager::createNewObject(eItem, 1, 0, U"SpecialMagicD", Circle{ 20 }, pos, { 0, 0 }, { 0, 0 });
		if (tempItem) {
			Item* newItem = static_cast<Item*>(tempItem);
			newItem->setItemType(ItemType::SpecialMagicD);
			newItem->setActive(true);
			myItems << newItem;
		}
	}
	break;
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
		enemy.hp = Parse<double>(csv[row][1]);
		enemy.damage = Parse<int>(csv[row][2]);
		enemy.textureStr = csv[row][3];
		enemy.hitbox = ObjectManager::parseFigure(csv[row][4]);
		enemy.speed = Parse<double>(csv[row][5]);

		enemyDatas[enemy.name] = enemy; // エネミー名をキーとして、その情報をマップに保存
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

void ObjectManager::stopEnemies()
{
	for (auto& enemy : myEnemies) {
		enemy->setSpeed(0);
	}
}

void ObjectManager::switchSpecialBullet()
{
	if (KeySpace.down() || MouseM.down())
	{
		const auto& availableBullets = myPlayer->availableBullet;

		if (availableBullets.empty()) {
			currentState = BulletType::None;
			currentIndex = -1;
		}
		else {
			// ハッシュマップのキーを配列として取得
			Array<ItemType> keys;
			for (const auto& pair : availableBullets) {
				keys << pair.first;
			}

			// 現在のインデックスを更新
			currentIndex = (currentIndex + 1) % keys.size();

			// 現在選択されているアイテムタイプを取得
			selectedItemType = keys[currentIndex];

			// BulletTypeに変換
			currentState = fromItemType(selectedItemType);
		}
	}
}


BulletType ObjectManager::fromItemType(ItemType itemType)
{
	switch (itemType)
	{
	case ItemType::SpecialMagicA:
		return BulletType::SpecialA;
	case ItemType::SpecialMagicB:
		return BulletType::SpecialB;
	case ItemType::SpecialMagicC:
		return BulletType::SpecialC;
	case ItemType::SpecialMagicD:
		return BulletType::SpecialD;
	default:
		return BulletType::None;
	}
}

void ObjectManager::setDelayTimer()
{
	BulletProperty bp = myPlayer->createNormalProperty();
	if (bulletTimer.duration().count() != bp.delay)
	{
		bulletTimer.set(SecondsF(bp.delay));
	}

	bp = myPlayer->createLaserProperty();
	if (specialBulletTimer[BulletType::SpecialA].duration().count() != bp.delay)
	{
		specialBulletTimer[BulletType::SpecialA].set(SecondsF(bp.delay));
	}

	bp = myPlayer->createWideProperty();
	if (specialBulletTimer[BulletType::SpecialB].duration().count() != bp.delay)
	{
		specialBulletTimer[BulletType::SpecialB].set(SecondsF(bp.delay));
	}

	bp = myPlayer->createPrasmaProperty();
	if (specialBulletTimer[BulletType::SpecialC].duration().count() != bp.delay)
	{
		specialBulletTimer[BulletType::SpecialC].set(SecondsF(bp.delay));
	}

	bp = myPlayer->createMineProperty();
	if (specialBulletTimer[BulletType::SpecialD].duration().count() != bp.delay)
	{
		specialBulletTimer[BulletType::SpecialD].set(SecondsF(bp.delay));
	}

}

double ObjectManager::calcDistance(const Vec2& a, const Vec2& b)
{
	return (a - b).length();
}

Enemy* ObjectManager::findClosestEnemy()
{
	Enemy* closest = nullptr;
	double minDistance = std::numeric_limits<double>::max();
	Vec2 playerPos = myPlayer->getPos();

	for (auto* enemy : myEnemies) {
		double dist = calcDistance(playerPos, enemy->getPos());
		if (dist < minDistance) {
			minDistance = dist;
			closest = enemy;
		}
	}

	return closest;
}

void ObjectManager::drawArrow(const Vec2& from, const Vec2& to, Vec2 offset)
{
	const Texture& arrowTexture = TextureAsset(U"Yajirusi");

	// ベクトルの角度を計算（ラジアン）
	Vec2 direction = to - from;
	double angle = Math::Atan2(direction.y, direction.x);

	// 矢印のテクスチャを回転させて描画
	arrowTexture.rotated(angle + 90).drawAt(from - offset);
}

void ObjectManager::updateAndDrawArrow(Vec2 offset) {
	Vec2 playerPos = myPlayer->getPos();
	Enemy* closestEnemy = findClosestEnemy();

	// 特定の距離以上離れているか
	if (closestEnemy && calcDistance(playerPos, closestEnemy->getPos()) > 800) {
		// 矢印を描画する
		drawArrow(playerPos, closestEnemy->getPos(), offset);
	}
}

// アイテム用のcleanUP
void ObjectManager::cleanUp(Array<Item*>& items)
{
	for (auto it = items.begin(); it != items.end();) {
		if (!(*it)->getIsActive()) {
			delete* it;
			it = items.erase(it);
		}
		else {
			++it;
		}
	}
}
