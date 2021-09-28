/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyShip.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/25/2021
-----------------------------------------------------------------*/
#include"EnemyShip.h"
#include"GameObjectTypes.h"
#include"../Engine/Engine.h"
#include"../Engine/Collision.h"
#include"Score.h"
#include"../Engine/ShowCollision.h"
#include"Flame_Anims.h"
#include"Ship_Anims.h"

EnemyShip::EnemyShip(GameObject* player) :GameObject(), isDead(false),player(player),
flameLeft("assets/flame.spt", this),
flameRight("assets/flame.spt", this)
{
	AddGOComponent(new CS230::Sprite("assets/Enemyship.spt", this));
	constexpr double PI = 3.1415926535;
	double rotate_amount = ((rand() % 1024) / 1024.0) * PI * 2.0;
	SetRotation(rotate_amount);
	double random_pos = -((rand() % 1024 / 1024.0) * 1024 + 1024);  
	SetPosition(player->GetPosition() + math::RotateMatrix(rotate_amount) * math::vec2{0,random_pos });
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
	
}

void EnemyShip::Update(double dt)
{ 
	flameLeft.Update(dt);
	flameRight.Update(dt);
	
	math::vec2 enemyvector = math::RotateMatrix(GetRotation()) * math::vec2{ 0,1};
	math::vec2 playervector = player->GetPosition() - GetPosition();
	double cross_value = enemyvector.Normalize().Cross(playervector.Normalize());
	
	if (cross_value < -0.05)
	{
		UpdateRotation(-rotationRate * dt);
	}
	else if (cross_value > 0.05)
	{
		UpdateRotation(rotationRate * dt);
	}
	UpdateVelocity(math::RotateMatrix(GetRotation()) * math::vec2{ 0, accel * dt });
	UpdateVelocity(math::vec2{ -(GetVelocity().x * drag * dt) ,-(GetVelocity().y * drag * dt) });
	UpdatePosition(math::vec2{ GetVelocity().x * dt,GetVelocity().y * dt });
	UpdateGOComponents(dt);

}


void EnemyShip::Draw(math::TransformMatrix displayMatrix)
{
	GetGOComponent<CS230::Sprite>()->Draw(displayMatrix * GetMatrix());
	flameLeft.Draw(displayMatrix * GetMatrix() * math::TranslateMatrix(this->GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	flameRight.Draw(displayMatrix * GetMatrix() * math::TranslateMatrix(this->GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	ShowCollision* showCollision = Engine::GetGSComponent<ShowCollision>();
	if (showCollision != nullptr)
	{
		if (showCollision->IsEnabled() == true)
		{
			CS230::Collision* collision = GetGOComponent<CS230::Collision>();
			if (collision != nullptr)
			{
				collision->Draw(displayMatrix);
			}
		}
	}
}

GameObjectType EnemyShip::GetObjectType()
{
	return GameObjectType::EnemyShip;
}

std::string EnemyShip::GetObjectTypeName()
{
	return "EnemyShip";
}

bool EnemyShip::CanCollideWith(GameObjectType collideAgainstType)
{
	if (collideAgainstType == GameObjectType::Ship || collideAgainstType == GameObjectType::Laser)
	{
		return true;
	}
	return false;
}

void EnemyShip::ResolveCollision(GameObject* collidedWith)
{
	if (collidedWith->GetObjectType() == GameObjectType::Laser)
	{
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		this->RemoveGOComponent<CS230::Collision>();
		Engine::GetGSComponent<Score>()->AddScore(300);
		GetGOComponent<CS230::Sprite>()->PlayAnimation(1);
		collidedWith->set_destroyed(true);
	}
}
