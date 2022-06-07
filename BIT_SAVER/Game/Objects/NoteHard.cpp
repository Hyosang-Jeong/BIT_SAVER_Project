/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Notes.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Hyosang Jung 

-----------------------------------------------------------------*/
#include"../../Engine/Engine.h"
#include "NoteHard.h"
#include"../../Engine/Sprite/GameParticles.h"
#include "EnergyBar.h"
//#include "../../Engine/Music/music.h"
//#include "../../Game/Levels/State.h"
//#include "../../Engine/Window/Window.h"
#include"Score.h"
//#include"../../Engine/Physics/Camera.h"
//#include"../Levels/MainOption.h"
//#include"obstacle.h"
#include "Score Enum.h"
#include "../Objects/Hero.h"

HardNote::HardNote(glm::vec2 startPos, glm::vec2 velocity, double time) :
    isMiss(false),
	UpAttackKey(InputKey::Keyboard::None),
	DownAttackKey(InputKey::Keyboard::None),
	life_time(time),
GameObject(startPos, glm::vec2{ 2,1 })
{
	timer = 0.0;
	start_timer = false;

	if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
	{
		energy = (static_cast<EnergyBar*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Energy_bar)));
	}
	AddGOComponent(new Sprite("../images/Hit_star.png", this));
	SetVelocity(velocity);

}

void HardNote::Update(double dt)
{
	UpAttackKey = Engine::GetAttack_Key().UpAttackKey;
	DownAttackKey = Engine::GetAttack_Key().DownAttackKey;

	if (change_state == true)
	{
		change_state = false;
		static_cast<Hero*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero))->Enter_Magumagu();
	}

	if (start_timer == true)
	{
		if (timer > life_time)
		{
			static_cast<Hero*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero))->Exit_Magumagu();
			set_destroy(true);
		}
		timer += dt;
	}
	else if (GetPosition().x < -10)
	{
		set_destroy(true);
	}

	GameObject::Update(dt);

	Hit_Check();
	
	
}

void HardNote::Draw(glm::mat3 camera_matrix)
{
	GameObject::Draw(camera_matrix);
}

glm::vec2 HardNote::Getposition()
{
    return GameObject::GetPosition();
}

void HardNote::Hit_Check()
{
	if (start_timer == true)		// other than first hit doesnt need to find out if hit up or down
	{
		if ((UpAttackKey.IsKeyDown() == true && UpAttackKey.IsKeyReapeated() == false)||
			(DownAttackKey.IsKeyDown() == true && DownAttackKey.IsKeyReapeated() == false))
		{
			switch (static_cast<int>(Score_check()))
			{
				case static_cast<int>(SCORE::PERFECT) :
				{}
				case static_cast<int>(SCORE::GOOD) :
				{}
				case static_cast<int>(SCORE::BAD) :
				{
					Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
					UpdatePosition({ 0.25,0 });
					UpdateScale({ 0.1,0.1 });
					if (Engine::GetGSComponent<Score>() != nullptr)
					{
						Engine::GetGSComponent<Score>()->AddScore(HardNote_Score);
					}
					//isMiss = false;
					break;
				}
				default:
					break;
			}
		}
	}
	else		// first hit needs to find out if hit up or down
	{
		double hero_y_pos = static_cast<Hero*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero))->GetPosition().y;

		if ((UpAttackKey.IsKeyDown() == true && UpAttackKey.IsKeyReapeated() == false) && hero_y_pos <= -2)
		{
			switch (Score_check())
			{
				case static_cast<int>(SCORE::PERFECT) :
				{}
				case static_cast<int>(SCORE::GOOD) :
				{}
				case static_cast<int>(SCORE::BAD) :
				{
					Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
					isMiss = false;
					start_timer = true;
					change_state = true;
					UpdatePosition({ 0.25,0 });
					SetVelocity({ -2, 0 });
					UpdateScale({ 0.5,0.1 });
					if (Engine::GetGSComponent<Score>() != nullptr)
					{
						Engine::GetGSComponent<Score>()->AddScore(HardNote_Score);
					}
					break;
				}
				default:
					break;
			}

		}

		if ((DownAttackKey.IsKeyDown() == true && DownAttackKey.IsKeyReapeated() == false && hero_y_pos >= -2))
		{
			switch (Score_check())
			{
				case static_cast<int>(SCORE::PERFECT) :
				{}
				case static_cast<int>(SCORE::GOOD) :
				{}
				case static_cast<int>(SCORE::BAD) :
				{
					Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
					isMiss = false;
					start_timer = true;
					change_state = true;
					UpdatePosition({ 0.25,0 });
					SetVelocity({ -2, 0 });
					UpdateScale({ 0.5,0.1 });
					if (Engine::GetGSComponent<Score>() != nullptr)
					{
						Engine::GetGSComponent<Score>()->AddScore(HardNote_Score);
					}
					break;
				}
				default:
					break;
			}

		}
	}
}

int HardNote::Score_check()
{
	float HeroPostion = 0;
	float NotePosition = GetPosition().x;

	if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
	{
		HeroPostion = -4.f;
	}

	if (NotePosition - HeroPostion <= 0.5f && NotePosition - HeroPostion >= -0.5f)//0.4
	{
		return static_cast<int>(SCORE::PERFECT);
	}
	else if (NotePosition - HeroPostion <= 1.f && NotePosition - HeroPostion >= -1.f)//0.4
	{
		return static_cast<int>(SCORE::GOOD);
	}
	else if (NotePosition - HeroPostion <= 1.5f && NotePosition - HeroPostion >= -1.5f)//0.4
	{
		return static_cast<int>(SCORE::BAD);
	}
	return static_cast<int>(SCORE::MISS);
}


