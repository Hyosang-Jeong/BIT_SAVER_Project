/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Note_collisionBox.cpp
Project: BIT_SAVER
Author:	Hyun Kang
-----------------------------------------------------------------*/
#include"Note_collisionBox.h"
#include"../../Engine/Engine.h"

Note_box::Note_box(glm::vec2 startPos) :
GameObject(startPos, glm::vec2{ 1,20 })
{
	//AddGOComponent(new Sprite("../images/hit_circle.png", this));
	UP = Engine::GetTextureManager().Load("../images/hit_circle.png");
	Down = Engine::GetTextureManager().Load("../images/hit_circle.png");
}

void Note_box::Update(double dt)
{
	GameObject::Update(dt);
	scale += static_cast<float>(dt)*30.f;

}

void Note_box::ResolveCollision(GameObject* )
{

}

const bool Note_box::GetDestroyed() const
{
	return is_destroyed;
}


void Note_box::Draw(glm::mat3 )
{
	//GameObject::Draw(camera_matrix);
	UP->Draw({ -4,3 }, { 1.5,1.5 }, { scale,0 });
	Down->Draw({ -4,-7 }, { 1.5,1.5 }, { scale,0 });
}

glm::vec2 Note_box::Getposition()
{
	return GameObject::GetPosition();
}

void Note_box::set_attack_flag(bool value,GLfloat ypos)
{
	if (value == false)
	{
		is_repeated = false;
	}
		attack_pressed = value;
		attack_ypos = ypos;
}

