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
    VolumeUp(InputKey::Keyboard::U),
    VolumeDown(InputKey::Keyboard::D),
    GameObject(startPos,  glm::vec2{ 2,2 })
{
	texture.setup_texobj("../images/extra1.png");
}

void Hero::Update(double dt)
{
    GameObject::Update(dt);

    UpdateXVelocity(dt);
    Attack_Check();
}

void Hero::Draw(glm::mat3 )
{
	texture.Draw(mdl_to_ndc_xform , "Basic_model", "Hero");
}

glm::vec2 Hero::Getposition()
{
    return GameObject::GetPosition();
}

std::pair<bool, GLfloat> Hero::Get_Attack_flag()
{
	return { attack_pressed,GetPosition().y };
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


