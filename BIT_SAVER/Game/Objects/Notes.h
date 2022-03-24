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


class Note : public GameObject
{
public:
    Note(glm::vec2 startPos,glm::vec2 velocity);
    virtual void Update(double dt) override;
    glm::vec2 Getposition();
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Note;
    }
    virtual void Draw(glm::mat3 camera_matrix) override;
    virtual void Hit_Check();
    virtual int Score_check();

    

private:
    InputKey UpAttackKey;
    InputKey DownAttackKey;
    bool isMiss;


    EnergyBar* energy;

};