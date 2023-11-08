#include "oPlayer.h"

// 静的メンバー変数の初期化
Player* Player::instance = nullptr;

Player::Player(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, double speed_)
	:speed(speed_), GameObject(eObjectType::ePlayer, hp_, damage_, textureStr, hitbox_, pos_, { 0,0 }, { 0,0 }),
	expPoints(0), level(1), nextLevelExp(100)
{
	setupAnimations();
	changeCoolTime(1s);

	maxHp = hp;
	previousHp = hp;

	normalMagicLevel = 1;


}

Player::~Player()
{
}


Player* Player::getInstance()
{
	return instance;
}

void Player::create(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, double speed_)
{
	if (instance == nullptr)
	{
		instance = new Player(hp_, damage_, textureStr, hitbox_, pos_, speed_);
	}
}

void Player::destroy()
{
	delete instance;
	instance = nullptr;
}

void Player::update() {

	updateCommon();

	// プレイヤーの向きをマウスカーソルの位置に基づいて更新
	updateDirectionToMouse();

	move();

	// プレイヤーが動いている場合のみアニメーションフレームを更新
	if (isMoving) {
		animationDuration++;
		if (animationDuration % animationSpeed == 0) {
			animationFrame = (animationFrame + 1) % playerAnimations.at(currentDirection).size();
		}
	}
	else {
		// プレイヤーが動いていない場合、アニメーションの最初のフレームを表示
		animationFrame = 0;
	}

	// ダメージを受けたことを検知
	if (previousHp > hp) {
		damageDelayElapsed = 0.0;
	}
	else
	{
		damageDelayElapsed += Scene::DeltaTime();
	}

	regenerateHp(regeneVal);

	previousHp = hp; // 現在のHPを前フレームのHPとして保存
	if (hp <= 0)
	{
		hp = 0;
	}
}

void Player::regenerateHp(double regeneVal) {
	if (damageDelayElapsed > regenDelay)
	{

		if (isMoving == true) regeneVal *= 0.25;

		hp += regeneVal;

		if (hp > maxHp)
		{
			hp = maxHp;
		}
	}
}

void Player::move() {
	const double deltaTime = Scene::DeltaTime();
	Vec2 moveDir = { 0,0 };
	getMoveDirection(moveDir);

	// 進行方向を保存
	Vec2 normalizedMoveDir = moveDir.normalized();

	if (normalizedMoveDir.length() > 0)
	{
		pos += normalizedMoveDir * speed * deltaTime;
		setPos(pos);
		isMoving = true;
	}
	else
	{
		isMoving = false;
	}
}

void Player::getMoveDirection(Vec2& moveDir)
{
	isMoving = false;  // まず動いていないと仮定

	if (KeyW.pressed())
	{
		moveDir.y -= 1;
		isMoving = true;
	}
	if (KeyA.pressed())
	{
		moveDir.x -= 1;
		isMoving = true;
	}
	if (KeyS.pressed())
	{
		moveDir.y += 1;
		isMoving = true;
	}
	if (KeyD.pressed())
	{
		moveDir.x += 1;
		isMoving = true;
	}
}

void Player::draw(Vec2 offset, bool isHitboxDraw) const
{
	// playerAnimations 内に currentDirection が存在するか確認
	if (playerAnimations.find(currentDirection) == playerAnimations.end()) {
		return;
	}

	// animationFrame が現在の方向のテクスチャリージョン配列の範囲内にあるか確認
	if (animationFrame < 0 || animationFrame >= playerAnimations.at(currentDirection).size()) {
		return;
	}

	// アニメーションのフレームを描画
	this->playerAnimations.at(currentDirection)[animationFrame].resized(64, 64).drawAt(pos - offset, ColorF{ 1.0, isBlinkShift ? 0.5 : 1 });
	if (isHitboxDraw) drawHitbox(-offset); // ヒットボックスを描画	
}

