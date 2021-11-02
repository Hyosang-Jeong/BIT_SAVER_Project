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

#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance

#include "../../Game/Objects/GameObjectType.h"
class EnergyBar : public GameObject
{
public:
    EnergyBar(glm::vec2 startPos);
    void Update(double dt) override;
    void ResolveCollision(GameObject* test_obj) override;
    const bool GetDestroyed() const;
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Energy_bar;
    }
    glm::vec2 Getposition();
    void set_attack_flag(bool attack_flag, GLfloat ypos);
    void Draw(glm::mat3 camera_matrix) override;
private:
    
    bool Hit[2] = { false };   //Hit check flag
    glm::vec2 Hit_pos[2] = { {-20,-20},{-20,-20} }; //Track1 and Track2  // intial pos -20,-20 => not to draw initail state
    bool attack_pressed{ false };
    bool is_repeated{ false };
    bool is_destroyed{ true };
    GLfloat attack_ypos{ 0 };
};