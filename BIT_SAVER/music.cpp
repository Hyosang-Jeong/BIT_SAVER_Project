#include "music.h"

using namespace std;



void Music::SoundSystem()
{
    System_Create(&pSystem);

    pSystem->init(4, FMOD_INIT_NORMAL, NULL);

    pSystem->createSound("music1.mid", FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &pSound[0]);
}

void Music::Play(int Sound_num)
{
    pSystem->playSound(pSound[Sound_num], NULL, 0, pChannel);
}
