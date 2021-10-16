#pragma once
//we use fmod library here
#include<iostream>
#include"fmod.hpp"
#include"fmod_errors.h"
#include <fmod.h>
#include <string>
#include <vector>
//#define SOUND_MAX       1.0f
#define SOUND_MAX       0.9f
#define SOUND_MIN       0.0f
#define SOUND_DEFAULT   0.5f
#define SOUND_WEIGHT    0.1f 

class Music
{
public:
    enum SOUND_NUM
    {
        REWIND = 0,
        SOUND_EFFECT1,
        MUSIC_END
    };

    //Music() {}
    //~Music() {}
    void Init();
    void Play(int Sound_num);
    void Stop();
    void Resume();
    void Pause();
    void volumeUp();
    void volumeDown();
    void Release();
    FMOD::System* pSystem[MUSIC_END]{};
    FMOD::Channel* pChannel[MUSIC_END]{};
    FMOD::Sound* pSound[MUSIC_END]{};
    FMOD_RESULT result;
    bool isstop = false;
private:
    float volume;

    std::vector<const char*> MusicName{};
};
