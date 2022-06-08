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
#include"../Levels/State.h"
#include "../../Engine/GameObject/GameObjectManager.h"
#include"../../Game/Levels/Clear.h"
#include"Score.h"
#define VOL 0.5f;


Hero::Hero(glm::vec2 startPos) :
    timer(0),
    GameObject({ startPos.x , startPos.y - 2 }, glm::vec2{ 1.5,1.5 }),
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
    UpAttackKey = Engine::GetAttack_Key().UpAttackKey;
    DownAttackKey = Engine::GetAttack_Key().DownAttackKey;
}

void Hero::Draw(glm::mat3 camera_matrix)
{
   GameObject::Draw(camera_matrix);
}

void Hero::die()
{
    if (currState != &stateDie)
    {
        SetRotation(0.85);
        ChangeState(&stateDie);
    }
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
        hero->ChangeState(&hero->stateRunning);
    }
}

//run state
void Hero::State_Running::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::hero_run));
    hero->SetPosition({ hero->GetPosition().x, -7});
    hero->SetVelocity({ 0,0});
}

void Hero::State_Running::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{}

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
    hero->SetVelocity({0,-3});
}

void Hero::State_Falling::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::down));
    hero->UpdateVelocity({ 0,-1 });
}

void Hero::State_Falling::TestForExit(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetPosition().y < -7)
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
        hero->ChangeState(&hero->stateAttack);
    }

}
// attack state
void Hero::State_Attack::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->SetVelocity({ 0,-jumpVelocity });
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
    Engine::GetMusic().Play(SOUND_NUM::HIT);
}

void Hero::State_Attack::Update([[maybe_unused]] GameObject* object,  [[maybe_unused]]double dt)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetPosition().y < -5)
    {
        hero->SetVelocity({ 0,0 });
        hero->SetPosition({ hero->GetPosition().x, -7 });
    }

}

void Hero::State_Attack::TestForExit(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetGOComponent<Sprite>()->IsAnimationDone() == true)
    {
        hero->ChangeState(&hero->stateRunning);
    }
    if ((hero->UpAttackKey.IsKeyDown() == true && hero->UpAttackKey.IsKeyReapeated() == false))
    {
        hero->ChangeState(&hero->stateJump);
    }
    if ((hero->DownAttackKey.IsKeyDown() == true && hero->DownAttackKey.IsKeyReapeated() == false))
    {
        hero->ChangeState(&hero->stateAttack);
    }
}

// state jump
void Hero::State_Jump::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
    Engine::GetMusic().Play(SOUND_NUM::HIT);
}

void Hero::State_Jump::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
    Hero* hero = static_cast<Hero*>(object);

    hero->SetPosition({ hero->GetPosition().x,3 });

    if (hero->GetPosition().y > 3)
    {
        hero->SetVelocity({ 0,0 });
        hero->SetPosition({ hero->GetPosition().x, 3 });
    }

}

void Hero::State_Jump::TestForExit(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetGOComponent<Sprite>()->IsAnimationDone() == true)
    {
        hero->ChangeState(&hero->statefalling);
    }
    if (hero->DownAttackKey.IsKeyDown() == true && hero->DownAttackKey.IsKeyReapeated() == false)
    {
        hero->ChangeState(&hero->stateAttack);
    }
}

void Hero::State_Die::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::hero_die));
    hero-> SetPosition({ -4,-8 });
}

void Hero::State_Die::Update(GameObject* , double )
{
    ////Hero* hero = static_cast<Hero*>(object);
    //glm::vec2 target_scale = glm::vec2{ 2,2 };
    ////glm::vec2 target_position = hero->GetPosition() / 10.f;
    ////if (Engine::GetGSComponent<Camera>()->get_scale().x < target_scale.x)
    ////{
    ////    Engine::GetGSComponent<Camera>()->set_scale({ Engine::GetGSComponent<Camera>()->get_scale().x + dt, Engine::GetGSComponent<Camera>()->get_scale().y + dt });
    ////    Engine::GetGSComponent<Camera>()->SetPosition({ Engine::GetGSComponent<Camera>()->GetPosition().x + (dt*target_position.x), Engine::GetGSComponent<Camera>()->GetPosition().y + (dt * target_position.y) });
    ////}
    //if (Engine::GetGSComponent<Camera>()->get_scale().x < target_scale.x)
    //{
    //    Engine::GetGSComponent<Camera>()->set_scale({ Engine::GetGSComponent<Camera>()->get_scale().x + dt, Engine::GetGSComponent<Camera>()->get_scale().y + dt });
    //}
} 

void Hero::State_Die::TestForExit(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetGOComponent<Sprite>()->IsAnimationDone() == true)
    {
        Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Clear));
        static_cast<Clear*>(Engine::GetGameStateManager().Find("Clear"))->Setstats("You Lose", Engine::GetGSComponent<Score>()->Getscore(), Engine::GetGSComponent<Score>()->GetscoreCount());
        static_cast<Clear*>(Engine::GetGameStateManager().Find("Clear"))->Set_lose(true);
    }
}


void Hero::State_Magumagu::Enter(GameObject* object)
{
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::down));
    hero->SetPosition({ hero->GetPosition().x,-2 }); 
    hero->SetVelocity({ 0, 0 });
}

void Hero::State_Magumagu::Update(GameObject* object, double )
{
    Hero* hero = static_cast<Hero*>(object);

    if (hero->GetGOComponent<Sprite>()->IsAnimationDone() == true)
    {
        hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::down));
    }

    if ((hero->DownAttackKey.IsKeyDown() == true && hero->DownAttackKey.IsKeyReapeated() == false) ||
        (hero->UpAttackKey.IsKeyDown() == true && hero->UpAttackKey.IsKeyReapeated() == false))
    {
        Engine::GetMusic().Play(SOUND_NUM::HIT);
        hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
        Engine::GetGSComponent<Camera>()->shake(0.015f, 0.1f, 1.f);
    }
}

void Hero::State_Magumagu::TestForExit(GameObject* )
{
    // exit this state if the hard note is set_destroy == true; in NoteHard.cpp.
}

void Hero::Enter_Magumagu()
{
    //Hero* hero = static_cast<Hero*>( );
    ChangeState(&this->stateMagumagu);
}

void Hero::Exit_Magumagu()
{
    ChangeState(&this->statefalling);

    //if (this->GetPosition().y > 0)
    //{
    //    ChangeState(&this->statefalling);
    //}
    //else
    //{
    //    ChangeState(&this->stateRunning);
    //}
}