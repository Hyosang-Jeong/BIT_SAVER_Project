/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Notes.cpp
Project:
Author:
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"../../Engine/Engine.h"
#include"Notes.h"
#include"../../Engine/Sprite/GameParticles.h"
#include "EnergyBar.h"
#include "../../Engine/Music/music.h"
#include "../../Engine/Engine.h"
#include "../../Game/Levels/State.h"
#include "../../Engine/Window/Window.h"
#include"Score.h"
#include"../../Engine/Physics/Camera.h"

Note::Note(glm::vec2 startPos, glm::vec2 velocity) :
	UpAttackKey1(InputKey::Keyboard::F),
	UpAttackKey2(InputKey::Keyboard::Up),
	DownAttackKey1(InputKey::Keyboard::J),
	DownAttackKey2(InputKey::Keyboard::Down),
    isMiss(false),

    energy(static_cast<EnergyBar*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Energy_bar))),
GameObject(startPos, glm::vec2{ 0.5,1 })

{
	AddGOComponent(new Sprite("../images/hit_star.png", this));
	SetVelocity(velocity);

}

void Note::Update(double dt)
{
	GameObject::Update(dt);
	if (GetPosition().x < -10)
	{
		set_destroy(true);
	}
	Hit_Check();
	
	if (isMiss == true)
	{
	    if (energy->GetScale().x > 0)
	    {
		energy->SetScale(glm::vec2{ energy->GetScale().x - (dt / 10),energy->GetScale().y });
		energy->UpdatePosition(glm::vec2{ -(dt / 10),0 });
	    }
	    else
	    {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Gameover));
	    }
	}	
}

void Note::Draw(glm::mat3 camera_matrix)
{
	GameObject::Draw(camera_matrix);
}

glm::vec2 Note::Getposition()
{
	return GameObject::GetPosition();
}

void Note::Hit_Check()
{
    //set_destroy(true);

	if (Score_check()== static_cast<int>(SCORE::PERFECT) && GetPosition().y > 0)
	{
		if (UpAttackKey1.IsKeyDown() == true || UpAttackKey2.IsKeyDown() == true && isRepeated==false)
		{
			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			set_destroy(true);
		}
	}
	else if (Score_check() == static_cast<int>(SCORE::GOOD) && GetPosition().y > 0)
	{
		if (UpAttackKey1.IsKeyDown() == true || UpAttackKey2.IsKeyDown() == true && isRepeated == false)
		{
			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			set_destroy(true);
		}
	}
	else if (Score_check() == static_cast<int>(SCORE::BAD) && GetPosition().y > 0)
	{
		if (UpAttackKey1.IsKeyDown() == true || UpAttackKey2.IsKeyDown() == true && isRepeated == false)
		{
			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			set_destroy(true);
		}
	}

	if (Score_check() == static_cast<int>(SCORE::PERFECT) && GetPosition().y < 0)
	{
		if (DownAttackKey1.IsKeyDown() == true || DownAttackKey2.IsKeyDown() == true && isRepeated == false)
		{
			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			set_destroy(true);
		}
	}

	else if (Score_check() == static_cast<int>(SCORE::GOOD) && GetPosition().y < 0)
	{
		if (DownAttackKey1.IsKeyDown() == true || DownAttackKey2.IsKeyDown() == true && isRepeated == false)
		{
			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			set_destroy(true);
		}
	}
	else if (Score_check() == static_cast<int>(SCORE::BAD)	&& GetPosition().y < 0)
	{
		if (DownAttackKey1.IsKeyDown() == true || DownAttackKey2.IsKeyDown() == true && isRepeated == false)
		{
			Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			set_destroy(true);
		}
	}

	if (Score_check() == static_cast<int>(SCORE::MISS) && isMiss == false && Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x > 1)
	{
		isMiss = true;
		Engine::GetGSComponent<MissEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
		Engine::GetGSComponent<Score>()->AddScore(Score_check());
	}
}

int Note::Score_check()
{
    if (GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x <= 0.4
	&& Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x <= 0.4)
    {
	return static_cast<int>(SCORE::PERFECT);
    }
    else if (GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x <= 0.7 &&
	GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x > 0.4 ||
	Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x <= 0.7 &&
	Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x > 0.4)
    {
	return static_cast<int>(SCORE::GOOD);
    }
    else if (GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x < 1 &&
	GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x > 0.7 ||
	Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x < 1 &&
	Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x > 0.7)
    {
	return static_cast<int>(SCORE::BAD);
    }
    return static_cast<int>(SCORE::MISS);


}


