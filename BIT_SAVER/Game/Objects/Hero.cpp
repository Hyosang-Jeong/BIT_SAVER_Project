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
	jumpKey(InputKey::Keyboard::Up),
	GameObject(startPos, 0, glm::vec2{ 2,2 })
{
	texture.setup_texobj("../images/stickman.png");
	
	//sprite.Load("assets/hero.spt");
	//currState = &stateIdle;
	//currState->Enter(this);
}


void Hero::Update(double dt)
{
	GameObject::Update(dt);

	UpdateXVelocity( dt);
	if (Getposition().y > 0.5)
	{
		SetVelocity({ 0, 0 });
		SetPosition({ Getposition().x,0.5 });
	}
	if (Getposition().y < -0.3)
	{
		SetVelocity({ 0, 0 });
		SetPosition({ Getposition().x,-0.29 });
	}

}

void Hero::Draw()
{
	texture.Draw(mdl_to_ndc_xform,"Duck","Duck");

	/*mdl_ref = Engine::GetGLModel().find("Duck");
	shd_ref = Engine::GetGLShader().find("Collision");

	shd_ref->second.Use();
	 
	glBindVertexArray(mdl_ref->second.vaoid);

	GLint uniform_var_loc1 = glGetUniformLocation(shd_ref->second.GetHandle(), "uModelToNDC");
	if (uniform_var_loc1 >= 0)
	{
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, &mdl_to_ndc_xform[0].x);
	}
	else
	{
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}

	glDrawElements(mdl_ref->second.primitive_type, mdl_ref->second.draw_cnt, GL_UNSIGNED_SHORT, NULL);
	shd_ref->second.UnUse();*/

}


glm::vec2 Hero::Getposition()
{
	return GameObject::GetPosition();
}

void Hero::UpdateXVelocity([[maybe_unused]]double dt)
{

	//if (moveLeftKey.IsKeyDown() == true && move_release_frag[0] == false)
	//{
	//	//UpdateVelocity({ -5,0 });
	//	//UpdatePosition({ -0.5, 0 });
	//	move_release_frag[0] = true;
	//	SetScale(glm::vec2{ 0.1, 0.1 });
	//}

	// if (moveRightKey.IsKeyDown() == true && move_release_frag[1] == false)
	//{
	//	UpdatePosition({ 0.5, 0 });
	//	move_release_frag[1] = true;
	//	SetScale(glm::vec2{ -0.1, 0.1 });
	//}

	if (moveUpKey.IsKeyDown() == true && move_release_frag[2] == false)
	{
		UpdateVelocity({ 0,10 });
		move_release_frag[2] = true;
	}

	 if (moveDownKey.IsKeyDown() == true && move_release_frag[3] == false)
	{
		 UpdateVelocity({ 0,-10 });
		move_release_frag[3] = true;
	}


	 if (moveLeftKey.IsKeyReleased() == true)
	 {
		 move_release_frag[0] = false;
	 }

	 if (moveRightKey.IsKeyReleased() == true)
	 {
		 move_release_frag[1] = false;
	 }

	 if (moveUpKey.IsKeyReleased() == true)
	 {
		 move_release_frag[2] = false;
	 }

	 if (moveDownKey.IsKeyReleased() == true)
	 {
		 move_release_frag[3] = false;
	 }

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