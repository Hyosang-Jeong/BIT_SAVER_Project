/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Energy.h
Project: BIT_SAVER
Author:
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include "../../Game/Objects/GameObjectType.h"
class CheckBox : public GameObject
{
public:
    CheckBox(glm::vec2 startPos, int color);

    GameObjectType GetObjectType() override
    {
        return GameObjectType::Check_box;
    }

private:

};