/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Note.h
Project: 
Author: 
Creation date: 
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
    void Update(double dt) override;
    glm::vec2 Getposition();
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Note;
    }
    void Draw(glm::mat3 camera_matrix) override;
    void Hit_Check();
    int Score_check();
private:
    InputKey UpAttackKey1;
    InputKey UpAttackKey2;
    InputKey DownAttackKey1;
    InputKey DownAttackKey2;
    bool isMiss;

    EnergyBar* energy;
};

enum class SCORE
{
    MISS=0,
    BAD,
    GOOD,
    PERFECT
};