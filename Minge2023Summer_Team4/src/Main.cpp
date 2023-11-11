# include "../stdafx.h"
#include "Define.h" // OpenSiv3D v0.6.11
#include "Game/pGame.h"
#include "Title/pTitle.h"
#include "Result/pResult.h"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// シーンマネージャーを作成
	App manager;

	// タイトルシーンを登録
	manager.add<Title>(SceneList::Title);
	manager.add<Game>(SceneList::Game);
	manager.add<Result>(SceneList::Result);

	manager.init(SceneList::Title);

	// 画面サイズを変更
	Window::Resize(1024, 768);

	//画像の登録
	//Titleシーン
	TextureAsset::Register(U"Title", Resource(U"Image/title.png"));

	//Gameシーン
	TextureAsset::Register(U"Cursor", Resource(U"Image/Cursor.png"));
	TextureAsset::Register(U"Frame", Resource(U"Image/Frame.png"));
	TextureAsset::Register(U"playerImage", Resource(U"Image/Player.png"));
	TextureAsset::Register(U"Background", Resource(U"Image/Background.png"));

	TextureAsset::Register(U"Ghost", Resource(U"Image/Ghost.png"));
	TextureAsset::Register(U"Experience", Resource(U"Image/Experience.png"));
	TextureAsset::Register(U"NormalBullet", Resource(U"Image/NormalBullet.png"));
	TextureAsset::Register(U"SpecialMagicA", Resource(U"Image/MagicBookA.png"));
	TextureAsset::Register(U"SpecialMagicB", Resource(U"Image/MagicBookB.png"));
	TextureAsset::Register(U"SpecialMagicC", Resource(U"Image/MagicBookC.png"));
	TextureAsset::Register(U"SpecialMagicD", Resource(U"Image/MagicBookD.png"));
	TextureAsset::Register(U"EnemyBullet", Resource(U"Image/EnemyBullet.png"));
	TextureAsset::Register(U"LaserBullet", Resource(U"Image/LaserBullet.png"));
	TextureAsset::Register(U"MineBullet", Resource(U"Image/MineBullet.png"));
	TextureAsset::Register(U"NormalBullet", Resource(U"Image/NormalBullet.png"));
	TextureAsset::Register(U"PrasmaBullet", Resource(U"Image/prasmaBullet.png"));
	TextureAsset::Register(U"WideBullet", Resource(U"Image/WideBullet.png"));

	TextureAsset::Register(U"NormalMagic", Resource(U"Image/NormalBook.png"));
	TextureAsset::Register(U"RockL", Resource(U"Image/RockL.png"));
	TextureAsset::Register(U"RockM", Resource(U"Image/RockM.png"));
	TextureAsset::Register(U"RockS", Resource(U"Image/RockS.png"));
	TextureAsset::Register(U"MiniMapFrame", Resource(U"Image/MiniMapFrame.png"));
	TextureAsset::Register(U"MagicFrame", Resource(U"Image/MagicFrame.png"));
	TextureAsset::Register(U"PlayerIcon", Resource(U"Image/PlayerIcon.png"));
	TextureAsset::Register(U"EnemyIcon", Resource(U"Image/EnemyIcon.png"));
	TextureAsset::Register(U"DebriIcon", Resource(U"Image/DebriIcon.png"));
	TextureAsset::Register(U"Hp", Resource(U"Image/Hp.png"));
	TextureAsset::Register(U"HpFrame", Resource(U"Image/HpFrame.png"));

	TextureAsset::Register(U"Effect1", Resource(U"Image/Effect1.png"));
	TextureAsset::Register(U"Effect2", Resource(U"Image/Effect2.png"));
	TextureAsset::Register(U"Effect3", Resource(U"Image/Effect3.png"));
	TextureAsset::Register(U"Effect4", Resource(U"Image/Effect4.png"));

	TextureAsset::Register(U"Bat", Resource(U"Image/Bat.png"));
	TextureAsset::Register(U"BigRat", Resource(U"Image/BigRat.png"));
	TextureAsset::Register(U"Rat", Resource(U"Image/Rat.png"));
	TextureAsset::Register(U"BigSpider", Resource(U"Image/BigSpider.png"));
	TextureAsset::Register(U"Spider", Resource(U"Image/Spider.png"));
	TextureAsset::Register(U"BloatedBedBug", Resource(U"Image/BloatedBedBug.png"));
	TextureAsset::Register(U"Cockroach", Resource(U"Image/Cockroach.png"));
	TextureAsset::Register(U"EvilEye", Resource(U"Image/EvilEye.png"));
	TextureAsset::Register(U"Worm", Resource(U"Image/Worm.png"));
	TextureAsset::Register(U"Kuro", Resource(U"Image/Kuro.png")); // BOSS

	TextureAsset::Register(U"Clear", Resource(U"Image/clear1.png"));
	TextureAsset::Register(U"gameOver", Resource(U"Image/gameOver.png"));
	TextureAsset::Register(U"Yajirusi", Resource(U"Image/Yajirusi.png"));
  
	//font
	FontAsset::Register(U"dotFont1", 20, Resource(U"Font/Nosutaru-dot.ttf"));
	FontAsset::Register(U"dotFont2", 30, Resource(U"Font/Nosutaru-dot.ttf"));
	FontAsset::Register(U"dotFont3", 50, Resource(U"Font/Nosutaru-dot.ttf"));
	FontAsset::Register(U"dotTitle1", 500, Resource(U"Font/Square.ttf"));

	EffectManager::create();

	while (System::Update())
	{
		// マウスカーソルをウィンドウの表示域に制限する。
		Cursor::ClipToWindow(true);
		if (not manager.update())
		{
			break;
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
