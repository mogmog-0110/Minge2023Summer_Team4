#include "pSoundPlayer.h"

SoundPlayer* SoundPlayer::instance = nullptr;

SoundPlayer::SoundPlayer()
{
	SoundTable.emplace(enumSound::eTitle, Audio{ Audio::Stream, U"Music/mapselect.mp3" });
	SoundTable.emplace(enumSound::eStageIntro, Audio{ U"Music/speedy_pre.mp3" });
	SoundTable.emplace(enumSound::eStageLoop, Audio{ Audio::Stream, U"Music/speedy_loop.mp3" });
	SoundTable.emplace(enumSound::eGameOver, Audio{ Audio::Stream, U"Music/tasogare.mp3" });

	SoundTable.emplace(enumSound::effectShot, Audio{ U"Effect/se_shot_001.wav" });
	SoundTable.emplace(enumSound::effectSelect, Audio{ U"Effect/poka02.mp3" });
	SoundTable.emplace(enumSound::effectDead, Audio{ U"Effect/se_powerdown_003.wav" });

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


void SoundPlayer::playSound(enumSound eS)
{
	nowPlaying = eS;
	SoundTable[nowPlaying].play();
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
