/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project:
Author:
Creation date: 3/14/2021
-----------------------------------------------------------------*/

#include "Background.h"
#include "../Engine/Engine.h"	//GetGameStateManage

Background::Background(glm::vec2 startPos, glm::vec2 velocity) :
	GameObject(startPos, glm::vec2{ 12,12 }), back_alive(true)
{
	texture.setup_texobj("../images/background.png");
	SetVelocity(velocity);
}

void Background::Update(double dt)
{
	GameObject::Update(dt);
	if (GetPosition().x < -10 && back_alive == true)
	{
		static Background* new_back = new Background({ 20, 0 }, { -5,0 });
		Engine::GetGSComponent<GameObjectManager>()->Add_front(new_back);

		back_alive = false;
	}
	if (GetPosition().x < -30)
	{
		set_destroy(true);
		back_alive = true;

	}
}

void Background::Draw(glm::mat3 camera_matrix)
{
	texture.Draw(mdl_to_ndc_xform * camera_matrix, "Basic_model", "Hero");
}

glm::vec2 Background::Getposition()
{
	return GameObject::GetPosition();
}
