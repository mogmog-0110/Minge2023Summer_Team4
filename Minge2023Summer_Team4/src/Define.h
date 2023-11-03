#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.11
# include "Figure.h"

// シーンの名前
enum class SceneList {
	Title,
	Game,
	Result
};

// 共有するデータ
struct GameData
{
	int something;
};

using App = SceneManager<SceneList, GameData>;

//　自分自身のオブジェクトタイプ
enum eObjectType {
	ePlayer,
	eEnemy,
	ePlayerBullet,
	eEnemyBullet,
	eDebris,
	eItem,
	eNone,
};

struct EnemyData {
	String name;
	int hp;
	int damage;
	String textureStr;
	Figure hitbox;
	double speed;
};

struct WaveData {
	double spawnTime;
	String enemyName;
	Vec2 spawnPos;
	double statusModifier; // 敵のステータスに掛けられる補正値
	int spawnCount;   
};

// ゲームの状態を表す
enum class GameState {
	Loading,
	Playing,
	Pausing,
	Scenario,
	Dead,
	Finished
};


// アイテムの種類を表す
enum class ItemType {
	ExpPoint,
	NormalMagic,
	SpecialMagicA,
	SpecialMagicB,
	SpecialMagicC,
	SpecialMagicD,
};

// バレットの種類とステイトを表す
enum class BulletType {
	Normal,
	SpecialA,
	SpecialB,
	SpecialC,
	SpecialD,
	None, // 特殊弾を取得していない
};

struct BulletProperty
{
	int hp;
	int damage;
	int size;
	double speed;

	double delay; // 弾生成の間隔
	int way; // 2way, 3way, 4way ...etc
	Array<Vec2> direction; // 弾の飛ぶ方向,実際にはVec2型として、velに格納

	// Wide用

	//Mine用
	int exproRange;
};

// 背景タイルの情報を保持する構造体
struct BackgroundTile
{
	Vec2 pos;  // タイルの位置
	int textureIndex;  // 使用するテクスチャのインデックス
};

const int FIELD_WIDTH = 100000;
const int FIELD_HEIGHT = 100000;


// 画像の保存倍率
static constexpr double EXPORT_SCALE = 4.0;  // 400% => 4.0倍

const int TILE_SIZE = 16 * EXPORT_SCALE; // タイルサイズ（ピクセル）

const int CHUNK_SIZE = 16; // チャンクサイズ（タイルの数）


struct BackgroundChunk {
	Array<BackgroundTile> tiles;  // このチャンクに含まれるタイルのリスト
	BackgroundChunk() {
		tiles.resize(CHUNK_SIZE * CHUNK_SIZE);
	}

	// (x, y)位置のタイルへの参照を返す関数
	BackgroundTile& getTile(int x, int y) {
		int index = y * CHUNK_SIZE + x;
		return tiles[index];
	}

	// (x, y)位置のタイルを描画する関数
	void draw(const Array<TextureRegion>& tileTextures, const Vec2& offset) const {
		for (const auto& tile : tiles) {
			if (0 <= tile.textureIndex && tile.textureIndex < tileTextures.size()) {
				tileTextures[tile.textureIndex].draw(tile.pos - offset);
			}
		}
	}
};

// グローバル関数（邪法）

Array<TextureRegion> splitImage(const Texture& texture, int cellWidth, int cellHeight);
