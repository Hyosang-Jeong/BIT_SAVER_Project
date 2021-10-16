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
        ENERGY = 0,
        REWIND,
        SOUND_EFFECT1,
        MUSIC_END
    };

    //Music() {}
    //~Music() {}
    void Init();
    void Load();
    void Update();
    void Play(int sound_num);
    void Stop(int sound_num);
    void Resume(int sound_num);
    void Pause(int sound_num);
    void volumeUp(int sound_num);
    void volumeDown(int sound_num);
    void ErrorCheck(FMOD_RESULT result);
    void Release();

    
    FMOD_SYSTEM* pSystem;
    FMOD_CHANNEL* pChannel[MUSIC_END]{};
    FMOD_SOUND* pSound[MUSIC_END]{};
    FMOD_RESULT result;
    FMOD_SOUNDGROUP* bgm_group;
    FMOD_SOUNDGROUP* sfx_group;
    
private:
    float volume;
    float Musicvolume = 0.5f;
    float SFXvolume = 0.5f;

    std::vector<const char*> MusicName{};
};
