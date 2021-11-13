/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: BIT_SAVER
Author:
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"Hero.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity
#define VOL 0.5f;


Hero::Hero(glm::vec2 startPos) :
    moveLeftKey(InputKey::Keyboard::Left),
    moveRightKey(InputKey::Keyboard::Right),
    moveUp1Key(InputKey::Keyboard::Up),
    moveDown1Key(InputKey::Keyboard::Down),
    moveUp2Key(InputKey::Keyboard::F),
    moveDown2Key(InputKey::Keyboard::J),
    AttackKey(InputKey::Keyboard::Space),
    //hero_state(Hero_state::RUN_ENTER),
    timer(0),
    GameObject(startPos, glm::vec2{ 2,2 })
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
    std::cout << currState << std::endl;
    //if (hero_state == RUN_ENTER)
    //{
    //    GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::hero_run));
    //    hero_state = RUN;
    //}

    //else if (hero_state == UP_ENTER)
    //{
    //    GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
    //    hero_state = UP;
    //}

    //else if (hero_state == DOWN_ENTER)
    //{
    //    if (GetGOComponent<Sprite>()->IsAnimationDone() == true)
    //    {
    //        GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::down));
    //        hero_state = RUN_ENTER;
    //    }
    //}

    //else if (hero_state == DOWN_ATTACK_ENTER)
    //{
    //    GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
    //    hero_state = DOWN_ATTACK;
    //}
    //else if (hero_state == DOWN_ATTACK)
    //{
    //    if (GetGOComponent<Sprite>()->IsAnimationDone() == true)
    //    {
    //        GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
    //        hero_state = RUN_ENTER;
    //    }
    //
    //}
    //else if (hero_state == DOWN)
    //{ 
    //    if (GetPosition().y == -5)
    //    {
    //        hero_state = RUN_ENTER;
    //    }
    //}

    GetGOComponent<Collision>()->UpdateCollision(GetPosition(),GetScale());
}

void Hero::Draw(glm::mat3 camera_matrix)
{
   GameObject::Draw(camera_matrix);
}

void Hero::UpdateXVelocity([[maybe_unused]]double dt)
{
    //if (GetPosition().y >5)
    //{
    //    SetVelocity({ 0,-10});
    //    SetPosition({ GetPosition().x, 5 });
    //    hero_state =DOWN;
    //}

    // if (GetPosition().y <-5)
    //{
    //    SetVelocity({ 0,0 });
    //    SetPosition({ GetPosition().x, -5 });
    //}

    //if (moveUp1Key.IsKeyDown() == true || moveUp2Key.IsKeyDown()==true)
    //{
    //    hero_state = UP_ENTER;
    //    SetVelocity({ 0,80 });
    //}
    // if (moveDown1Key.IsKeyDown() == true || moveDown2Key.IsKeyDown() == true)
    //{
    //     hero_state = DOWN_ATTACK_ENTER;
    //     SetVelocity({ 0,-80 });
    //}
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
    if ((hero->moveUp1Key.IsKeyDown() == true && hero->moveUp1Key.IsKeyReapeated() == false) ||
        (hero->moveUp2Key.IsKeyDown() == true && hero->moveUp2Key.IsKeyReapeated() == false))
    {
        hero->ChangeState(&hero->stateJump);
    }
    if ((hero->moveDown1Key.IsKeyDown() == true && hero->moveDown1Key.IsKeyReapeated() == false) ||
        (hero->moveDown2Key.IsKeyDown() == true && hero->moveDown2Key.IsKeyReapeated() == false))
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
    if ((hero->moveUp1Key.IsKeyDown() == true && hero->moveUp1Key.IsKeyReapeated() == false) || 
          (hero->moveUp2Key.IsKeyDown() == true && hero->moveUp2Key.IsKeyReapeated() ==false))
    {
        hero->ChangeState(&hero->stateJump);
    }
    if ((hero->moveDown1Key.IsKeyDown() == true && hero->moveDown1Key.IsKeyReapeated() == false) ||
        (hero->moveDown2Key.IsKeyDown() == true && hero->moveDown2Key.IsKeyReapeated() == false))
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
