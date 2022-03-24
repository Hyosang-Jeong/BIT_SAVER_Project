/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: stage_bar.h
Project: BIT_SAVER
Author:	Jaewoo Choi
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
    const double WINDOW_WIDTH = 20;
    const double BOSS_PITCH = 0.625;
    int currstate;
    bool Doupdate;
    Texture* extra_stage_barPtr;
    Texture* boss_stage_barPtr;

    double extra_stage_time;
    double music_total_time;

    double boss_stage_time;
    double actual_total_time;
    double extra_stage_size;
    double boss_stage_size;
    glm::vec2 extra_stage_pos_range;
    glm::vec2 boss_stage_pos_range;


    glm::vec2 stage_pos;
    glm::vec2 stage_scale;
};