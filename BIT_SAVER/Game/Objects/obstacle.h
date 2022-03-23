/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: obstacle.h
Project:  BIT_SAVER
Author: Jaewoo.choi, Hyosang Jung

-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"

class Obstacle : public GameObject
{
public:
    Obstacle(glm::vec2 startPos, glm::vec2 velocity);
    void Update(double dt) override;
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Obstacle;
    }
    void Draw(glm::mat3 camera_matrix) override;

};