void Player::setupAnimations()
{
	// TextureAssetからテクスチャを直接取得
	const Texture& playerTexture = TextureAsset(U"playerImage");

	auto regions = splitImage(playerTexture, 24 * EXPORT_SCALE, 24 * EXPORT_SCALE);

	playerAnimations[U"down"] = { regions[0], regions[1], regions[2], regions[3] };
	playerAnimations[U"left"] = { regions[4], regions[5], regions[6], regions[7] };
	playerAnimations[U"right"] = { regions[8], regions[9], regions[10], regions[11] };
	playerAnimations[U"up"] = { regions[12], regions[13], regions[14], regions[15] };
	playerAnimations[U"dead"] = { regions[16], regions[17], regions[18], regions[19] };
}

bool Player::isDead() {
	if (hp <= 0) return true;
	else return false;
}

void Player::playDeathAnimation() {
	if (!isDeadAnimationPlaying) {
		currentDirection = U"dead";  // 死亡アニメーションへの方向を設定
		animationFrame = 0;  // アニメーションフレームをリセット
		isDeadAnimationPlaying = true;  // フラグを設定
		animationDuration = 0;
	}

	 //アニメーションフレームのインクリメント
	if (isDeadAnimationPlaying) {
		animationDuration++;
		if (animationDuration % animationSpeed == 0) {
			animationFrame++;
			if (animationFrame >= playerAnimations[U"dead"].size()) {
				animationFrame = playerAnimations[U"dead"].size() - 1;  // アニメーションの最後のフレームに留める
			}
		}
	}
}

bool Player::deathAnimationFinished() const
{
	try {
		return isDeadAnimationPlaying && (animationFrame == playerAnimations.at(U"dead").size() - 1);
	}
	catch (const std::out_of_range&) {
		// エントリが存在しない場合の処理
		return false;
	}
}

void Player::updateDirectionToMouse() {
	// マウスカーソルとプレイヤーの位置の差分を計算
	Vec2 diff = (Cursor::PosF() - Scene::CenterF()).setLength(1);

	// atan2を使用して角度を計算（ラジアン）
	double angle = Atan2(diff.y, diff.x);

	// 角度を度数法に変換
	double degree = ToDegrees(angle);

	// 角度に基づいて向きを変更
	if (degree >= -45 && degree < 45) {
		currentDirection = U"right";
	}
	else if (degree >= 45 && degree < 135) {
		currentDirection = U"down";
	}
	else if ((degree >= 135 && degree <= 180) || (degree < -135 && degree >= -180)) {
		currentDirection = U"left";
	}
	else {
		currentDirection = U"up";
	}
}

void Player::onItemPickUp(Item* item)
{
	// アイテムを取得した際の処理
	applyItemEffect(item);

	// アイテムを非アクティブに設定
	item->setActive(false);
}

void Player::gainExp(int points)
{
	int expPoints = getExp();
	expPoints += points;
	setExp(expPoints);
	checkLevelUp();

	// 経験値を増加させた後の処理（レベルアップ処理等）をここに記述
}

// レベルアップの確認を行うメソッド
void Player::checkLevelUp()
{
	while (getExp() >= nextLevelExp) {
		expPoints -= nextLevelExp;
		level++;
		levelUp();
	}
}

// レベルアップ時の処理を行うメソッド
void Player::levelUp()
{
	nextLevelExp += (level * 70); // 次のレベルに必要な経験値を増加させる

	// その他レベルアップ時の処理
	switch (level % 4) {
	case 0:
		maxHp += 5; // 体力を10増加
		regeneVal += 0.05;
		
		break;
	case 1:
		damage += 5; // 
		
		break;
	case 2:
		if (speed <= 500)
		{
			speed += 5; // スピードを1増加
		}
		break;
	case 3:
		attractionRadius += 5; // アイテム収集範囲を10増加
		
		break;
	}

	// その他レベルアップ時の処理
}

