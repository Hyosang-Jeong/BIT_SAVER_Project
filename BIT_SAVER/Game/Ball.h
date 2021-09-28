/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.h
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once
#include"Ball_Anims.h"
#include "..\Engine\GameObject.h"
#include"GameObjectTypes.h"
namespace math { struct vec2; }
class Ball : public CS230::GameObject 
{
public:
    Ball(math::vec2 startPos);
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;

    GameObjectType GetObjectType()
    {
        return GameObjectType::Ball;
    }
    std::string GetObjectTypeName()
    {
        return "Ball";
    }
private:
    static constexpr double bounceVelocity = 750;

    class State_Bounce : public State 
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Bounce"; }
    };
    class State_Land : public State 
    {
    public:
        virtual void Enter(GameObject* object)override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Land"; }
    };
    State_Bounce bounce;
    State_Land land;

};



