#include "music.h"
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
#include "../../Engine/Input/Input.h"

using namespace std;

void Music::Init()
{
    MusicName.push_back("../sound/canon.wav");
    //MusicName.push_back("something");

    System_Create(&pSystem);
    pSystem->init(MUSIC_END+1, FMOD_INIT_NORMAL, NULL);
    for (int i = 0; i < MusicName.size(); i++)
    {
        pSystem->createSound(MusicName[i], FMOD_DEFAULT, NULL, &pSound[i]);
    }
    
}

void Music::Play(int Sound_num)
{
    pSystem->playSound(pSound[Sound_num], NULL, 0, &pChannel);
}

void Music::Stop()
{
    pChannel->stop();
}

void Music::Resume()
{
    pChannel->setPaused(false);
}

void Music::Pause()
{
    pChannel->setPaused(true);
}

void Music::volumeUp()
{
    if (volume < SOUND_MAX) {
        volume += SOUND_WEIGHT;
    }
    pChannel->setVolume(volume);
}

void Music::volumeDown()
{
    if (volume > SOUND_MIN) {
        volume -= SOUND_WEIGHT;
    }
    pChannel->setVolume(volume);
}

void Music::Release()
{
    pSystem->close();
    pSystem->release();
}



