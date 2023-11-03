#include "oGameObject.h"
#include "oPlayer.h"

GameObject::~GameObject()
{
	
}


//====================================================
//毎Tick実行するかんすう

void GameObject::update()
{
	updateCommon();
	move();
	updateAnimation();
}

void GameObject::updateCommon()
{
	if (velRepull.length() > 0.01) velRepull.setLength(velRepull.length() - repullDecaySpeed * Scene::DeltaTime());


	if (objType == eDebris || objType == eEnemy || objType == ePlayer )
	{
		if (blinkTimer1.isRunning())
		{
			if (!(blinkTimer2.isRunning()))
			{
				isBlinkShift = !isBlinkShift;
				blinkTimer2.restart();
			}
		}
		else
		{
			isBlinkShift = false;
		}
	}
}

void GameObject::move()
{
	// プレイヤーの座標の取得
	Player* myPlayer = Player::getInstance();
	Vec2 playerPos = myPlayer->getPos();

	Vec2 elementVector = (pos - playerPos).setLength(1);

	vel = elementVector.setLength(vel.length()) * (-1);
	pos += (vel + velRepull) * Scene::DeltaTime();

    setPos(pos);

}

//====================================================
//描画関連

void GameObject::draw(Vec2 offset, bool isHitboxDraw) const {
	Vec2 drawPos = pos - offset;

	// sizeはヒットボックスと大きさがほとんど一緒。OAMに渡す値で、ヒットボックスとテクスチャの大きさを決める。

	if (texture) {
		// テクスチャが存在すれば描画
		texture.resized(size, size).drawAt(drawPos, ColorF{ 1.0, isBlinkShift ? 0.5 : 1 });
	}
	else
	{
		drawAnimation(drawPos);
	}

	if (isHitboxDraw) {
		drawHitbox(-offset);
	}
}

void GameObject::drawAnimation(Vec2 drawPos) const
{
	if (animations.contains(currentDirection)) {
		const auto& frames = animations.at(currentDirection);
		if (!frames.isEmpty())
		{
			size_t frameIndex = animationFrame % frames.size();  // size_t型の一時変数を使用
			frames[frameIndex].resized(size, size).drawAt(drawPos, ColorF{ 1.0, isBlinkShift ? 0.5 : 1 });

		}
	}
}

void GameObject::drawHitbox(Vec2 offset) const
{
	if (collisionalTimer.isRunning() == false)
		hitbox.movedBy(offset).draw({ Palette::Tomato, 0.5 });
	else
		hitbox.movedBy(offset).draw({ Palette::Royalblue, 0.5 });

	//ついでにデバッグ用
	debugfont(Format(hp)).drawAt(this->pos + offset + Vec2{ 0,30 }, { Palette::Navy,0.5 });
}

// アニメーション関連のメソッド
void GameObject::updateAnimation() {
	// デルタタイムをアニメーションタイマーに加算
	animationTimer += Scene::DeltaTime();

	// タイマーがアニメーションの更新間隔を超えた場合
	if (animationTimer >= animationInterval) {
		// アニメーションフレームをインクリメント
		animationFrame++;

		// 現在の方向のアニメーションフレームの最大数を取得
		int maxFrames = animations[currentDirection].size();

		// フレーム数が最大を超えた場合、リセット
		if (animationFrame >= maxFrames)
		{
			animationFrame = 0;
		}

		// アニメーションタイマーをリセット
		animationTimer = 0.0;
	}
}

//====================================================
//外部からの変数取得


Figure GameObject::getHitbox()
{
	return hitbox;
}

int GameObject::getDamage()
{
	return damage;
}

//====================================================
//接触関連

bool GameObject::isCollisional()
{
	return !collisionalTimer.isRunning();
}

void GameObject::onCollisionResponse(int damage)
{
	collisionalTimer.restart();
	hp -= damage;

	if (objType == eDebris || objType == eEnemy || objType == ePlayer) blinkTimer1.restart();

	if (objType == eEnemy) myEffectManager->create_damageScoreEffect(pos, damage);
}

void GameObject::onCollisionResponse(Vec2 RepullPos)
{
	//collisionalTimer.restart();
	velRepull = (pos - RepullPos).setLength(vel.length() == 0 ? 100 : vel.length());

}

void GameObject::calcDamage(int damage)
{
}

void GameObject::changeCoolTime(Duration cooltime) 
{
	collisionalTimer.set(cooltime);
}

bool GameObject::isDead(Vec2 playerPos_) {
	if (hp <= 0) return true;
	else return false;
}

bool GameObject::isItemDrop() {
	return isItemDropable;
}

bool GameObject::isBulletSelfDamage()
{
	return false;
}

//====================================================
//君は完璧で最強のゲッター関数


Vec2 GameObject::getPos() const
{
	return pos;
}

double GameObject::getSpeed() const
{
	return speed;
}

eObjectType GameObject::getObjType() const
{
	return objType;
}

double GameObject::getHp() const
{
	return hp;
}

int GameObject::getExp() const
{
	return expPoints;
}

void GameObject::setSpeed(double speed)
{
	this->speed = speed;
}

void GameObject::setPos(Vec2 newPos)
{
	pos = newPos;
	hitbox.setCenter(newPos);
}

void GameObject::setVelocity(Vec2 vel)
{
	this->vel = vel;
}

void GameObject::setAcceleration(Vec2 acc )
{
	this->acc = acc;
}

void GameObject::setTexture(String textureStr)
{
	texture = TextureAsset{ textureStr };
}

void GameObject::setExp(int points)
{
	expPoints = points;

}
