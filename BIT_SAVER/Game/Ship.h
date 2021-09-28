/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.h
Project: CS230
Author: Hyosang Jung
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\GameObject.h"
#include"GameObjectTypes.h"
class Ship : public CS230::GameObject 
{
public:
    Ship(math::vec2 startPos);
    void Update(double dt) override;
    void Draw(math::TransformMatrix cameraMatrix) override;
    GameObjectType GetObjectType()
    {
        return GameObjectType::Ship;
    }
    std::string GetObjectTypeName()
    {
        return "Ship";
    }
    void ResolveCollision(CS230::GameObject* objectB) override;
    bool IsDead() { return isDead; }
    bool CanCollideWith(GameObjectType objectBType) override;
private:

    CS230::Sprite left_flame;
    CS230::Sprite right_flame;

    CS230::InputKey rotateCounterKey;
    CS230::InputKey rotateClockKey;
    CS230::InputKey accelerateKey;
    CS230::InputKey shootingKey;
    static constexpr double accel = 400;
    static constexpr double drag = 1.0f;
    double rotation_speed = 3;  
    bool is_accelerate = false;
    bool isDead = false;
    math::vec2 speed = { 10,10 };
};