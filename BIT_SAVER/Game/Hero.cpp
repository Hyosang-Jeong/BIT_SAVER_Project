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
#include"Level1.h"  // Level1's gravity
//#include  "..\Engine\Camera.h" // using Camera
//#include"Hero_Anims.h" //use enum value

Hero::Hero(glm::vec2 startPos) :
	moveLeftKey(InputKey::Keyboard::Left),
	moveRightKey(InputKey::Keyboard::Right),
	jumpKey(InputKey::Keyboard::Up),
	GameObject(startPos)
{
	//sprite.Load("assets/hero.spt");
	mdl_ref = Engine::GetGLModel().find("Duck");
	shd_ref = Engine::GetGLShader().find("Duck");
	//currState = &stateIdle;
	//currState->Enter(this);
}


void Hero::Update(double dt)
{
	GameObject::Update(dt);
	shd_ref->second.Use();
	//if (Getposition().x - sprite.GetFrameSize().x / 2 <= 0)
	//{
	//	SetPosition(math::vec2{ sprite.GetFrameSize().x / 2.0 ,GetPosition().y });
	//	SetVelocity(math::vec2{ 0,GetVelocity().y });
	//}
	//if (Getposition().x + sprite.GetFrameSize().x / 2 >= Engine::GetWindow().GetSize().x + camera.GetPosition().x)
	//{
	//	SetPosition(math::vec2{ Engine::GetWindow().GetSize().x + camera.GetPosition().x - sprite.GetFrameSize().x / 2 ,GetPosition().y });

	//	SetVelocity(math::vec2{ 0,GetVelocity().y });
	//}
}

void Hero::Draw()
{
	glBindVertexArray(mdl_ref->second.vaoid );

	GLint uniform_var_loc1 = glGetUniformLocation(shd_ref->second.GetHandle(), "color_frag");
	texture.setup_texobj("../images/chick.png");
	GLuint  texobj_hdl0 = texture.Get_texture();
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, texobj_hdl0);
	glBindTextureUnit(0, texobj_hdl0);
	
	GLuint tex_loc = glGetUniformLocation(shd_ref->second.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 0);

	glDrawElements(mdl_ref->second.primitive_type, mdl_ref->second.draw_cnt, GL_UNSIGNED_SHORT, NULL);

	glBindVertexArray(0);

	shd_ref->second.UnUse();
}


glm::vec2 Hero::Getposition()
{
	return GameObject::GetPosition();
}

void Hero::UpdateXVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		UpdateVelocity(glm::vec2{ -(acceleration * dt),0 });
		if (GetVelocity().x < -max_velocity)
		{
			SetVelocity(glm::vec2{ -max_velocity,GetVelocity().y });
		}
	}
	else if (moveRightKey.IsKeyDown() == true)
	{
		UpdateVelocity(glm::vec2{ (acceleration * dt),0 });

		if (GetVelocity().x > max_velocity)
		{
			SetVelocity(glm::vec2{ max_velocity,GetVelocity().y });
		}
	}

	else if (moveLeftKey.IsKeyDown() == false && moveRightKey.IsKeyDown() == false)
	{
		if (GetVelocity().x < 0)
		{
			UpdateVelocity(glm::vec2{ (drag * dt),0 });
			if (GetVelocity().x > 0)
			{
				SetVelocity(glm::vec2{ 0,GetVelocity().y });
			}
		}
		else if (GetVelocity().x > 0)
		{
			UpdateVelocity(glm::vec2{ -(drag * dt),0 });
			if (GetVelocity().x < 0)
			{
				SetVelocity(glm::vec2{ 0,GetVelocity().y });
			}
		}
	}
}


void Hero::ChangeState(State* newState) {
	Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}

void Hero::State_Jumping::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);

	hero->SetVelocity(glm::vec2{ hero->GetVelocity().x, Hero::jumpVelocity });
	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
}
void Hero::State_Jumping::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	//hero->UpdateVelocity(math::vec2{ 0,-(Level1::gravity * dt) });
	hero->UpdateXVelocity(dt);  //Change X Velocity stuff
}
void Hero::State_Jumping::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == false) {  //Jump Key not pressed
		hero->SetVelocity(glm::vec2{ hero->GetVelocity().x,0 });
	}
	if (hero->GetVelocity().y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Idle::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
}

void Hero::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{

}

void Hero::State_Idle::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	else if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}



void Hero::State_Running::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->SetScale(glm::vec2{ -1.0,1.0 });
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->SetScale(glm::vec2{ 1.0,1.0 });
	}
	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
}

void Hero::State_Running::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}


void Hero::State_Running::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetVelocity().x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	else if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->GetVelocity().x > 0 && hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateSkidding);
	}

	else if (hero->GetVelocity().x < 0 && hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
}

void Hero::State_Skidding::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}

void Hero::State_Skidding::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetVelocity().x < 0)
	{
		hero->UpdateVelocity(glm::vec2{ (drag * 2 * dt) ,0 });
	}
	else if (hero->GetVelocity().x > 0)
	{
		hero->UpdateVelocity(glm::vec2{ -(drag * 2 * dt) ,0 });
	}

}

void Hero::State_Skidding::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x <= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x >= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == false && hero->moveLeftKey.IsKeyDown() == false)
	{
		hero->ChangeState(&hero->stateRunning);
	}
}

void Hero::State_Falling::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	//hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}


void Hero::State_Falling::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	//hero->UpdateVelocity(math::vec2{ 0,-(Level1::gravity * dt) });
	hero->UpdateXVelocity(dt);
}


void Hero::State_Falling::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	/*if (hero->GetPosition().y <= Level1::floor)
	{
		hero->SetVelocity(math::vec2{ hero->GetVelocity().x,0 });
		hero->SetPosition(math::vec2{ hero->GetPosition().x,Level1::floor });
		if (hero->GetVelocity().x > 0)
		{
			if (hero->moveLeftKey.IsKeyDown() == false)
			{
				hero->ChangeState(&hero->stateRunning);
			}
			else if (hero->moveLeftKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
		}
		else if (hero->GetVelocity().x < 0)
		{
			if (hero->moveRightKey.IsKeyDown() == false)
			{
				hero->ChangeState(&hero->stateRunning);
			}
			else if (hero->moveRightKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
		}
		else if (hero->GetVelocity().x == 0)
		{
			hero->ChangeState(&hero->stateIdle);
		}
	}*/
}