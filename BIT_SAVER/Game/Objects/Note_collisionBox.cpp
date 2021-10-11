/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"Note_collisionBox.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity

Note_box::Note_box(glm::vec2 startPos) : GameObject(startPos, 0, glm::vec2{ 1,10})
{
	texture.setup_texobj("../images/Note_collision_box.png");
	mdl_ref = Engine::GetGLModel().find("Basic_model");
	shd_ref = Engine::GetGLShader().find("Collision");
	collision_box.min.x = -5.5;
	collision_box.min.y = -10;
	collision_box.max.x = -2.5;
	collision_box.max.y = 10;
}


void Note_box::Update(double dt)
{
	GameObject::Update(dt);
}

void Note_box::Draw()
{
	texture.Draw(mdl_to_ndc_xform, "Basic_model", "Hero");

}


glm::vec2 Note_box::Getposition()
{
	return GameObject::GetPosition();
}

//void Hero::State_Jumping::Enter([[maybe_unused]] GameObject* object)
//{
//	//Hero* hero = static_cast<Hero*>(object);
//
//	//hero->SetVelocity(glm::vec2{ hero->GetVelocity().x, Hero::jumpVelocity });
//	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
//}
//void Hero::State_Jumping::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
//	//Hero* hero = static_cast<Hero*>(object);
//	//hero->UpdateVelocity(math::vec2{ 0,-(Level1::gravity * dt) });
//	//hero->UpdateXVelocity(dt);  //Change X Velocity stuff
//}
//void Hero::State_Jumping::TestForExit([[maybe_unused]] GameObject* object) {
//	//Hero* hero = static_cast<Hero*>(object);
//	//if (hero->jumpKey.IsKeyDown() == false) {  //Jump Key not pressed
//	//	hero->SetVelocity(glm::vec2{ hero->GetVelocity().x,0 });
//	//}
//	//if (hero->GetVelocity().y <= 0) {
//	//	hero->ChangeState(&hero->stateFalling);
//	//}
//}
//
//void Hero::State_Idle::Enter([[maybe_unused]] GameObject* object)
//{
//	//Hero* hero = static_cast<Hero*>(object);
//	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
//}
//
//void Hero::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
//{
//
//}
//
//void Hero::State_Idle::TestForExit([[maybe_unused]] GameObject* object)
//{
//	//Hero* hero = static_cast<Hero*>(object);
//	//if (hero->moveLeftKey.IsKeyDown() == true)
//	//{
//	//	hero->ChangeState(&hero->stateRunning);
//	//}
//	//else if (hero->moveRightKey.IsKeyDown() == true)
//	//{
//	//	hero->ChangeState(&hero->stateRunning);
//	//}
//	//else if (hero->jumpKey.IsKeyDown() == true)
//	//{
//	//	hero->ChangeState(&hero->stateJumping);
//	//}
//}
//
//
//
//void Hero::State_Running::Enter([[maybe_unused]] GameObject* object)
//{
//	//Hero* hero = static_cast<Hero*>(object);
//	//if (hero->moveLeftKey.IsKeyDown() == true)
//	//{
//	//	hero->SetScale(glm::vec2{ -0.1,0.1 });
//	//}
//	//else if (hero->moveRightKey.IsKeyDown() == true)
//	//{
//	//	hero->SetScale(glm::vec2{ 0.1,0.1 });
//	//}
//	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
//}
//
//void Hero::State_Running::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
//{
//	//Hero* hero = static_cast<Hero*>(object);
//	//hero->UpdateXVelocity(dt);
//}
//
//
//void Hero::State_Running::TestForExit([[maybe_unused]] GameObject* object)
//{
//	//Hero* hero = static_cast<Hero*>(object);
//	//if (hero->GetVelocity().x == 0)
//	//{
//	//	hero->ChangeState(&hero->stateIdle);
//	//}
//	//else if (hero->jumpKey.IsKeyDown() == true)
//	//{
//	//	hero->ChangeState(&hero->stateJumping);
//	//}
//	//else if (hero->GetVelocity().x > 0 && hero->moveLeftKey.IsKeyDown() == true)
//	//{
//	//	hero->ChangeState(&hero->stateSkidding);
//	//}
//
//	//else if (hero->GetVelocity().x < 0 && hero->moveRightKey.IsKeyDown() == true)
//	//{
//	//	hero->ChangeState(&hero->stateSkidding);
//	//}
//}
//
//void Hero::State_Skidding::Enter([[maybe_unused]] GameObject* object)
//{
//	//Hero* hero = static_cast<Hero*>(object);
//	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
//}
//
//void Hero::State_Skidding::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
//{
//	/*Hero* hero = static_cast<Hero*>(object);
//	if (hero->GetVelocity().x < 0)
//	{
//		hero->UpdateVelocity(glm::vec2{ (drag * 2 * dt) ,0 });
//	}
//	else if (hero->GetVelocity().x > 0)
//	{
//		hero->UpdateVelocity(glm::vec2{ -(drag * 2 * dt) ,0 });
//	}*/
//
//}
//
//void Hero::State_Skidding::TestForExit([[maybe_unused]] GameObject* object)
//{
//	/*Hero* hero = static_cast<Hero*>(object);
//	if (hero->jumpKey.IsKeyDown() == true)
//	{
//		hero->ChangeState(&hero->stateJumping);
//	}
//	else if (hero->moveLeftKey.IsKeyDown() == true)
//	{
//		if (hero->GetVelocity().x <= 0)
//		{
//			hero->ChangeState(&hero->stateRunning);
//		}
//	}
//	else if (hero->moveRightKey.IsKeyDown() == true)
//	{
//		if (hero->GetVelocity().x >= 0)
//		{
//			hero->ChangeState(&hero->stateRunning);
//		}
//	}
//	else if (hero->moveRightKey.IsKeyDown() == false && hero->moveLeftKey.IsKeyDown() == false)
//	{
//		hero->ChangeState(&hero->stateRunning);
//	}*/
//}
//
//void Hero::State_Falling::Enter([[maybe_unused]] GameObject* object)
//{
//	//Hero* hero = static_cast<Hero*>(object);
//	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
//}
//
//
//void Hero::State_Falling::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
//{
//	//Hero* hero = static_cast<Hero*>(object);
//	//hero->UpdateVelocity(math::vec2{ 0,-(Level1::gravity * dt) });
//	//hero->UpdateXVelocity(dt);
//}
//
//
//void Hero::State_Falling::TestForExit([[maybe_unused]] GameObject* object)
//{
//	//Hero* hero = static_cast<Hero*>(object);
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