/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"Bunny.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity


Bunny::Bunny(glm::vec2 startPos) :
	moveLeftKey(InputKey::Keyboard::Left),
	moveRightKey(InputKey::Keyboard::Right),
	moveUpKey(InputKey::Keyboard::Up),
	moveDownKey(InputKey::Keyboard::Down),
	jumpKey(InputKey::Keyboard::Up),
	GameObject(startPos, 0, { 0.1,0.1 })
{
	texture.setup_texobj("../images/stickman.png");
	mdl_ref = Engine::GetGLModel().find("Duck");
	shd_ref = Engine::GetGLShader().find("Duck");

}


void Bunny::Update(double dt)
{
	GameObject::Update(dt);
	//UpdateXVelocity(dt);
}

void Bunny::Draw()
{
	texture.Draw(mdl_to_ndc_xform, "Duck", "Duck");
}


glm::vec2 Bunny::Getposition()
{
	return GameObject::GetPosition();
}

void Bunny::UpdateXVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		UpdatePosition({ -dt, 0 });
		SetScale(glm::vec2{ 0.1, 0.1 });
	}

	else if (moveRightKey.IsKeyDown() == true)
	{
		UpdatePosition({ dt, 0 });
		SetScale(glm::vec2{ -0.1, 0.1 });
	}

	if (moveUpKey.IsKeyDown() == true)
	{
		UpdatePosition({ 0,dt });
	}

	else if (moveDownKey.IsKeyDown() == true)
	{
		UpdatePosition({ 0,-dt });
	}
}


//void Bunny::ChangeState(State* newState)
//{
//	Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
//	currState = newState;
//	currState->Enter(this);
//}
//
//void Bunny::State_Jumping::Enter([[maybe_unused]]GameObject* object)
//{
//
//}
//void Bunny::State_Jumping::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
//
//}
//void Bunny::State_Jumping::TestForExit([[maybe_unused]] GameObject* object) {
//
//}
//
//void Bunny::State_Idle::Enter([[maybe_unused]] GameObject* object)
//{
//	
//}
//
//void Bunny::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
//{
//
//}
//
//void Bunny::State_Idle::TestForExit([[maybe_unused]] GameObject* object)
//{
//
//}
//
//
//
//void Bunny::State_Running::Enter([[maybe_unused]] GameObject* object)
//{
//	
//	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
//}
//
//void Bunny::State_Running::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
//{
//	
//}
//
//
//void Bunny::State_Running::TestForExit([[maybe_unused]] GameObject* object)
//{
//
//}
//
//void Bunny::State_Skidding::Enter([[maybe_unused]] GameObject* object)
//{
//	//Bunny* hero = static_cast<Bunny*>(object);
//	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
//}
//
//void Bunny::State_Skidding::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
//{
//	//Bunny* hero = static_cast<Bunny*>(object);
//	//if (hero->GetVelocity().x < 0)
//	//{
//	//	hero->UpdateVelocity(glm::vec2{ (drag * 2 * dt) ,0 });
//	//}
//	//else if (hero->GetVelocity().x > 0)
//	//{
//	//	hero->UpdateVelocity(glm::vec2{ -(drag * 2 * dt) ,0 });
//	//}
//
//}
//
//void Bunny::State_Skidding::TestForExit([[maybe_unused]] GameObject* object)
//{
//	//Bunny* hero = static_cast<Bunny*>(object);
//	//if (hero->jumpKey.IsKeyDown() == true)
//	//{
//	//	hero->ChangeState(&hero->stateJumping);
//	//}
//	//else if (hero->moveLeftKey.IsKeyDown() == true)
//	//{
//	//	if (hero->GetVelocity().x <= 0)
//	//	{
//	//		hero->ChangeState(&hero->stateRunning);
//	//	}
//	//}
//	//else if (hero->moveRightKey.IsKeyDown() == true)
//	//{
//	//	if (hero->GetVelocity().x >= 0)
//	//	{
//	//		hero->ChangeState(&hero->stateRunning);
//	//	}
//	//}
//	//else if (hero->moveRightKey.IsKeyDown() == false && hero->moveLeftKey.IsKeyDown() == false)
//	//{
//	//	hero->ChangeState(&hero->stateRunning);
//	//}
//}
//
//void Bunny::State_Falling::Enter([[maybe_unused]] GameObject* object)
//{
//	//Bunny* hero = static_cast<Bunny*>(object);
//	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
//}
//
//
//void Bunny::State_Falling::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
//{
//	//Bunny* hero = static_cast<Bunny*>(object);
//	//hero->UpdateVelocity(math::vec2{ 0,-(Level1::gravity * dt) });
//	//hero->UpdateXVelocity(dt);
//}
//
//
//void Bunny::State_Falling::TestForExit([[maybe_unused]] GameObject* object)
//{
//	//Bunny* hero = static_cast<Bunny*>(object);
//	/*if (hero->GetPosition().y <= Level1::floor)
//	{
//		hero->SetVelocity(math::vec2{ hero->GetVelocity().x,0 });
//		hero->SetPosition(math::vec2{ hero->GetPosition().x,Level1::floor });
//		if (hero->GetVelocity().x > 0)
//		{
//			if (hero->moveLeftKey.IsKeyDown() == false)
//			{
//				hero->ChangeState(&hero->stateRunning);
//			}
//			else if (hero->moveLeftKey.IsKeyDown() == true)
//			{
//				hero->ChangeState(&hero->stateSkidding);
//			}
//		}
//		else if (hero->GetVelocity().x < 0)
//		{
//			if (hero->moveRightKey.IsKeyDown() == false)
//			{
//				hero->ChangeState(&hero->stateRunning);
//			}
//			else if (hero->moveRightKey.IsKeyDown() == true)
//			{
//				hero->ChangeState(&hero->stateSkidding);
//			}
//		}
//		else if (hero->GetVelocity().x == 0)
//		{
//			hero->ChangeState(&hero->stateIdle);
//		}
//	}*/
//}