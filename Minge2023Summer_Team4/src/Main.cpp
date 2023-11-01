﻿# include "../stdafx.h"
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

	//font
	FontAsset::Register(U"dotFont1", 20, Resource(U"Font/Nosutaru-dot.ttf"));

	EffectManager::create();

	while (System::Update())
	{
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
