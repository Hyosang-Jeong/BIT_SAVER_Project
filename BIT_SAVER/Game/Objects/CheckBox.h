/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CheckBox.h
Project: BIT_SAVER
Author: Jaewoo Choi
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include "../../Game/Objects/GameObjectType.h"
#include"..\Engine\Input\Input.h"  //input key

class CheckBox : public GameObject
{
public:
    CheckBox(glm::vec2 startPos, int color);

    GameObjectType GetObjectType() override
    {
        return GameObjectType::Check_box;
    }
    void Draw(glm::mat3 camera_matrix) override;
private:

    InputKey tilde;
    bool isTildeKeyDown;

};