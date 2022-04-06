/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: BIT_SAVER
Author:  Sunwoo Lee

-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"

enum class hero_anim
{
    hero_run,
    up_attck,
    down,
    hero_die
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
    void Draw(glm::mat3 camera_matrix) override;
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Hero;
    }
    //std::string GetObjectTypeName() override { return "Hero"; }
    void die();

    void Enter_Magumagu();
    void Exit_Magumagu();
    InputKey UpAttackKey;
    InputKey DownAttackKey;

private:

    class State_Idle : public ObjectState {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };
    class State_Running : public ObjectState {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };
    class State_Falling : public ObjectState {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Fallling"; }
    };
    class State_Attack : public ObjectState {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Attack"; }
    };
    class State_Jump : public ObjectState {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Jump"; }
    };
    class State_Die : public ObjectState {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Die"; }
    };
    class State_Magumagu : public ObjectState {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Magumagu"; }
    };

    State_Idle stateIdle;
    State_Running stateRunning;
    State_Falling statefalling;
    State_Attack stateAttack;
    State_Jump stateJump;
    State_Die stateDie;
    State_Magumagu stateMagumagu;
    //Hero_state hero_state;

    static constexpr double acceleration = 1;
    static constexpr double drag = 500;
    static constexpr double max_velocity = 500;
    static constexpr double jumpVelocity = 1000;

    double timer;

    void UpdateXVelocity(double dt);     //Change X velocity stuff
};