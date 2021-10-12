/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: BIT_SAVER
Author: 
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"Note_collisionBox.h"
#include"../Engine/Engine.h" //get window
#include"..\Levels\Level1.h"  // Level1's gravity

Note_box::Note_box(glm::vec2 startPos) : GameObject(startPos, 0, glm::vec2{ 1,10})
{
	texture.setup_texobj("../images/Note_collision_box.png");
}


void Note_box::Update(double dt)
{
	GameObject::Update(dt);
}

void Note_box::Draw()
{
	texture.Draw(mdl_to_ndc_xform, "Basic_model", "Hero");
}


glm::vec2 Note_box::Getposition()
{
	return GameObject::GetPosition();
}

