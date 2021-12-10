/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: fever.h
Project: BIT_SAVER
Author:	Jaewoo Choi
-----------------------------------------------------------------*/
#pragma once

#include"..\Engine\Input\Input.h"
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"
#include"Score.h"
class Fever_bar : public GameObject
{
public:
    Fever_bar(glm::vec2 startPos);
    void Update(double dt) override;
    void Draw(glm::mat3 camera_matrix) override;
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Fever_bar;
    }
private:
     int initial_score;
     bool is_fever_mode;

    Texture* fever_barPtr;
    Texture* fever_gazePtr;
    Score* score_ptr;
};