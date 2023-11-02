#include "oGhost.h"

Ghost::~Ghost()
{
}

void Ghost::update(const Vec2& playerPos, const String& playerDirection) {
	// プレイヤーの位置に少し遅れて追従する
	this->pos = pos.lerp(playerPos, 0.1);

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
	GameObject::updateAnimation();
}

void Ghost::draw(Vec2 offset) const
{
	animationDraw(offset);
}

void Ghost::animationDraw(Vec2 offset) const
{
	if (animations.contains(currentDirection)) {
		const auto& frames = animations.at(currentDirection);
		if (!frames.isEmpty()) {
			size_t frameIndex = animationFrame % frames.size();  // size_t型の一時変数を使用
			frames[frameIndex].resized(32, 32).draw(pos - Vec2(64, 64) - offset);
		}
	}
}

void Ghost::setupAnimations() {
	// ゴーストのテクスチャを読み込む
	const Texture& ghostTexture = TextureAsset(U"Ghost");

	// テクスチャを24x24ピクセルの領域に分割
	auto regions = splitImage(ghostTexture, 24 * EXPORT_SCALE, 24 * EXPORT_SCALE);

	// 各向きごとのアニメーションフレームを設定
	animations[U"right"] = { regions[0], regions[1], regions[2], regions[3] };
	animations[U"left"] = { regions[4], regions[5], regions[6], regions[7] };
	animations[U"up"] = { regions[8], regions[9], regions[10], regions[11] };
}
