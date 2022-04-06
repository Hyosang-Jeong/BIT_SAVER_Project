/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: stage_bar.cpp
Project: BIT_SAVER
Author:	Jaewoo Choi
-----------------------------------------------------------------*/
#include"stage_bar.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity


Stage_bar::Stage_bar(glm::vec2 startPos, double total_time, double extra_time) :
	music_total_time(total_time),extra_stage_time(extra_time),
	GameObject(startPos, glm::vec2{ 1,1 })
{
	AddGOComponent(new Sprite("../spt/hero.spt", this));
	//stage_barPtr = Engine::GetTextureManager().Load("../images/stage_bar.png");
	extra_stage_barPtr = Engine::GetTextureManager().Load("../images/extra_stage_bar.png");
	boss_stage_barPtr = Engine::GetTextureManager().Load("../images/boss_stage_bar.png");
	GetGOComponent<Sprite>()->PlayAnimation(0);
	currstate = 0;
	boss_stage_time = (music_total_time - extra_stage_time) * BOSS_PITCH;
	actual_total_time = extra_stage_time + boss_stage_time;

	extra_stage_size = WINDOW_WIDTH * (extra_stage_time / actual_total_time);

	extra_stage_pos_range = { -10,extra_stage_size - 10 };
	boss_stage_pos_range = { extra_stage_pos_range.y , 10 };

	stage_pos = { (extra_stage_pos_range.x + extra_stage_pos_range.y) * 0.5, (boss_stage_pos_range.x + boss_stage_pos_range.y) * 0.5 };
	stage_scale = { extra_stage_pos_range.y - stage_pos.x ,  boss_stage_pos_range.y - stage_pos.y };

	Doupdate = true;
}

void Stage_bar::Update(double dt)
{
	if (Doupdate == true)
	{
		GameObject::Update(dt);
		UpdatePosition({ (WINDOW_WIDTH / actual_total_time) * dt,0 });
		if (GetPosition().x > extra_stage_pos_range.y && currstate == 0)
		{
			currstate = 1;
		}
	}
}

void Stage_bar::Draw(glm::mat3 camera_matrix)
{
	extra_stage_barPtr->Draw({ stage_pos.x,9 }, { stage_scale.x,0.5 });
	boss_stage_barPtr->Draw({ stage_pos.y,9 }, { stage_scale.y,0.5 });
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
