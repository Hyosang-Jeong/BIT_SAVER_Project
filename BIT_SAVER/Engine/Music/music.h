/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: music.h
Project: BIT_SAVER
Author: Jaewoo.choi

-----------------------------------------------------------------*/
#pragma once
//we use fmod library here

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
    void SetVolume(float volume_);
    void pitchUp(int sound_num);
    void pitchDefault(int sound_num);
    void pitchDown(int sound_num);
    bool isPlaying(int sound_num);
    void ErrorCheck(FMOD_RESULT result);
    void Release();
    void Setposition(int sound_num, unsigned position);


    FMOD_SYSTEM* pSystem;
    FMOD_CHANNEL* pChannel[MUSIC_END]{};
    FMOD_SOUND* pSound[MUSIC_END]{};
    FMOD_RESULT result;
    FMOD_SOUNDGROUP* bgm_group;
    FMOD_SOUNDGROUP* sfx_group;
    FMOD_BOOL isplaying;
    float pitch = 1.f;
    float Musicvolume = 0.5f;
    float SFXvolume = 0.5f;
    std::vector<const char*> MusicName;

private:
    float volume = 0.f;
};
