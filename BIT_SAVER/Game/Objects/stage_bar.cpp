/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: BIT_SAVER
Author:
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"stage_bar.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity

constexpr double WINDOW_WIDTH = 20;

Stage_bar::Stage_bar(glm::vec2 startPos, double total_time, double extra_time) :
total_time(total_time),extra_stage_time(extra_time),
	GameObject(startPos, glm::vec2{ 1,1 })
{
	AddGOComponent(new Sprite("../spt/hero.spt", this));
	stage_barPtr = Engine::GetTextureManager().Load("../images/stage_bar.png");
	GetGOComponent<Sprite>()->PlayAnimation(0);
	currstate = 0;
	Doupdate = true;
}

void Stage_bar::Update(double dt)
{
	if (Doupdate == true)
	{
		GameObject::Update(dt);
		UpdatePosition({ (WINDOW_WIDTH / 2.0 / extra_stage_time) * dt,0 });
		if (GetPosition().x > 0 && currstate == 0)
		{
			currstate = 1;
		}
	}
}

void Stage_bar::Draw(glm::mat3 camera_matrix)
{
	stage_barPtr->Draw({ 0,9 }, {10,1});
	GameObject::Draw(camera_matrix);
}

int Stage_bar::Getchangeflag() // 0 for extra,  1 for boss but still extra stage,  2 for boss
{
	if (currstate == 1)
	{
		currstate = 2;
		return 1;
	}
	return 0;
}

void Stage_bar::SetUpdate(bool update)
{
	Doupdate = update;
}
