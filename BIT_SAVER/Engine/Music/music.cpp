#include "music.h"
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
#include "../../Engine/Input/Input.h"
#include "../Engine.h"

using namespace std;
void Music::Init()
{
    result = FMOD_System_Create(&pSystem, FMOD_VERSION);
    ErrorCheck(result);
    result = FMOD_System_Init(pSystem, MUSIC_END, FMOD_INIT_NORMAL, nullptr);
    ErrorCheck(result);
    Load();
}

void Music::Load()
{
    
    result = FMOD_System_CreateSound(pSystem, "../sound/disco.mp3", FMOD_DEFAULT, nullptr, &pSound[DISCO]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/rewind.mp3", FMOD_DEFAULT, nullptr, &pSound[REWIND]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/offset.mp3", FMOD_DEFAULT, nullptr, &pSound[OFFSET]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/button1.mp3", FMOD_DEFAULT, nullptr, &pSound[SOUND_EFFECT1]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/button2.mp3", FMOD_DEFAULT, nullptr, &pSound[SOUND_EFFECT2]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/energy.mp3", FMOD_DEFAULT, nullptr, &pSound[ENERGY]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/boss_entrance.mp3", FMOD_DEFAULT, nullptr, &pSound[BOSS_ENTRANCE]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/fever.mp3", FMOD_DEFAULT, nullptr, &pSound[FEVER]);
    ErrorCheck(result);
}
void Music::Play(int sound_num)
{
    result = FMOD_System_PlaySound(pSystem, pSound[sound_num], 0, 0, &pChannel[sound_num]);
    ErrorCheck(result);
}

void Music::Stop(int sound_num)
{
    result = FMOD_Channel_Stop(pChannel[sound_num]);
    ErrorCheck(result);
}

void Music::Update()
{
    result = FMOD_System_Update(pSystem);
}

void Music::Resume(int sound_num)
{
    
    result = FMOD_Channel_SetPaused(pChannel[sound_num], false);
    ErrorCheck(result);
}

void Music::Pause(int sound_num)
{
    result = FMOD_Channel_SetPaused(pChannel[sound_num], true);
    ErrorCheck(result);
}

void Music::volumeUp(int sound_num)
{
    if (volume < SOUND_MAX) 
    {
        volume = SOUND_MAX;
    }
    result = FMOD_Channel_SetVolume(pChannel[sound_num], volume);
    ErrorCheck(result);
}

void Music::volumeDown(int sound_num)
{
    if (volume > SOUND_MIN) {
        volume -= SOUND_WEIGHT;
    }
    result = FMOD_Channel_SetVolume(pChannel[sound_num], volume);
    ErrorCheck(result);
}

void Music::SetVolume(int sound_num, float volume_)
{
    result = FMOD_Channel_SetVolume(pChannel[sound_num], volume_);
    ErrorCheck(result);
}

void Music::pitchUp(int sound_num)
{
    //ErrorCheck(FMOD_System_CreateDSPByType(pSystem, FMOD_DSP_TYPE_PITCHSHIFT, &pitch_shift));
    //ErrorCheck(FMOD_Channel_AddDSP(pChannel[sound_num], 0, pitch_shift));
    //pitch = 2.0f;
    //ErrorCheck(FMOD_DSP_SetParameterFloat(pitch_shift, 0, pitch));
    //ErrorCheck(FMOD_DSP_SetActive(pitch_shift, true));
    ErrorCheck(FMOD_Channel_GetPitch(pChannel[sound_num], &pitch));
    pitch = 1.5f;
    ErrorCheck(FMOD_Channel_SetPitch(pChannel[sound_num], pitch));

}

void Music::pitchDefault(int sound_num)
{
    ErrorCheck(FMOD_Channel_GetPitch(pChannel[sound_num], &pitch));
    pitch = 1.0f;
    ErrorCheck(FMOD_Channel_SetPitch(pChannel[sound_num], pitch));

}

void Music::pitchDown(int sound_num)
{
    ErrorCheck(FMOD_Channel_GetPitch(pChannel[sound_num], &pitch));
    pitch = 0.5f;
    ErrorCheck(FMOD_Channel_SetPitch(pChannel[sound_num], pitch));
}

bool Music::isPlaying(int sound_num)
{
    result = FMOD_Channel_IsPlaying(pChannel[sound_num],&isplaying);

    return isplaying;
}



void Music::Release()
{
    FMOD_System_Close(pSystem);
    FMOD_System_Release(pSystem);
}



void Music::ErrorCheck(FMOD_RESULT results)
{

    if (results != FMOD_OK) {
        Engine::GetLogger().LogError("Error: there are error in music file");
        std::cout << static_cast<int>(results);
        //add result where is exact error happen function
        exit(EXIT_FAILURE);
    }

}



