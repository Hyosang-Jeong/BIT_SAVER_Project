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


    for (int i = 0; i < MUSIC_END; i++)
    {
        result = FMOD::System_Create(&pSystem[i]);
        result = pSystem[i]->init(MUSIC_END, FMOD_INIT_NORMAL, NULL);
    }

    MusicName.push_back("../sound/boss.mp3");
    MusicName.push_back("../sound/Energy.mp3");
    MusicName.push_back("../sound/button1.mp3");


    for (int i = 0; i < MusicName.size(); i++)
    {
        result = pSystem[i]->createSound(MusicName[i], FMOD_DEFAULT, NULL, &pSound[i]);
        if (result != FMOD_OK) {
            Engine::GetLogger().LogError("Error: FMOD_system are not created sound at track num: ");
            std::cout << i;
            exit(EXIT_FAILURE);
        }
    }
}

void Music::Play(int Sound_num)
{

    while (true)
    {
        pSystem[Sound_num]->playSound(pSound[Sound_num], NULL, 0, &pChannel[Sound_num]);
        Engine::GetMusic().pSystem[Music::SOUND_NUM::SOUND_EFFECT1]->update();
        break;
    }
}

void Music::Stop()
{
    pChannel[0]->stop();
}

void Music::Resume()
{
    pChannel[0]->setPaused(false);
}

void Music::Pause()
{
    pChannel[0]->setPaused(true);
}

void Music::volumeUp()
{
    if (volume < SOUND_MAX) {
        volume += SOUND_WEIGHT;
    }
    pChannel[0]->setVolume(volume);
}

void Music::volumeDown()
{
    if (volume > SOUND_MIN) {
        volume -= SOUND_WEIGHT;
    }
    pChannel[0]->setVolume(volume);

}

void Music::Release()
{
    pSystem[0]->close();
    pSystem[0]->release();
}



