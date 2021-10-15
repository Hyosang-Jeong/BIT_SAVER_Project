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
//#include "..\Engine\Sprite.h" //sprite
#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"

class Hero : public GameObject
{
public:
    Hero(glm::vec2 startPos);
    void Update(double dt) override;
    glm::vec2 Getposition();
    void Draw() override;
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Hero;
    }
private:
    InputKey moveUpKey;
    InputKey moveDownKey;
    InputKey moveLeftKey;
    InputKey moveRightKey;
    InputKey AttackKey;
    InputKey VolumeUp;
    InputKey VolumeDown;

    Texture Hit_tex;
    Texture Miss_tex;
    static constexpr double acceleration = 1;
    static constexpr double drag = 500;
    static constexpr double max_velocity = 500;
    static constexpr double jumpVelocity = 1000;
    //const BIT_SAVER::Camera& camera;

    bool move_release_frag[4] = { false };
    bool attack_pressed = false;

    bool Hit[2] = { false };   //Hit check flag
    glm::vec2 Hit_pos[2] = { {-20,-20},{-20,-20} }; //Track1 and Track2  // intial pos -20,-20 => not to draw initail state 
    void UpdateXVelocity(double dt);     //Change X velocity stuff
    void Attack_Check();
};