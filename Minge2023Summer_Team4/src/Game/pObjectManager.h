# pragma once
# include "../Define.h"
# include "../Figure.h"
# include "pObjectAppearanceManager.h"
# include "pEventManager.h"
# include "oPlayer.h"
# include "oDebris.h"
# include "oBullet.h"
# include "oEnemy.h"
# include "oItem.h"
# include "pEffectManager.h"
#include "../pSoundPlayer.h"
# include "oGhost.h";

class ObjectAppearanceManager;
class Player;

class ObjectManager
{
private:

	Timer bulletTimer{ 0.5s, StartImmediately::Yes };
	HashTable<BulletType, Timer> specialBulletTimer =
	{
		{ BulletType::SpecialA, Timer{ 1s, StartImmediately::No } },
		{ BulletType::SpecialB, Timer{ 1s, StartImmediately::No } },
		{ BulletType::SpecialC, Timer{ 1s, StartImmediately::No } },
		{ BulletType::SpecialD, Timer{ 1s, StartImmediately::No } },
	};



	SoundPlayer* mySoundPlayer;
	EffectManager* myEffectManager;
	Ghost* myGhost;

	template<typename T, typename U>
	void checkCollision(T* obj1, U* obj2);

	template<typename T, typename U>
	void checkCollisions(T* obj, Array<U*>& objs);

	template<typename T, typename U>
	void checkCollisionsBetweenArrays(Array<T*>& objs1, Array<U*>& objs2);

	template<typename T>
	void cleanUp(Array<T*>& objs, Vec2 playerPos);
	template<typename T>
	void cleanUp(Array<T*>& objs);
	void cleanUp(Array<Item*>& items);

	template<typename T>
	void updateObjList(Array<T*>& objectList);

	bool gameEnd = false;

public:

	// 現在、どの特殊弾を選択しているかのState
	BulletType currentState; 

	// どの特殊弾にアクセスしているか
	int currentIndex;

	ItemType selectedItemType;

	// 各オブジェクトの配列
	Array<Debris*> myDebrises;
	Array<Bullet*> myPlayerBullets;
	Array<Bullet*> myEnemyBullets;
	Array<Enemy*> myEnemies;
	Array<Item*> myItems;

  
	// 敵の名前をキーとした敵情報を格納したハッシュテーブル
	HashTable<String, EnemyData> enemyDatas;

	~ObjectManager();
	ObjectManager();

	Player* myPlayer;
	
	void update();
	void collision();
	void draw(Vec2 offset) const;

	void createDebris();
	void createEnemy();
	void createPlayerBullet();
	void createBullet(Vec2 pos, Vec2 vel, const BulletProperty& bp, Vec2 acc, BulletType);
	void createEnemyBullet();
	void createSpecialBullet(Vec2, Vec2, Vec2);
	void createItem(Vec2, int);
	void createItemConfirm(Vec2 pos, int ItemNum = -1);

	HashTable<String, EnemyData> loadEnemyData(const String& filename);
	Array<WaveData> loadWaveData(const String& filename);

	Enemy* createEnemyFromData(WaveData waveData);
	static Figure parseFigure(const String&);
	void stopEnemies();
	void switchSpecialBullet();
	BulletType fromItemType(ItemType);

	void setDelayTimer();
	double calcDistance(const Vec2&, const Vec2&);

	Enemy* findClosestEnemy();
	void drawArrow(const Vec2&, const Vec2&, Vec2 offset);
	void updateAndDrawArrow(Vec2 offset);
};


// Collisionに関するテンプレート関数
template<typename T, typename U>
void ObjectManager::checkCollision(T* obj1, U* obj2) {
	if (obj1->isCollisional() && obj2->isCollisional() && obj1->getHitbox().intersects(obj2->getHitbox())) {

		if (obj1->getObjType() != eDebris) obj1->onCollisionResponse(obj2->getPos());  // 押し出しの応答をobj1に適用
		if (obj2->getObjType() != eDebris) obj2->onCollisionResponse(obj1->getPos());  // 押し出しの応答をobj2に適用


		// 敵同士の衝突でない場合のみダメージを適用
		// 10/31追記　debris-enemy間でもダメージを適用しない
		// 11/10追記　Itemでダメージ受けてどうすんだよ！！！！！！！
		if (obj1->getObjType() == eEnemy && obj2->getObjType() == eEnemy);
		else if (obj1->getObjType() == eDebris && obj2->getObjType() == eEnemy);
		else if (obj1->getObjType() == ePlayer && obj2->getObjType() == eItem);
		else
		{
			obj1->onCollisionResponse(obj2->getDamage()); // ダメージの応答をobj1に適用
			obj2->onCollisionResponse(obj1->getDamage()); // ダメージの応答をobj2に適用

		}
		
	}
}

template<typename T, typename U>
void ObjectManager::checkCollisions(T* obj, Array<U*>& objs) {
	for (auto& obj2 : objs)
	{
		checkCollision(obj, obj2);
	}
}

template<typename T, typename U>
void ObjectManager::checkCollisionsBetweenArrays(Array<T*>& objs1, Array<U*>& objs2) {
	for (auto& obj1 : objs1) {
		for (auto& obj2 : objs2) {
			checkCollision(obj1, obj2);
		}
	}
}
// playerPosを必要とするオブジェクトのためのcleanUp
template<typename T>
void ObjectManager::cleanUp(Array<T*>& objs, Vec2 playerPos) {
	int i = 0;
	for (auto it = objs.begin(); it != objs.end();)
	{
		if ((*it)->isDead(playerPos))
		{
			if ((*it)->isItemDrop() && (*it)->getObjType() == eObjectType::eDebris) {
				// デブリの位置でアイテムを生成
				Vec2 objPos = (*it)->getPos();
				int expPoints = (*it)->getExp();
				createItem(objPos, expPoints);
				if ((*it)->getObjType() == eObjectType::eDebris) mySoundPlayer->playEffect(effectHitDebris);
			}
			delete* it;
			it = objs.erase(it);
		}
		else
		{
			++it;
		}
	}
}

// playerPosを必要としないオブジェクトのためのcleanUp
template<typename T>
void ObjectManager::cleanUp(Array<T*>& objs) {
	for (auto it = objs.begin(); it != objs.end();) {
		if ((*it)->isDead()) {
			// オブジェクトの種類をチェック
			if ((*it)->getObjType() == eObjectType::eEnemy) {
				// 敵の位置でアイテムを生成
				Vec2 objPos = (*it)->getPos();
				int expPoints = (*it)->getExp();
				createItem(objPos, expPoints);
				myEffectManager->create_spliteEffect(objPos ,U"Effect1", 0.5, 100);
				defeatCount += 1;
				mySoundPlayer->playEffect(effectHit1);
			}

			delete* it;
			it = objs.erase(it);
		}
		else {
			++it;
		}
	}
}

// updateのためのテンプレート関数
template<typename T>
void ObjectManager::updateObjList(Array<T*>& objectList)
{
	for (auto& object : objectList) {
		object->update();
	}
}
