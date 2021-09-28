/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 4/16/2021
-----------------------------------------------------------------*/

#include "Meteor.h"
#include"../Engine/Engine.h"
#include<stdlib.h>
#include "ScreenWrap.h"
#include"Meteor_Anims.h"
#include"..\Engine\GameObjectManager.h"
#include"Score.h"
#include"Laser.h"
#include"../Engine/Collision.h"
#include"GameParticles.h"

constexpr double PI = 3.1415926535;

Meteor::Meteor() :GameObject(math::vec2{ 0,0 }),health(100),size(1)
{
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt",this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
	AddGOComponent(new ScreenWrap(*this));
	SetPosition({ static_cast<double>(rand() % Engine::GetWindow().GetSize().x),static_cast<double>(rand() % Engine::GetWindow().GetSize().y) });
	SetRotation(((rand() % 1024) / 1024.0) * PI * 2.0);
	double meteor_scale = (((rand() % 1024) / 1024.0) / 4.0) + 0.75;
	SetScale({ meteor_scale, meteor_scale });
	SetVelocity(math::vec2{ static_cast<double>(rand()%201)-100 ,static_cast<double>(rand() % 201) - 100 });
}

Meteor::Meteor(Meteor& original) :GameObject(original.GetPosition()),size(original.size+1),health(100)
{
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
	double meteor_scale{ 0 };
	switch (size)
	{
		case 1: meteor_scale = (((rand() % 1024) / 1024.0) / 4.0) + 0.75;
			break;
		case 2: meteor_scale = (((rand() % 1024) / 1024.0) / 4.0) + 0.5;
			break;
		case 3: meteor_scale = (((rand() % 1024) / 1024.0) / 4.0) + 0.25;
			break;
	}
	SetRotation(original.GetRotation());
	SetScale({ meteor_scale, meteor_scale});
	SetVelocity(original.GetVelocity());
	AddGOComponent(new ScreenWrap(*this));

}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
	if (GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Meteor_Anim::Fade_Anim) && GetGOComponent<CS230::Sprite>()->IsAnimationDone()==true)
	{
		set_destroyed(true);
	}
}

void Meteor::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Laser)
	{
		health -= 10;
		//|vectorToObject| * Radius = Collision Point
		//ObjectB Pos - Meteor Pos = vectorToObject
		math::vec2 vectorToobject = (objectB->GetPosition() - GetPosition()).Normalize();
		math::vec2 collision_point = vectorToobject * GetGOComponent<CS230::CircleCollision>()->GetRadius();
		math::vec2 object_velocity = objectB->GetVelocity().Normalize();


		Engine::GetGSComponent<HitEmitter>()->Emit(1, collision_point + GetPosition(),GetVelocity(), { 0,0 }, 0);
		Engine::GetGSComponent<MeteorBitEmitter>()->Emit(10, collision_point + GetPosition(), GetVelocity(), (vectorToobject *2 + object_velocity)*50, PI / 2.0);
	}
	if (health == 0 && size < 3)
	{
		Meteor* tmp1 = new Meteor(*this);
		Meteor* tmp2 = new Meteor(*this);

		tmp1->SetVelocity(math::RotateMatrix(PI / 6) * GetVelocity());
		tmp2->SetVelocity(math::RotateMatrix(-PI / 6) * GetVelocity());

		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(tmp1);
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(tmp2);
		this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
		this->RemoveGOComponent<CS230::Collision>();
		Engine::GetGSComponent<Score>()->AddScore(100*size);
	}
	if (health == 0 && size == 3)
	{
		this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
		this->RemoveGOComponent<CS230::Collision>();
		Engine::GetGSComponent<Score>()->AddScore(100 * size);
	}
	else
	{
		UpdateVelocity(0.01 * objectB->GetVelocity());
	}

}

