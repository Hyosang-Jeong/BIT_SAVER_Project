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
    hero_state(Hero_state::RUN_ENTER),
  GameObject(startPos, glm::vec2{ 2,2 })
{
    AddGOComponent(new Sprite("../spt/hero.spt", this));
   
}

void Hero::Update(double dt)
{
    GameObject::Update(dt);

    UpdateXVelocity(dt);

    if (hero_state == RUN_ENTER)
    {
        GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::hero_run));
        hero_state = RUN;
    }

    else if (hero_state == UP_ENTER)
    {
        GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
        hero_state = UP;
    }

    else if (hero_state == DOWN_ENTER)
    {
        if (GetGOComponent<Sprite>()->IsAnimationDone() == true)
        {
            GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::down));
            hero_state = RUN_ENTER;
        }
    }

    else if (hero_state == DOWN_ATTACK_ENTER)
    {
        GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
        hero_state = DOWN_ATTACK;
    }
    else if (hero_state == DOWN_ATTACK)
    {
        if (GetGOComponent<Sprite>()->IsAnimationDone() == true)
        {
            GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::up_attck));
            hero_state = RUN_ENTER;
        }
    
    }
    else if (hero_state == DOWN)
    { 
        if (Getposition().y == -5)
        {
            hero_state = RUN_ENTER;
        }
    }
    GetGOComponent<Collision>()->UpdateCollision(GetPosition(),GetScale());
}

void Hero::Draw(glm::mat3 camera_matrix)
{
   GameObject::Draw(camera_matrix);
}

glm::vec2 Hero::Getposition()
{
    return GameObject::GetPosition();
}


void Hero::UpdateXVelocity([[maybe_unused]] double dt)
{

    if (Getposition().y >5)
    {
        SetVelocity({ 0,-10});
        SetPosition({ Getposition().x, 5 });
        hero_state =DOWN;
    }

     if (Getposition().y <-5)
    {
        SetVelocity({ 0,0 });
        SetPosition({ Getposition().x, -5 });
    }

    if (moveUp1Key.IsKeyDown() == true || moveUp2Key.IsKeyDown()==true)
    {
        hero_state = UP_ENTER;
        SetVelocity({ 0,80 });
    }
     if (moveDown1Key.IsKeyDown() == true || moveDown2Key.IsKeyDown() == true)
    {
         hero_state = DOWN_ATTACK_ENTER;
         SetVelocity({ 0,-80 });
    }
}





