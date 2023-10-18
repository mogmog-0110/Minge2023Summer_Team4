#include "oPlayer.h"

// 静的メンバー変数の初期化
Player* Player::instance = nullptr;

Player::Player(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, double speed_)
	:speed(speed_), GameObject(eObjectType::ePlayer, hp_, damage_,textureStr,hitbox_, pos_, { 0,0 }, { 0,0 })
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


Array<TextureRegion> Player::splitImage(const Texture& texture, int cellWidth, int cellHeight)
{
	Array<TextureRegion> regions;

	for (int y = 0; y < texture.height(); y += cellHeight)
	{
		for (int x = 0; x < texture.width(); x += cellWidth)
		{
			regions << texture(Rect(x, y, cellWidth, cellHeight));
		}
	}

	return regions;
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
