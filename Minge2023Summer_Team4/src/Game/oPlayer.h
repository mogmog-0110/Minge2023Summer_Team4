#pragma once
#include "oGameObject.h"
#include "../Define.h"

class Player :
    public GameObject
{
private:
	Player(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, double speed_);
	~Player();

	// コピーコンストラクタと代入演算子を非公開にする
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	// 唯一のインスタンスを格納する静的メンバー変数
	static Player* instance;

	const Texture tempTexture{ U"💩"_emoji };
	double speed;

protected:

public:

	// 唯一のインスタンスを取得するための静的メソッド
	static Player* getInstance();

	// 唯一のインスタンスを作成
	static void create(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, double speed_);


	void update() override;
	void move() override;

	void draw(Vec2 offset, bool isHitboxDraw) const override;
};

