#pragma once
//we use fmod library here
#include<iostream>
#include"fmod.hpp"
#include"fmod_errors.h"
#include <string>

class Music
{
public:
    enum SOUND_NAME
    {
        MUSIC_CANON = 0,
        MUSIC_END
    };
    void SoundSystem(const char* music_file_name, int music_num);
    void Play(int Sound_num);
private:
    FMOD::System* pSystem;
    FMOD::Sound* pSound[MUSIC_END];
    FMOD::Channel* pChannel;
};
