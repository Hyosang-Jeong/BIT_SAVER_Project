/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: BIT_SAVER
Author:
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once

#include"..\Engine\Input\Input.h"
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"

class Stage_bar : public GameObject
{
public:
    Stage_bar(glm::vec2 startPos, double total_time, double extra_time);
    void Update(double dt) override;
    void Draw(glm::mat3 camera_matrix) override;
    int Getchangeflag();
    void SetUpdate(bool update);
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Stage_bar;
    }
private:
    int currstate;
    bool Doupdate;
    Texture* stage_barPtr;
    const double extra_stage_time;
    const double total_time;
    GLModel stage_barModel;
};