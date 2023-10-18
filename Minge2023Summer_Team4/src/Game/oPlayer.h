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

	// プレイヤーの画像を読み込む
	Texture playerImage = TextureAsset(U"playerImage");

	// 画像の保存倍率
	static constexpr double EXPORT_SCALE = 4.0;  // 400% => 4.0倍

	// 各方向のアニメーションフレームを格納するHashTable
	HashTable<String, Array<TextureRegion>> playerAnimations;

	const Texture tempTexture{ U"💩"_emoji };

	// 現在のプレイヤーの向き
	String currentDirection = U"up";

	bool isDeadAnimationPlaying = false;

	// アニメーションのフレームの経過時間をカウント
	int animationDuration = 0;

	// この値は、1フレームあたりのアップデートの頻度を示す。値が大きいほどアニメーションは遅くなる
	const int animationSpeed = 10;

	// アニメーションを制御するための変数
	double animationTimer = 0.0; // アニメーションのタイマー
	const double animationInterval = 0.2; // アニメーションフレームの更新間隔（0.2秒ごとに更新）
	int animationFrame;

	const double repelDistance = 10;
	double speed;

protected:

public:

	// 唯一のインスタンスを取得するための静的メソッド
	static Player* getInstance();

	// 唯一のインスタンスを作成
	static void create(int hp_, int damage_, String textureStr, Figure hitbox_, Vec2 pos_, double speed_);

	// デストラクタ
	static void destroy();


	void update() override;


	void move() override;
	void getMoveDirection(Vec2& moveDir);


	void draw(Vec2 offset, bool isHitboxDraw) const override;

	void setupAnimations();

	Array<TextureRegion> splitImage(const Texture& texture, int cellWidth, int cellHeight);

	bool isDead();
	void playDeathAnimation();

	bool deathAnimationFinished() const;

	void updateAnimation();

	void updateDirectionToMouse();

};
