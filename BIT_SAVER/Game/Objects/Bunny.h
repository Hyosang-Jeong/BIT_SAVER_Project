/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
//#include "..\Engine\Sprite.h" //sprite
#include"..\Engine\Input\Input.h"
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance


class Bunny : public GameObject
{
public:
    Bunny(glm::vec2 startPos);
    void Update(double dt) override;
    glm::vec2 Getposition();
    void Draw() override;
private:
    InputKey moveUpKey;
    InputKey moveDownKey;
    InputKey moveLeftKey;
    InputKey moveRightKey;

    InputKey jumpKey;

    static constexpr double acceleration = 1;
    static constexpr double drag = 500;
    static constexpr double max_velocity = 500;
    static constexpr double jumpVelocity = 1000;
    //const CS230::Camera& camera;

    void UpdateXVelocity(double dt);     //Change X velocity stuff


};