void Player::applyItemEffect(Item* item) {
	ItemType itemType = item->getItemType();
	if (itemType == ItemType::ExpPoint)
	{
		// アイテムが経験値を持っている場合、プレイヤーの経験値を増加させる
		int expPoints = item->getExp();  // アイテムから経験値の量を取得
		gainExp(expPoints);
	}
	else if  (itemType == ItemType::NormalMagic)
	{
		normalMagicLevel += 1;
	}
	else
	{
		if (availableBullet.contains(itemType))
		{
			// 既にアイテムが存在する場合、個数を1増やす
			availableBullet[itemType] += 1;
		}
		else
		{
			// アイテムが存在しない場合、個数を1で初期化して追加
			availableBullet[itemType] = 1;
		}
	}
}


void Player::attractItems(Array<Item*>& items)
{
	for (Item* item : items)
	{
		if (item->getItemType() == ItemType::ExpPoint) {
			Vec2 direction = item->getPos() - pos; // アイテムへの方向ベクトル
			double distance = direction.length();

			if (distance < attractionRadius)
			{
				// 吸い寄せの計算
				Vec2 attraction = direction.normalized() * attractionSpeed; // attractionSpeedは吸い寄せる速度
				item->setPos(item->getPos() - attraction);
			}
		}
	}
}

//ゲット関数

double Player::getAttractionRadius() const
{
	return this->attractionRadius;
}

double Player::getAttractionSpeed() const
{
	return this->attractionSpeed;
}

int Player::getLevel() const
{
	return this->level;
}

int Player::getNextlevelExp() const
{
	return this->nextLevelExp;
}

int Player::getMaxHp() const
{
	return this->maxHp;
}

// セット関数

void Player::setAttractionRadius(double radius)
{
	this->attractionRadius = radius;
}

void Player::setAttractionSpeed(double speed)
{
	this->attractionSpeed = speed;
}

void Player::setMaxHp(int hp)
{
	this->maxHp = hp;
}

void Player::setSpeed(double speed)
{
	this->speed = speed;
}

void Player::setHp(double)
{
	this->hp = hp;

}

BulletProperty Player::createNormalProperty()
{
	BulletProperty bp;
	switch (normalMagicLevel)
	{
		case 1:
			bp.way = 1; bp.damage = 20; bp.speed = 300; bp.size = 10; bp.delay = 1.0;
			break;
		case 2:
			bp.way = 1; bp.damage = 25; bp.speed = 500; bp.size = 12; bp.delay = 0.8;
			break;
		case 3:
			bp.way = 3; bp.damage = 30; bp.speed = 500; bp.size = 12; bp.delay = 0.8;
			break;
		case 4:
			bp.way = 5; bp.damage = 40; bp.speed = 600; bp.size = 14; bp.delay = 0.6;
			break;
		case 5:
			bp.way = 7; bp.damage = 50; bp.speed = 700; bp.size = 14; bp.delay = 0.5;
			break;
		case 6:
			bp.way = 7; bp.damage = 60; bp.speed = 1000; bp.size = 16; bp.delay = 0.3;
			break;
		default:
			bp.way = 7; bp.damage = 60 + normalMagicLevel; bp.speed = 1000; bp.size = 10 + normalMagicLevel; bp.delay = 0.3;
	}
	return bp;

}

BulletProperty Player::createMineProperty()
{
	BulletProperty bp;
	switch (availableBullet[ItemType::SpecialMagicD])
	{
	case 0:
		break;
	case 1:
		bp.damage = 60; bp.size = 10; bp.delay = 3.0; bp.exproRange = 100;
		break;
	case 2:
		bp.damage = 80; bp.size = 12; bp.delay = 2.5; bp.exproRange = 125;
		break;
	case 3:
		bp.damage = 100; bp.size = 12; bp.delay = 2.0; bp.exproRange = 150;
		break;
	case 4:
		bp.damage = 120; bp.size = 14; bp.delay = 1.5; bp.exproRange = 175;
		break;
	case 5:
		bp.damage = 140; bp.size = 14; bp.delay = 1.0; bp.exproRange = 200;
		break;
	case 6:
		bp.damage = 180; bp.size = 16; bp.delay = 0.3; bp.exproRange = 225;
		break;
	default:
		bp.damage = 200 + availableBullet[ItemType::SpecialMagicD] * 2; bp.delay = 0.3; bp.exproRange = 225 + availableBullet[ItemType::SpecialMagicD] * 2;
	}
	return bp;
}

