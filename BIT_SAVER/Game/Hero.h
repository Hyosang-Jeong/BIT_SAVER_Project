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
#include "..\Engine\Sprite.h" //sprite
#include "..\Engine\Input.h" //input key
#include "..\Engine\Vec2.h" //vec2 struct 
#include "..\Engine\GameObject.h" // GameObject inheritance
#include"GameObjectTypes.h"
class Hero : public CS230::GameObject {
public:
    Hero(math::vec2 startPos);
    void Update(double dt) override;
    math::vec2 Getposition();
    GameObjectType GetObjectType() override
    {
       return GameObjectType::Hero;
    }
    std::string GetObjectTypeName() override
    {
        return "Hero";
    }
    bool IsDead() { return isDead; }
    void Draw(math::TransformMatrix displayMatrix);
    void ResolveCollision(GameObject* objectB) override;
    bool CanCollideWith(GameObjectType objectBType) override;
private:
    bool isDead;
    GameObject* standingOnObject;
    CS230::InputKey moveLeftKey;
    CS230::InputKey moveRightKey;
    CS230::InputKey jumpKey;
    static constexpr double acceleration = 250;
    static constexpr double drag = 500;
    static constexpr double max_velocity = 500;
    static constexpr double jumpVelocity = 1000;
    static constexpr double hurtTime = 2;
    double hurtTimer=0;
    bool drawHero=true;

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };
    class State_Running : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };
    class State_Skidding : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Skidding"; }
    };
    class State_Jumping : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Falling : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };
    State_Idle stateIdle;
    State_Running stateRunning;
    State_Skidding stateSkidding;
    State_Jumping stateJumping;
    State_Falling stateFalling;

    void UpdateXVelocity(double dt);     //Change X velocity stuff

};