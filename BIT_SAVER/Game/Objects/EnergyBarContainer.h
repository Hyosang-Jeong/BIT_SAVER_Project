/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnergyBarContainer.h
Project: BIT_SAVER
Author: Jaewoo Choi
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include "../../Game/Objects/GameObjectType.h"
class EnergyBarContainer : public GameObject
{
public:
    EnergyBarContainer(glm::vec2 startPos);

    void Draw(glm::mat3 camera_matrix) override;

    GameObjectType GetObjectType() override
    {
        return GameObjectType::Energy_bar_container;
    }


private:


};