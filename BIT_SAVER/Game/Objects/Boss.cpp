/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Boss.cpp
Project: BIT_SAVER
Author: Hyun Kang
-----------------------------------------------------------------*/
#include"Boss.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity


Boss::Boss(glm::vec2 startPos) :
	GameObject(startPos, glm::vec2{ 4,4 })
{
	AddGOComponent(new Sprite("../spt/boss.spt", this));
	GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(boss_anim::spawn));
}

void Boss::Update(double dt)
{
	GameObject::Update(dt);
	UpdateXVelocity(dt);
	if (GetPosition().x < 10)
	{
		is_generating = false;
		SetVelocity({ 0,0 });
		SetPosition({ 10,-5 });
	}
}

void Boss::Draw(glm::mat3 camera_matrix)
{
	GameObject::Draw(camera_matrix);

}

void Boss::GenerateBoss()
{
	is_generating = true;
	SetVelocity({ -1,0 });
}

void Boss::UpdateXVelocity(double )
{
	if (is_generating == true)
	{
		SetVelocity({-1,0 });
	}
}


glm::vec2 Boss::Getposition()
{
	return GameObject::GetPosition();
}
