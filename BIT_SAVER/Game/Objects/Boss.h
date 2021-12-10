/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Boss.h
Project: BIT_SAVER
Author: Hyun Kang
-----------------------------------------------------------------*/
#pragma once
//#include "..\Engine\Sprite.h" //sprite
#include"..\Engine\Input\Input.h"
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"

enum class boss_anim
{
    spawn
};


class Boss : public GameObject
{
public:
    Boss(glm::vec2 startPos);
    void Update(double dt) override;
    glm::vec2 Getposition();
    void Draw(glm::mat3 camera_matrix) override;
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Boss;
    }
    void GenerateBoss();
private:
    void UpdateXVelocity(double dt);     //Change X velocity stuff
    bool is_generating;

};