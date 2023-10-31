#include "oPlayer.h"

// 静的メンバー変数の初期化
Player* Player::instance = nullptr;

Player::Player(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, double speed_)
	:speed(speed_), GameObject(eObjectType::ePlayer, hp_, damage_,textureStr,hitbox_, pos_, { 0,0 }, { 0,0 }),
	expPoints(0), level(1), nextLevelExp(100)
{
	setupAnimations();
	changeCoolTime(1s);
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

	// アニメーションを更新
	updateAnimation();

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
}


void Player::move() {
	const double deltaTime = Scene::DeltaTime();
	Vec2 moveDir = { 0,0 };
	getMoveDirection(moveDir);

	// 進行方向を保存
	Vec2 normalizedMoveDir = moveDir.normalized();

	if (normalizedMoveDir.length() > 0)
	{
		Logger << speed;
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
	this->playerAnimations.at(currentDirection)[animationFrame].drawAt(pos - offset);
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

bool Player::deathAnimationFinished() const {
	try {
		return isDeadAnimationPlaying && (animationFrame == playerAnimations.at(U"dead").size() - 1);
	}
	catch (const std::out_of_range&) {
		// エントリが存在しない場合の処理
		return false;
	}
}

void Player::updateAnimation() {
	// デルタタイムをアニメーションタイマーに加算
	animationTimer += Scene::DeltaTime();

	// タイマーがアニメーションの更新間隔を超えた場合
	if (animationTimer >= animationInterval) {
		// アニメーションフレームをインクリメント
		animationFrame++;

		// 現在の方向のアニメーションフレームの最大数を取得
		int maxFrames = playerAnimations[currentDirection].size();

		// フレーム数が最大を超えた場合、リセット
		if (animationFrame >= maxFrames) {
			animationFrame = 0;
		}

		// アニメーションタイマーをリセット
		animationTimer = 0.0;
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
	nextLevelExp += (level * 50); // 次のレベルに必要な経験値を増加させる

	// その他レベルアップ時の処理
	switch (level % 4) {
	case 0:
		hp += 10; // 体力を10増加
		
		break;
	case 1:
		damage += 5; // ダメージを5増加
		
		break;
	case 2:
		speed += 10; // スピードを1増加
		
		break;
	case 3:
		attractionRadius += 10; // アイテム収集範囲を10増加
		
		break;
	}

	// その他レベルアップ時の処理
}

void Player::applyItemEffect(Item* item) {
	if (item->getItemType() == ItemType::ExpPoint)
	{
		// アイテムが経験値を持っている場合、プレイヤーの経験値を増加させる
		int expPoints = item->getExp();  // アイテムから経験値の量を取得
		gainExp(expPoints);
	}
	else if (item->getItemType() == ItemType::NormalMagic)
	{
		levelNormal+= 1;
	}
	else if (item->getItemType() == ItemType::SpecialMagicA)
	{
		if (availableBullet.includes(ItemType::SpecialMagicA))
		{
			levelSpecialA += 1;
		}
		else
		{
			availableBullet << ItemType::SpecialMagicA;
		}
	}
	else if (item->getItemType() == ItemType::SpecialMagicB)
	{
		if (availableBullet.includes(ItemType::SpecialMagicB))
		{
			levelSpecialB += 1;
		}
		else
		{
			availableBullet << ItemType::SpecialMagicB;
		}
	}
	else if (item->getItemType() == ItemType::SpecialMagicC)
	{
		if (availableBullet.includes(ItemType::SpecialMagicC))
		{
			levelSpecialC += 1;
		}
		else
		{
			availableBullet << ItemType::SpecialMagicC;
		}
	}
	else if (item->getItemType() == ItemType::SpecialMagicD)
	{
		if (availableBullet.includes(ItemType::SpecialMagicD))
		{
			levelSpecialD += 1;
		}
		else
		{
			availableBullet << ItemType::SpecialMagicD;
		}
	}

}

void Player::attractItems(Array<Item*>& items)
{
	for (Item* item : items) {
		if (item->getItemType() == ItemType::ExpPoint) {
			Vec2 direction = item->getPos() - pos; // アイテムへの方向ベクトル
			double distance = direction.length();

			if (distance < attractionRadius) {
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

int Player::getBulletLevel(BulletType bulletType) const
{
	switch (bulletType)
	{
	case BulletType::Normal:
		return levelNormal;
	case BulletType::SpecialA:
		return levelSpecialA;
	case BulletType::SpecialB:
		return levelSpecialB;
	case BulletType::SpecialC:
		return levelSpecialC;
	case BulletType::SpecialD:
		return levelSpecialD;
	}
}

int Player::getNextlevelExp() const
{
	return this->nextLevelExp;
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

