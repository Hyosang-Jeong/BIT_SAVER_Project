#pragma once
//we use fmod library here
#include<iostream>
#include"fmod.hpp"
#include"fmod_errors.h"
#include <fmod.h>
#include <string>
#include <vector>
#define SOUND_MAX       1.0f
#define SOUND_MIN       0.0f
#define SOUND_DEFAULT   0.5f
#define SOUND_WEIGHT    0.1f 

class Music
{
public:
    enum SOUND_NUM
    {
        MUSIC_CANON = 0,
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
private:
    float volume;
    FMOD::System* pSystem;
    FMOD::Sound* pSound[MUSIC_END];
    FMOD::Channel* pChannel;
    std::vector<const char*> MusicName;
};
