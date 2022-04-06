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

		//Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->ChangeState();
		static_cast<Hero*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero))->Enter_Magumagu();
		//Hero* hero = static_cast<Hero*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero));
		//hero->Enter_Magumagu();
	}

	if (start_timer == true)
	{
		if (timer > life_time)
		{
			static_cast<Hero*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero))->Exit_Magumagu();
			set_destroy(true);
		}

		timer += dt;
		SetScale({ 2,1 });
	}
	else if (GetPosition().x < -10)
	{
		set_destroy(true);
	}

	GameObject::Update(dt);
	Hit_Check();
	
	if (isMiss == true)
	{
	    if (energy->GetScale().x > 0)
	    {
		energy->SetScale(glm::vec2{ energy->GetScale().x - (dt / 10),energy->GetScale().y });
		energy->UpdatePosition(glm::vec2{ -(dt / 10),0 });
	    }
	}	
}

void HardNote::Draw(glm::mat3 camera_matrix)
{
	//glm::mat3 trans_mat
	//{
	//	1,0,0,
	//	0,1,0,
	//	-0.25,0,1
	//};
	//GameObject::Draw(camera_matrix * trans_mat);
	GameObject::Draw(camera_matrix);
}

glm::vec2 HardNote::Getposition()
{
    return GameObject::GetPosition();
}

void HardNote::Hit_Check()
{
	if (start_timer == true)
	{
		if (UpAttackKey.IsKeyDown() == true && UpAttackKey.IsKeyReapeated() == false)
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
					SetVelocity({ -5, 0 });
					UpdatePosition({ 1,0 });
					UpdateScale({ 1,1 });
					//isMiss = false;
					break;
				}
			}
			Engine::GetGSComponent<Score>()->AddScore(50000);
		}
	}
	else
	{
		if ((UpAttackKey.IsKeyDown() == true && UpAttackKey.IsKeyReapeated() == false) && GetPosition().y > 0)
		{
			switch (static_cast<int>(Score_check()))
			{
				case static_cast<int>(SCORE::PERFECT) :
				{
					Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
					isMiss = false;
					start_timer = true;
					change_state = true;
					break;
				}
				case static_cast<int>(SCORE::GOOD) :
				{
					Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
					isMiss = false;
					start_timer = true;
					change_state = true;
					break;
				}
				case static_cast<int>(SCORE::BAD) :
				{
					Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
					isMiss = false;
					start_timer = true;
					change_state = true;
					break;
				}
			}
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
		}

		if ((DownAttackKey.IsKeyDown() == true && DownAttackKey.IsKeyReapeated() == false && GetPosition().y < 0))
		{
			switch (static_cast<int>(Score_check()))
			{
				case static_cast<int>(SCORE::PERFECT) :
				{
					Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
					isMiss = false;
					start_timer = true;
					change_state = true;
					break;
				}
				case static_cast<int>(SCORE::GOOD) :
				{
					Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
					isMiss = false;
					start_timer = true;
					change_state = true;
					break;
				}
				case static_cast<int>(SCORE::BAD) :
				{
					Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
					isMiss = false;
					start_timer = true;
					change_state = true;
					break;
				}
			}
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
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


