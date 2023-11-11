#include "pSoundPlayer.h"

SoundPlayer* SoundPlayer::instance = nullptr;

SoundPlayer::SoundPlayer()
{
	SoundTable.emplace(enumSound::eTitle, Audio{ Audio::Stream, U"Music/mapselect.mp3", Loop::Yes });//);
	SoundTable.emplace(enumSound::eStageIntro, Audio{ U"Music/speedy_pre.mp3" });
	SoundTable.emplace(enumSound::eStageLoop, Audio{ Audio::Stream, U"Music/speedy_loop.mp3" , Loop::Yes });//, Loop::Yes);
	SoundTable.emplace(enumSound::eGameOver, Audio{ Audio::Stream, U"Music/tasogare.mp3" , Loop::Yes });//, Loop::Yes);

	EffectTable.emplace(enumEffect::effectShot, Audio{ U"Effect/se_shot_001.wav" });
	EffectTable.emplace(enumEffect::effectShotLaser, Audio{ U"Effect/se_shot_004.wav" });
	EffectTable.emplace(enumEffect::effectShotLaser2, Audio{ U"Effect/laser03.mp3" });
	EffectTable.emplace(enumEffect::effectShotWide, Audio{ U"Effect/maou_se_8bit18.wav" });
	EffectTable.emplace(enumEffect::effectShotWide2, Audio{ U"Effect/garagara.wav" });
	EffectTable.emplace(enumEffect::effectShotPrazma, Audio{ U"Effect/thunder_attack.wav" });
	EffectTable.emplace(enumEffect::effectShotMinePop, Audio{ U"Effect/shoot01.mp3" });
	EffectTable.emplace(enumEffect::effectShotMineBoom, Audio{ U"Effect/explosion01.mp3" });
	EffectTable.emplace(enumEffect::effectSelect, Audio{ U"Effect/poka02.mp3" });
	EffectTable.emplace(enumEffect::effectDead, Audio{ U"Effect/se_powerdown_003.wav" });
	EffectTable.emplace(enumEffect::effectHit1, Audio{ U"Effect/se_hit_007.wav" });
	EffectTable.emplace(enumEffect::effectHit2, Audio{ U"Effect/se_hit_008.wav" });
	EffectTable.emplace(enumEffect::effectHitPlayer, Audio{ U"Effect/se_hit_003.wav" });
	EffectTable.emplace(enumEffect::effectHitDebris, Audio{ U"Effect/se_hit_006.wav" });

}

SoundPlayer::~SoundPlayer()
{
}

SoundPlayer* SoundPlayer::getInstance()
{
	return instance;
}

void SoundPlayer::create()
{
	if (instance == nullptr)
	{
		instance = new SoundPlayer();
	}
}

void SoundPlayer::destroy()
{
	delete instance;
	instance = nullptr;
}


void SoundPlayer::playEffect(enumEffect eE)
{
	arrEffect.push_back(EffectTable[eE]);
	arrEffect[arrEffect.size() - 1].play();
	cnt++;
}

void SoundPlayer::update()
{
	Print << arrEffect.size();
	Print << cnt;
	Print << U"";

	loopCheck();
	arrEffect.remove_if([](const Audio& b) { return (b.isPlaying() == false); });
}

void SoundPlayer::playSound(enumSound eS, Duration fadeSecond)
{
	nowPlaying = eS;
	SoundTable[nowPlaying].play(fadeSecond);
}




void SoundPlayer::loopCheck()
{

	if (nowPlaying == eStageIntro && SoundTable[nowPlaying].isPlaying() == false)
	{
		nowPlaying = eStageLoop;
		SoundTable[nowPlaying].play();
	}
}

void SoundPlayer::fadeoutAudio(Duration fadeSecond)
{
	SoundTable[nowPlaying].stop(fadeSecond);

}
