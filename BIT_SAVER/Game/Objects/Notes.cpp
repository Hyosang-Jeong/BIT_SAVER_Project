/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Notes.cpp
Project: 
Author: 
Creation date: 3/14/2021
-----------------------------------------------------------------*/

#include"Notes.h"

Note::Note(glm::vec2 startPos,glm::vec2 velocity) :  
GameObject(startPos, glm::vec2{ 0.5,1 })
{
	texture.setup_texobj("../images/hit_star.png");
	SetVelocity(velocity);
}

void Note::Update(double dt)
{
	GameObject::Update(dt);
	if (GetPosition().x < -10)
	{
		set_destroy(true);
	}
}

void Note::Draw(glm::mat3 camera_matrix)
{
	texture.Draw(mdl_to_ndc_xform * camera_matrix , "Basic_model", "Hero");
}

glm::vec2 Note::Getposition()
{
	return GameObject::GetPosition();
}
