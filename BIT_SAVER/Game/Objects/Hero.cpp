/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"Hero.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity

Hero::Hero(glm::vec2 startPos) :
	moveLeftKey(InputKey::Keyboard::Left),
	moveRightKey(InputKey::Keyboard::Right),
	moveUpKey(InputKey::Keyboard::Up),
	moveDownKey(InputKey::Keyboard::Down),
	AttackKey(InputKey::Keyboard::Space),
	GameObject(startPos, 0, glm::vec2{ 1,1 })
{
	texture.setup_texobj("../images/extra1.png");
}


void Hero::Update(double dt)
{
	GameObject::Update(dt);

	UpdateXVelocity(dt);
	Attack_Check();

	//std::cout << Getposition().x << "       " << Getposition().y << std::endl;

}

void Hero::Draw()
{
	texture.Draw(mdl_to_ndc_xform, "Basic_model", "Hero");
}

glm::vec2 Hero::Getposition()
{
	return GameObject::GetPosition();
}

void Hero::UpdateXVelocity([[maybe_unused]] double dt)
{
	if (moveUpKey.IsKeyDown() == true)
	{
		//SetPosition({ Getposition().x, 5 });
		UpdatePosition({ 0,dt });
	}

	else if (moveDownKey.IsKeyDown() == true)
	{
		//SetPosition({ Getposition().x, -5 });
		UpdatePosition({ 0,-dt });
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
	if (AttackKey.IsKeyDown() == true && attack_pressed == false)
	{

		//find collision box position
		GameObject* Note_collision_box = nullptr;

		for (auto& object : Engine::GetGameStateManager().gameObjectManager.GetgameObjects())
		{
			if (object->GetObjectType() == GameObjectType::Note_collisionBox)
			{
				Note_collision_box = object;
				break;
			}
		}

		//Collision check
		for (auto& object : Engine::GetGameStateManager().gameObjectManager.GetgameObjects())
		{
			if (object->GetObjectType() == GameObjectType::Note)
			{
				if (Engine::GetGameStateManager().gameObjectManager.collision_check(Note_collision_box, object) == true)
				{
					object->set_destroy(true);
				}
			}
		}
		attack_pressed = true;
	}

	if (AttackKey.IsKeyReleased() == true)
	{
		attack_pressed = false;
	}

}
