/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: music.cpp
Project: BIT_SAVER
Author: Jaewoo.choi

-----------------------------------------------------------------*/
#include "music.h"
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
#include "../../Engine/Input/Input.h"
#include "../Engine.h"
#include "../../Game/Levels/MainOption.h"
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
    result = FMOD_System_CreateSound(pSystem, "../sound/offset.mp3", FMOD_DEFAULT, nullptr, &pSound[OFFSET]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/disco.mp3", FMOD_DEFAULT, nullptr, &pSound[DISCO]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/rewind.mp3", FMOD_DEFAULT, nullptr, &pSound[REWIND]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/dioma.mp3", FMOD_DEFAULT, nullptr, &pSound[DIOMA]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/energy.mp3", FMOD_DEFAULT, nullptr, &pSound[ENERGY]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/button1.mp3", FMOD_DEFAULT, nullptr, &pSound[SOUND_EFFECT1]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/button2.mp3", FMOD_DEFAULT, nullptr, &pSound[SOUND_EFFECT2]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/boss_entrance.mp3", FMOD_DEFAULT, nullptr, &pSound[BOSS_ENTRANCE]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/fever.mp3", FMOD_DEFAULT, nullptr, &pSound[FEVER]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/Cartoon.mp3", FMOD_DEFAULT, nullptr, &pSound[JANJI]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/321.mp3", FMOD_DEFAULT, nullptr, &pSound[WAIT]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/Neon1.wav", FMOD_LOOP_NORMAL, nullptr, &pSound[INTRO1]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/Neon2.wav", FMOD_LOOP_NORMAL, nullptr, &pSound[INTRO2]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/Neon3.wav", FMOD_LOOP_NORMAL, nullptr, &pSound[INTRO3]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/Hit_.mp3", FMOD_DEFAULT, nullptr, &pSound[HIT]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/selectingMenu.wav", FMOD_DEFAULT, nullptr, &pSound[MENU_SELECT]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/movingMenu.wav", FMOD_DEFAULT, nullptr, &pSound[MENU_MOVE]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/star1.wav", FMOD_DEFAULT, nullptr, &pSound[STAR1]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/star2.wav", FMOD_DEFAULT, nullptr, &pSound[STAR2]);
    ErrorCheck(result);

    result = FMOD_System_CreateSound(pSystem, "../sound/star3.wav", FMOD_DEFAULT, nullptr, &pSound[STAR3]);
    ErrorCheck(result);

    volume = SOUND_DEFAULT;

}
void Music::Play(int sound_num)
{
    
    result = FMOD_System_PlaySound(pSystem, pSound[sound_num], 0, 0, &pChannel[sound_num]);

    ErrorCheck(result);
    if (Engine::GetGSComponent<MainOption>() != nullptr)
        volume = Engine::GetGSComponent<MainOption>()->GetVolume();
    else
        result = FMOD_Channel_SetVolume(pChannel[sound_num], volume);

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

void Music::SetVolume(float volume_)
{
    if (Engine::GetGameStateManager().GetCurrstate()->GetcurrentMusic() != MUSIC_END)
    {
        FMOD_Channel_SetVolume(pChannel[Engine::GetGameStateManager().GetCurrstate()->GetcurrentMusic()], volume_);
   }
    volume = volume_;
}

void Music::pitchUp(int sound_num)
{

    ErrorCheck(FMOD_Channel_GetPitch(pChannel[sound_num], &pitch));
    pitch = 1.6f;
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

void Music::Setposition(int sound_num, unsigned position)
{
    result = FMOD_Channel_SetPosition(pChannel[sound_num], position * 1000, FMOD_TIMEUNIT_MS);
    ErrorCheck(result);
}



void Music::ErrorCheck(FMOD_RESULT results)
{

    if (results != FMOD_OK) {
        Engine::GetLogger().LogError("Error: there are error in music file");
        Engine::GetLogger().LogError("Error with " + std::to_string(static_cast<int>(results)));
        
        exit(EXIT_FAILURE);
    }

}



