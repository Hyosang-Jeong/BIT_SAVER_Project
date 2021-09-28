/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/20/2021
-----------------------------------------------------------------*/
#include "Laser.h"
#include"../Engine/Engine.h"

Laser::Laser(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 laserVelocity):GameObject(pos)
{
	AddGOComponent(new CS230::Sprite("assets/Laser.spt", this));
	SetRotation(rotation);
	SetScale(scale);
	SetVelocity(laserVelocity);
}


void Laser::Update(double dt)
{
	GameObject::Update(dt);
	if (GetPosition().x - (GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2) > Engine::GetWindow().GetSize().x)
	{
		set_destroyed(true);
	}
	else if (GetPosition().x + (GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2) < 0)
	{
		set_destroyed(true);
	}
	else if (GetPosition().y - (GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) > Engine::GetWindow().GetSize().y)
	{
		set_destroyed(true);
	}
	else if (GetPosition().y + (GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2) < 0)
	{
		set_destroyed(true);
	}
}

bool Laser::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Meteor || objectBType == GameObjectType::EnemyShip)
	{
		return true;
	}
	return false;
}

void Laser::ResolveCollision(GameObject* objectB)
{
	objectB->ResolveCollision(this);
	set_destroyed(true);
}
