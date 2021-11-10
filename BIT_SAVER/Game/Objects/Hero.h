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

#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"

enum class hero_anim
{
    hero_run,
    up_attck,
    down
};
enum Hero_state
{
    RUN_ENTER,
    RUN,
    UP_ENTER,
    UP,
    DOWN_ATTACK_ENTER,
    DOWN_ATTACK,
    DOWN_ENTER,
    DOWN
};

class Hero : public GameObject
{
public:
    Hero(glm::vec2 startPos);
    void Update(double dt) override;
    glm::vec2 Getposition();
    void Draw(glm::mat3 camera_matrix) override;
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Hero;
    }
private:

    InputKey moveUp1Key;
    InputKey moveUp2Key;
    InputKey moveDown1Key;
    InputKey moveDown2Key;
    InputKey moveLeftKey;
    InputKey moveRightKey;
    InputKey AttackKey;
    Hero_state hero_state;
    static constexpr double acceleration = 1;
    static constexpr double drag = 500;
    static constexpr double max_velocity = 500;
    static constexpr double jumpVelocity = 1000;

    void UpdateXVelocity(double dt);     //Change X velocity stuff
};