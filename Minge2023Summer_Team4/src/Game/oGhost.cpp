#include "oGhost.h"

Ghost::~Ghost()
{
}

void Ghost::update(const Vec2& playerPos, const String& playerDirection) {
	// プレイヤーの位置に少し遅れて追従する
	pos = pos.lerp(playerPos, 0.1);

	// プレイヤーの向きに応じてゴーストの向きを変更
	if (playerDirection == U"right") {
		currentDirection = U"right";
	}
	else if (playerDirection == U"left") {
		currentDirection = U"left";
	}
	else if (playerDirection == U"up") {
		currentDirection = U"up";
	}
	else
	{
		currentDirection = U"left";
	}

	// アニメーションの更新
	updateAnimation();
}

void Ghost::draw(Vec2 offset) const
{
	if (ghostAnimations.contains(currentDirection)) {
		const auto& frames = ghostAnimations.at(currentDirection);
		if (!frames.isEmpty()) {
			size_t frameIndex = animationFrame % frames.size();  // size_t型の一時変数を使用
			frames[frameIndex].resized(48, 48).draw(pos - Vec2(64, 64) - offset);
		}
	}
}

void Ghost::setupAnimations() {
	// ゴーストのテクスチャを読み込む
	const Texture& ghostTexture = TextureAsset(U"Ghost");

	// テクスチャを24x24ピクセルの領域に分割
	auto regions = splitImage(ghostTexture, 24 * EXPORT_SCALE, 24 * EXPORT_SCALE);

	// 各向きごとのアニメーションフレームを設定
	ghostAnimations[U"right"] = { regions[0], regions[1], regions[2], regions[3] };
	ghostAnimations[U"left"] = { regions[4], regions[5], regions[6], regions[7] };
	ghostAnimations[U"up"] = { regions[8], regions[9], regions[10], regions[11] };
}

void Ghost::updateAnimation() {
	// デルタタイムをアニメーションタイマーに加算
	animationTimer += Scene::DeltaTime();

	// タイマーがアニメーションの更新間隔を超えた場合
	if (animationTimer >= animationInterval) {
		// アニメーションフレームをインクリメント
		animationFrame++;

		// 現在の方向のアニメーションフレームの最大数を取得
		int maxFrames = ghostAnimations[currentDirection].size();

		// フレーム数が最大を超えた場合、リセット
		if (animationFrame >= maxFrames) {
			animationFrame = 0;
		}

		// アニメーションタイマーをリセット
		animationTimer = 0.0;
	}
}

