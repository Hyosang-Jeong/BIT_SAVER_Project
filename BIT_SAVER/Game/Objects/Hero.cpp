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

Hero::Hero(glm::vec2 startPos) :
	moveLeftKey(InputKey::Keyboard::Left),
	moveRightKey(InputKey::Keyboard::Right),
	moveUpKey(InputKey::Keyboard::Up),
	moveDownKey(InputKey::Keyboard::Down),
	AttackKey(InputKey::Keyboard::Space),
	GameObject(startPos, 0, glm::vec2{ 2,2 })
{
	texture.setup_texobj("../images/extra1.png");
	Hit_tex.setup_texobj("../images/Hit_star.png");
	Miss_tex.setup_texobj("../images/miss.png");
}


void Hero::Update(double dt)
{
	GameObject::Update(dt);

	UpdateXVelocity(dt);
	Attack_Check();
}

void Hero::Draw()
{
	texture.Draw(mdl_to_ndc_xform, "Basic_model", "Hero");

	if (Hit[0] == true )
	{
		Hit_tex.Draw(world_range, "Basic_model", "Hero",{ Hit_pos[0].x,  Hit_pos[0].y });
	} 
	if (Hit[1] == true)
	{
		Hit_tex.Draw(world_range, "Basic_model", "Hero", { Hit_pos[1].x,  Hit_pos[1].y });
	}

	if (Hit[0] == false)
	{
		Miss_tex.Draw(world_range, "Basic_model", "Hero", { Hit_pos[0].x+1,  Hit_pos[0].y });
	}
	if (Hit[1] == false)
	{
		Miss_tex.Draw(world_range, "Basic_model", "Hero", { Hit_pos[1].x+1,  Hit_pos[1].y });
	}
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
		for (auto& object : Engine::GetGameStateManager().gameObjectManager.GetgameObjects())
		{
			if (object->GetObjectType() == GameObjectType::Note)
			{
				if (Engine::GetGameStateManager().gameObjectManager.collision_check(Note_collision_box, object) == true)
				{
					Engine::GetLogger().LogEvent("Note and Note box collided");
					if (object->GetPosition().y == Getposition().y && AttackKey.IsKeyDown() == true && attack_pressed == false)
					{
						if (Getposition().y == 5)  
						{
							Hit[0] = true;
							Hit_pos[0] = object->GetPosition();
						}
						else
						{
							Hit[1] = true;
							Hit_pos[1] = object->GetPosition();
				     	}
						object->set_destroy(true);
						attack_pressed = true;
					}
				}
				if (Note_collision_box != nullptr)
				{
					if (object->GetAABB().max.x < Note_collision_box->GetAABB().min.x) //miss
					{
						if (object->GetPosition().y == 5)  //up track
						{
							Hit[0] = false;
							Hit_pos[0].x = Note_collision_box->GetPosition().x - Note_collision_box->GetTexturetoNDC().x / 2.0f;
							Hit_pos[0].y = object->GetPosition().y;
						}
						else
						{
							Hit[1] = false;
							Hit_pos[1].x = Note_collision_box->GetPosition().x - Note_collision_box->GetTexturetoNDC().x / 2.0f;
							Hit_pos[1].y = object->GetPosition().y;
						}
					}
				}
			}
		}

		if (AttackKey.IsKeyReleased() == true)
		{
			attack_pressed = false;
		}
}


