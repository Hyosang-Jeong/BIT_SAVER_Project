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
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr

Hero::Hero(glm::vec2 startPos) :
	moveLeftKey(InputKey::Keyboard::Left),
	moveRightKey(InputKey::Keyboard::Right),
	moveUpKey(InputKey::Keyboard::Up),
	moveDownKey(InputKey::Keyboard::Down),
	jumpKey(InputKey::Keyboard::Up),
	GameObject(startPos, 0, glm::vec2{ 0.1,0.1 })
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
	UpdateXVelocity( dt);

}

void Hero::Draw()
{
	glBindVertexArray(mdl_ref->second.vaoid );

	GLint uniform_var_loc1 = glGetUniformLocation(shd_ref->second.GetHandle(), "color_frag");
	texture.setup_texobj("../images/chick.png");

	GLuint  texobj_hdl0 = texture.Get_texture();

	glTextureParameteri(texobj_hdl0, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // size
	glTextureParameteri(texobj_hdl0, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texobj_hdl0);
	glBindTextureUnit(0, texobj_hdl0);
	
	GLuint tex_loc = glGetUniformLocation(shd_ref->second.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 0);

	GLint uniform_var_loc1 = glGetUniformLocation(shd_ref->second.GetHandle(), "uModelToNDC");
	if (uniform_var_loc1 >= 0)
	{
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(mdl_to_ndc_xform));
	}
	else
	{
		Engine::GetLogger().LogError("Uniform variable doesn't exist!!!");
	}

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
		UpdatePosition({  -dt, 0});
		SetScale(glm::vec2{ 0.1, 0.1 });
	}

	else if (moveRightKey.IsKeyDown() == true)
	{
		UpdatePosition({ dt, 0 });
		SetScale(glm::vec2{ -0.1, 0.1 });
	}

	if (moveUpKey.IsKeyDown() == true)
	{
		UpdatePosition({ 0,dt});
	}

	else if (moveDownKey.IsKeyDown() == true)
	{
		UpdatePosition({ 0,-dt });
	}
}


void Hero::ChangeState(State* newState) 
{
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
		hero->SetScale(glm::vec2{ -0.1,0.1 });
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->SetScale(glm::vec2{ 0.1,0.1 });
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