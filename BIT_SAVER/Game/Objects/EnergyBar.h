/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnergyBar.h
Project: BIT_SAVER
Author: Jaewoo Choi
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance

#include "../../Game/Objects/GameObjectType.h"

constexpr float SIXTEEN_TIME_PER_LIFE   =   10.f / 20.5f;
constexpr float EIGHT_TIME_PER_LIFE     = SIXTEEN_TIME_PER_LIFE * 2 ;
constexpr float FOUR_TIME_PER_LIFE      = EIGHT_TIME_PER_LIFE * 2;
constexpr float TWO_TIME_PER_LIFE       = FOUR_TIME_PER_LIFE * 2;
constexpr float ONE_TIME_PER_LIFE       = TWO_TIME_PER_LIFE * 2;

class EnergyBar : public GameObject
{
public:
    EnergyBar(glm::vec2 startPos);
    void Update(double dt) override;
    bool Isgameover();
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Energy_bar;
    }

    InputKey gameover;

private:


};