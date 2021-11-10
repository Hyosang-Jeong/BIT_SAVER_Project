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
	GameObject(startPos, glm::vec2{ -2,2 })
{
	AddGOComponent(new Sprite("../spt/boss.spt", this));
}

void Boss::Update(double dt)
{
	GameObject::Update(dt);
	UpdateXVelocity(dt);
	if (GetPosition().x < 8)
	{
		is_generating = false;
		SetVelocity({ 0,0 });
		SetPosition({ 8,0 });
	}
}

void Boss::Draw(glm::mat3 camera_matrix)
{
	GameObject::Draw(camera_matrix);

}

void Boss::GenerateBoss()
{
	is_generating = true;
}

void Boss::UpdateXVelocity(double dt)
{
	if (is_generating == true)
	{
		SetVelocity({ -dt * 50,0 });
	}


}


glm::vec2 Boss::Getposition()
{
	return GameObject::GetPosition();
}
