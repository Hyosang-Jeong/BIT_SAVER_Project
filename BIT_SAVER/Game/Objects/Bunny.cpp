/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: BIT_SAVER
Author: 
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
	mdl_ref = Engine::GetGLModel().find("Basic_model");
	shd_ref = Engine::GetGLShader().find("Hero");

}


void Bunny::Update(double dt)
{
	GameObject::Update(dt);
}

void Bunny::Draw()
{
	texture.Draw(mdl_to_ndc_xform, "Basic_model", "Hero");
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
