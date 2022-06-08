/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Offset.h
Project: BIT_SAVER
Author: Jaewoo.choi, Hyosang Jung 

-----------------------------------------------------------------*/
#pragma once
#include <string>
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include "..\Engine\GameObject\GameObjectManager.h" // gameobjectmanager
#include"..\Engine\Input\Input.h"  //input key
#include"..\..\Engine\Physics\Camera.h"
#include"../Objects/Track.h"

class CheckBox;
class Hero;
class Track;
class Background;
class EnergyBar;

class Offset : public GameState
{
public:

    Offset();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    std::string GetName() override { return "Offset"; }
    long double GetResultTime();
    SOUND_NUM GetcurrentMusic()
    {
	return SOUND_NUM::OFFSET;
    }

private:

    Texture* offset_x;
    Texture* offset_screen;
    Texture* offset_background;
    InputKey ESCAPE;
    InputKey HitKey;
    std::vector<Track_Time> track_time_vector; 
    GameObjectManager* gameObjectManager;
 
    Track* trackPtr;

    std::vector<long double> compareTime;
    long double currentTime;
    long double resultTime;
    long double currentResultTime;
    int hitNumber;
    bool isHit;
    bool isStart;
    bool isMusicEnd;
    glm::vec2 x_pos;
    long double yourOffset;
    int miliSeconds;
    int RealCompareNumber;
    double intervalTime;
    long double interval;
    bool isoffset;

    std::vector<float> pos;
};