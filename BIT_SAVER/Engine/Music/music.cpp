#include "music.h"
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>


using namespace std;



void Music::SoundSystem()
{

    System_Create(&pSystem);

    pSystem->init(4, FMOD_INIT_NORMAL, NULL);


    pSystem->createSound("../sound/canon.wav", FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &pSound[0]);


}

void Music::Play(int Sound_num)
{
    pSystem->playSound(pSound[Sound_num], NULL, 0, pChannel);
}


