#pragma once
//we use fmod library here
#include<iostream>
#include"fmod.hpp"

#include"fmod_errors.h"
#include <fmod.h>
#include <string>
#include <vector>
#include "Sound_Num.h"

#define SOUND_MAX       1.0f
#define SOUND_MIN       0.0f
#define SOUND_DEFAULT   0.5f
#define SOUND_WEIGHT    0.1f 

class Music
{
public:

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
    void SetVolume(int sound_num,float volume_);
    void pitchUp(int sound_num);
    void pitchDefault(int sound_num);
    void pitchDown(int sound_num);
    bool isPlaying(int sound_num);
    void ErrorCheck(FMOD_RESULT result);
    void Release();
    
    FMOD_SYSTEM* pSystem;
    FMOD_CHANNEL* pChannel[MUSIC_END]{};
    FMOD_SOUND* pSound[MUSIC_END]{};
    FMOD_RESULT result;
    FMOD_SOUNDGROUP* bgm_group;
    FMOD_SOUNDGROUP* sfx_group;
    FMOD_BOOL isplaying;
    float volume = 0.f;
    float pitch = 1.f;
    float Musicvolume = 0.5f;
    float SFXvolume = 0.5f;
    std::vector<const char*> MusicName;
};
