#pragma once

#include<iostream>
#include"fmod.hpp"
#include"fmod_errors.h"



class Music
{
public:
    void SoundSystem();
    void Play(int Sound_num);
private:
    FMOD::System* pSystem;
    FMOD::Sound* pSound[1];
    FMOD::Channel* pChannel[1];
};
//void SoundSystem() {
//    System_Create(&pSystem);
//
//    pSystem->init(4, FMOD_INIT_NORMAL, NULL);
//
//    pSystem->createSound("music1.mid", FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &pSound[0]);
//    //pSystem->createSound("Festival_of_Ghost.wav", FMOD_DEFAULT, NULL, &pSound[1]);
//}
//
//void Play(int Sound_num) {
//
//    pSystem->playSound(pSound[Sound_num], NULL, 0, pChannel);
//}
