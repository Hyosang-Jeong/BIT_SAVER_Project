/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnergyBar.h
Project: BIT_SAVER
Author:
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance

#include "../../Game/Objects/GameObjectType.h"
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

private:


};