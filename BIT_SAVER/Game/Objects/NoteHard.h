/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Notes.h
Project:  BIT_SAVER
Author: Jaewoo.choi, Hyosang Jung 

-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"


class EnergyBar;


class HardNote : public GameObject
{
public:
    HardNote(glm::vec2 startPos,glm::vec2 velocity, double time);
    void Update(double dt) override;
    glm::vec2 Getposition();
    GameObjectType GetObjectType() override
    {
        return GameObjectType::HardNote;
    }
    void Draw(glm::mat3 camera_matrix) override;
    void Hit_Check();
    int Score_check();

    

private:
    InputKey UpAttackKey;
    InputKey DownAttackKey;
    bool isMiss;

    bool start_timer;
    bool change_state;
    double life_time;
    double timer;
    static constexpr int HardNote_Score = 500;


    EnergyBar* energy;

};