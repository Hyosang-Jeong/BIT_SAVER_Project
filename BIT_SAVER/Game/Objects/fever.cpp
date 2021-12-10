/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: fever.cpp
Project: BIT_SAVER
Author:	Jaewoo Choi
-----------------------------------------------------------------*/
#include"fever.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity
#include"Background.h"
Fever_bar::Fever_bar(glm::vec2 startPos) :
	GameObject(startPos, glm::vec2{ 10,1 })
{
	fever_gazePtr = Engine::GetTextureManager().Load("../images/fever_gaze.png");
	fever_barPtr = Engine::GetTextureManager().Load("../images/fever_gaze_bar.png");
	score_ptr = Engine::GetGSComponent<Score>();
	initial_score = score_ptr->Getscore();
	is_fever_mode = false;
}

void Fever_bar::Update(double dt)
{
	if (is_fever_mode == false)
	{
		UpdatePosition({ static_cast<double>((score_ptr->Getscore() - initial_score)) * 0.005,0 });
	}
	if (GetPosition().x > 0)
	{
		is_fever_mode = true;
		SetPosition({ 0,GetPosition().y });
		Engine::GetGSComponent<Background>()->set_fever_mode(true);
		fever_gazePtr = Engine::GetTextureManager().Load("../images/fever_gaze2.png");
	}
	if (is_fever_mode == true)
	{
		UpdatePosition({ -0.05,0 });
	}
	if (GetPosition().x <-20)
	{
		is_fever_mode = false;
		Engine::GetGSComponent<Background>()->set_fever_mode(false);
		fever_gazePtr = Engine::GetTextureManager().Load("../images/fever_gaze.png");
	}

	initial_score = score_ptr->Getscore();
	GameObject::Update(dt);
}

void Fever_bar::Draw(glm::mat3 )
{
	fever_barPtr->Draw( { 0,-9 }, { 10,0.5 });
	fever_gazePtr->Draw( GetPosition(), { 10,0.5 });
}

