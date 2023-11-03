#pragma once
# include "oGameObject.h"
# include "../Define.h"
# include "oItem.h"

class Item;

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

	// 各方向のアニメーションフレームを格納するHashTable
	HashTable<String, Array<TextureRegion>> playerAnimations;

	const Texture tempTexture{ U"💩"_emoji };

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

	int expPoints;
	int level;
	int nextLevelExp;

	double maxHp;
	double regenDelay = 5.0; // 5秒の遅延
	double regeneVal = 0.1;

	double attractionRadius = 100;
	double attractionSpeed = 10;

	bool bIsItemEmpty = true;

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

	bool isDead();
	void playDeathAnimation();

	bool deathAnimationFinished() const;
	void updateDirectionToMouse();

	void onItemPickUp(Item*);

	void gainExp(int);
	void checkLevelUp();
	void levelUp();
	void applyItemEffect(Item*);

	void attractItems(Array<Item*>& items);

	void regenerateHp(double);

	// 取得した特殊弾とその個数
	HashTable<ItemType, int>availableBullet =
	{
			{ ItemType::SpecialMagicA, 0},
			{ ItemType::SpecialMagicB, 0},
			{ ItemType::SpecialMagicC, 0},
			{ ItemType::SpecialMagicD, 0},
	};

	//getter
	double getAttractionRadius() const;
	double getAttractionSpeed() const;
	int getLevel() const;
	int getNextlevelExp() const;
	int getMaxHp() const;

	//setter
	void setAttractionRadius(double);
	void setAttractionSpeed(double);

	// 現在のプレイヤーの向き
	String currentDirection = U"up";
	int normalMagicLevel;
	double bulletDelayElapsed = 0.0;

	BulletProperty createNormalProperty();
	BulletProperty createMineProperty();
	BulletProperty createWideProperty();
	BulletProperty createPrasmaProperty();
	BulletProperty createLaserProperty();

	bool isItemEmpty();
};
