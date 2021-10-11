#include "music.h"
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>


using namespace std;

void Music::SoundSystem(const char* music_file_name,int music_num)
{
    System_Create(&pSystem);
    pSystem->init(MUSIC_END+1, FMOD_INIT_NORMAL, NULL);
    pSystem->createSound(music_file_name, FMOD_LOOP_NORMAL, NULL, &pSound[music_num]);
}

void Music::Play(int Sound_num)
{
    pSystem->playSound(pSound[Sound_num], NULL, 0, &pChannel);
}


