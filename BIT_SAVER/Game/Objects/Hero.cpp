/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: BIT_SAVER
Author:  Sunwoo Lee

-----------------------------------------------------------------*/
#include"Hero.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity
#include"../Levels/MainOption.h"

#define VOL 0.5f;


Hero::Hero(glm::vec2 startPos) :
    timer(0),
    GameObject(startPos, glm::vec2{ 2,2 }),
    UpAttackKey(InputKey::Keyboard::None),
    DownAttackKey(InputKey::Keyboard::None)
{
   AddGOComponent(new Sprite("../spt/hero.spt", this));
   currState = &stateIdle;
   currState->Enter(this);
   GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::hero_run));
}

void Hero::Update(double dt)
{
    GameObject::Update(dt);
    UpdateXVelocity(dt);
    GetGOComponent<Collision>()->UpdateCollision(GetPosition(),GetScale());
    UpAttackKey = Engine::GetAttack_Key().UpAttackKey;
    DownAttackKey = Engine::GetAttack_Key().DownAttackKey;
}

void Hero::Draw(glm::mat3 camera_matrix)
{
   GameObject::Draw(camera_matrix);
}

void Hero::UpdateXVelocity([[maybe_unused]]double dt)
{

}

// idle state
void Hero::State_Idle::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::hero_run));
}

void Hero::State_Idle::Update(GameObject* object, double dt)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->timer += dt;
}

void Hero::State_Idle::TestForExit(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->timer > 0)
    {
        //hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::hero_run));
        hero->ChangeState(&hero->stateRunning);
    }

}

//run state
void Hero::State_Running::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::hero_run));
    hero->SetPosition({ hero->GetPosition().x, -5});
    hero->SetVelocity({ 0,0});
}

void Hero::State_Running::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
    //Hero* hero = static_cast<Hero*>(object);
}

void Hero::State_Running::TestForExit(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    if ((hero->UpAttackKey.IsKeyDown() == true && hero->UpAttackKey.IsKeyReapeated() == false))
    {
        hero->ChangeState(&hero->stateJump);
    }
    if ((hero->DownAttackKey.IsKeyDown() == true && hero->DownAttackKey.IsKeyReapeated() == false))
    {
        hero->ChangeState(&hero->stateAttack);
    }
}

// fall state
void Hero::State_Falling::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::down));
    hero->SetVelocity({0,-10});
}

void Hero::State_Falling::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
    //Hero* hero = static_cast<Hero*>(object);
}

void Hero::State_Falling::TestForExit(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetPosition().y < -5)
    {
        hero->ChangeState(&hero->stateRunning);
    }
    if ((hero->UpAttackKey.IsKeyDown() == true && hero->UpAttackKey.IsKeyReapeated() == false))
    {
        hero->ChangeState(&hero->stateJump);
    }
    if ((hero->DownAttackKey.IsKeyDown() == true && hero->DownAttackKey.IsKeyReapeated() == false))
    {
        hero->SetVelocity({ 0,0 });
        hero->SetPosition({ hero->GetPosition().x, -5 });
        hero->ChangeState(&hero->stateAttack);
    }

}
// attack state
void Hero::State_Attack::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->SetVelocity({ 0,-jumpVelocity });
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
}

void Hero::State_Attack::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetPosition().y < -5)
    {
        hero->SetVelocity({ 0,0 });
        hero->SetPosition({ hero->GetPosition().x, -5 });
    }
}

void Hero::State_Attack::TestForExit(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetGOComponent<Sprite>()->IsAnimationDone() == true)
    {
        hero->ChangeState(&hero->stateRunning);
    }
}

// state jump
void Hero::State_Jump::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->SetVelocity({0,jumpVelocity});
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
}

void Hero::State_Jump::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
   // Hero* hero = static_cast<Hero*>(object);
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetPosition().y > 5)
    {
        hero->SetVelocity({ 0,0 });
        hero->SetPosition({ hero->GetPosition().x, 5 });
    }
}

void Hero::State_Jump::TestForExit(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetGOComponent<Sprite>()->IsAnimationDone() == true)
    {
        //hero->SetVelocity({ 0,-10 });
        //hero->SetPosition({ hero->GetPosition().x, 5 });
        hero->ChangeState(&hero->statefalling);
    }
}
