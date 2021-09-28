/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.h
Project: CS230
Author: Hyosang Jung
Creation date: 4/16/2021
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\GameObject.h"
#include"GameObjectTypes.h"

class Hero;

class Bunny : public CS230::GameObject
{
public:

    Bunny(math::vec2 pos, std::vector<double> patrolNodes, Hero* heroPtr);
    GameObjectType GetObjectType() override { return GameObjectType::Bunny; }
    std::string GetObjectTypeName() override { return "Bunny"; }
    void ResolveCollision(GameObject* objectA) override;
private:
    class State_Patrol : public State {
    public:
        State_Patrol() {}
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "bounce"; }
    private:
    };
    class State_Attack : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "attack"; }
    };
    class State_Dead : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "land"; }
    private:
    };
    State_Patrol statePatrol;
    State_Attack stateAttack;
    State_Dead stateDead;
    Hero* heroPtr;

    std::vector<double> patrolNodes;
    int currPatrolNode;
    static constexpr int velocity = 75;
};