BulletProperty Player::createWideProperty()
{
	BulletProperty bp;
	switch (availableBullet[ItemType::SpecialMagicB])
	{
	case 0:
		break;
	case 1:
		bp.hp = 1; bp.damage = 60; bp.size = 20; bp.delay = 3.0;
		break;
	case 2:
		bp.hp = 10; bp.damage = 70; bp.size = 30; bp.delay = 1.5;
		break;
	case 3:
		bp.hp = 100; bp.damage = 100; bp.size = 40; bp.delay = 1.0;
		break;
	case 4:
		bp.hp = 100; bp.damage = 120; bp.size = 45; bp.delay = 0.7;
		break;
	case 5:
		bp.hp = 500; bp.damage = 150; bp.size = 60; bp.delay = 0.3;
		break;
	case 6:
		bp.hp = 1000; bp.damage = 200; bp.size = 80; bp.delay = 0.1;
		break;
	default:
		bp.damage = 200 + availableBullet[ItemType::SpecialMagicB] * 2; bp.delay = 0.3; bp.hp = 1000 + availableBullet[ItemType::SpecialMagicB] * 2;
		bp.size = 100;
	}
	return bp;
}

BulletProperty Player::createPrasmaProperty()
{
	BulletProperty bp;
	switch (availableBullet[ItemType::SpecialMagicC])
	{
	case 0:
		break;
	case 1:
		bp.hp = 100; bp.damage = 80; bp.size = 40; bp.delay = 10.0;
		break;
	case 2:
		bp.hp = 300; bp.damage = 100; bp.size = 45; bp.delay = 8.0;
		break;
	case 3:
		bp.hp = 500; bp.damage = 110; bp.size = 50; bp.delay = 6.0;
		break;
	case 4:
		bp.hp = 800; bp.damage = 150; bp.size = 65; bp.delay = 4.0;
		break;
	case 5:
		bp.hp = 1000; bp.damage = 200; bp.size = 70; bp.delay = 2.5;
		break;
	case 6:
		bp.hp = 1500; bp.damage = 240; bp.size = 85; bp.delay = 1.0;
		break;
	default:
		bp.damage = 50 + availableBullet[ItemType::SpecialMagicC] * 2; bp.delay = 0.3; bp.hp = 50 + availableBullet[ItemType::SpecialMagicC] * 2; bp.size = 85;

		bp.hp = 800;
		bp.damage = 50 + availableBullet[ItemType::SpecialMagicC] * 2;
		bp.size = 90;
		bp.delay = 0.3; bp.hp = 50 + availableBullet[ItemType::SpecialMagicC] * 2;
	}
	return bp;
}

BulletProperty Player::createLaserProperty()
{
	BulletProperty bp;
	switch (normalMagicLevel)
	{
	case 1:
		bp.way = 1; bp.damage = 20; bp.speed = 300; bp.size = 10; bp.delay = 2.0;
		break;
	case 2:
		bp.way = 1; bp.damage = 30; bp.speed = 500; bp.size = 12; bp.delay = 2.0;
		break;
	case 3:
		bp.way = 3; bp.damage = 30; bp.speed = 500; bp.size = 12; bp.delay = 1.5;
		break;
	case 4:
		bp.way = 3; bp.damage = 40; bp.speed = 600; bp.size = 14; bp.delay = 1.0;
		break;
	case 5:
		bp.way = 5; bp.damage = 40; bp.speed = 700; bp.size = 14; bp.delay = 0.5;
		break;
	case 6:
		bp.way = 5; bp.damage = 50; bp.speed = 1000; bp.size = 16; bp.delay = 0.3;
		break;
	default:
		bp.way = 7; bp.damage = 70 + normalMagicLevel; bp.speed = 1000; bp.size = 10 + normalMagicLevel; bp.delay = 0.3;
	}
	return bp;
}
