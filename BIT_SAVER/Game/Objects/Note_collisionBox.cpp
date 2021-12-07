/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Note_collisionBox.cpp
Project: BIT_SAVER
Author:
Creation date: 10/10/2021
-----------------------------------------------------------------*/
#include"Note_collisionBox.h"
#include"../../Engine/Engine.h"
Note_box::Note_box(glm::vec2 startPos) :
GameObject(startPos, glm::vec2{ 1,20 })
{
	AddGOComponent(new Sprite("../images/Note_collision_box.png", this));
}

void Note_box::Update(double dt)
{
	GameObject::Update(dt);
	is_destroyed = true;
}

void Note_box::ResolveCollision(GameObject* test_obj)
{
	if (test_obj->GetObjectType() == GameObjectType::Note && attack_pressed == true && is_repeated == false)
	{
		if (test_obj->GetPosition().y == attack_ypos)
		{
		    Engine::GetMusic().Play(SOUND_NUM::SOUND_EFFECT2);
			if (attack_ypos == 5)
			{
				Hit[0] = true;
				Hit_pos[0] = test_obj->GetPosition();
			}
			else
			{
				Hit[1] = true;
				Hit_pos[1] = test_obj->GetPosition();
			}
			test_obj->set_destroy(true);
			is_destroyed = true;
			is_repeated = true;
			Engine::GetLogger().LogEvent("Note destroyed!");
		}
		return;
	}

	else// for miss
	{
		if (test_obj->GetPosition().y == 5)  //up track
		{
			if (test_obj->GetPosition().x + test_obj ->GetTexturetoNDC().x/2.0< GetPosition().x - GetTexturetoNDC().x / 2.0)
			{
				//set miss texture's pos
				Hit[0] = false;
			//	Engine::GetLogger().LogEvent("Note miss!");

				Hit_pos[0].x = GetPosition().x;
				Hit_pos[0].y = test_obj->GetPosition().y;
				is_destroyed = false;
			}
		}
		else
		{
			if (test_obj->GetPosition().x + test_obj->GetTexturetoNDC().x / 2.0 < GetPosition().x - GetTexturetoNDC().x / 2.0)
			{
				Hit[1] = false;
			//	Engine::GetLogger().LogEvent("Note miss!");
				Hit_pos[1].x = GetPosition().x - GetTexturetoNDC().x / 2.0f;
				Hit_pos[1].y = test_obj->GetPosition().y;
				is_destroyed = false;
			}
		}
	}
}

const bool Note_box::GetDestroyed() const
{
	return is_destroyed;
}


void Note_box::Draw(glm::mat3 camera_matrix)
{
	GameObject::Draw(camera_matrix);
	//if (Hit[0] == true)
	//{
	//	Hit_tex.Draw(world_range, "Basic_model", "Hero", { Hit_pos[0].x,  Hit_pos[0].y });
	//}
	//if (Hit[1] == true)
	//{
	//	Hit_tex.Draw(world_range, "Basic_model", "Hero", { Hit_pos[1].x,  Hit_pos[1].y });
	//}

	//if (Hit[0] == false)
	//{
	//	Miss_tex.Draw(world_range, "Basic_model", "Hero", { Hit_pos[0].x,  Hit_pos[0].y });
	//}
	//if (Hit[1] == false)
	//{
	//	Miss_tex.Draw(world_range, "Basic_model", "Hero", { Hit_pos[1].x,  Hit_pos[1].y });
	//}
}

glm::vec2 Note_box::Getposition()
{
	return GameObject::GetPosition();
}

void Note_box::set_attack_flag(bool value,GLfloat ypos)
{
	if (value == false)
	{
		is_repeated = false;
	}
		attack_pressed = value;
		attack_ypos = ypos;
}

