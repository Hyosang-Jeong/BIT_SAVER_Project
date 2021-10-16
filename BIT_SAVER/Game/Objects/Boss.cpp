/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: BIT_SAVER
Author: 
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"Boss.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity


Boss::Boss(glm::vec2 startPos) :
	moveLeftKey(InputKey::Keyboard::Left),
	moveRightKey(InputKey::Keyboard::Right),
	moveUpKey(InputKey::Keyboard::Up),
	moveDownKey(InputKey::Keyboard::Down),
	jumpKey(InputKey::Keyboard::Up),
	GameObject(startPos, glm::vec2{ -2,2 })
{
	texture.setup_texobj("../images/stickman.png");
	mdl_ref = Engine::GetGLModel().find("Basic_model");
	shd_ref = Engine::GetGLShader().find("Hero");
}

void Boss::Update(double dt)
{
	GameObject::Update(dt);
}

void Boss::Draw(glm::mat3 )
{
	texture.Draw(mdl_to_ndc_xform , "Basic_model", "Hero");
}


glm::vec2 Boss::Getposition()
{
	return GameObject::GetPosition();
}
