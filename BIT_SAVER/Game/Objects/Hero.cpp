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
    moveUpKey(InputKey::Keyboard::Up),
    moveDownKey(InputKey::Keyboard::Down),
    AttackKey(InputKey::Keyboard::Space),
  GameObject(startPos, glm::vec2{ 2,2 })
{
    AddGOComponent(new Sprite("../spt/hero.spt", this));
    GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(hero_anim::hero_run));
}

void Hero::Update(double dt)
{
    UpdateXVelocity(dt);
    Attack_Check();
    GameObject::Update(dt);
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
    if (moveUpKey.IsKeyDown() == true)
    {
        SetPosition({ Getposition().x, 5 });
    }

    else if (moveDownKey.IsKeyDown() == true)
    {
        SetPosition({ Getposition().x, -5 });
    }

    else if (moveLeftKey.IsKeyDown() == true)
    {
        UpdatePosition({ -dt,0 });
    }
    else if (moveRightKey.IsKeyDown() == true)
    {
        UpdatePosition({ dt,0 });
    }
}

void Hero::Attack_Check()
{
		if (AttackKey.IsKeyDown() == true)
		{
			attack_pressed = true;
		}
		if (AttackKey.IsKeyReleased() == true)
		{
			attack_pressed = false;
		}
}


