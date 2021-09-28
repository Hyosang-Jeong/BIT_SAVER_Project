/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/18/2021
-----------------------------------------------------------------*/
#include"Ship.h"
#include"..\Engine\Engine.h"  // get logger,get window
#include"Flame_Anims.h"  // flame animation
#include "ScreenWrap.h"  // ship screen wrap
#include"../Engine/ShowCollision.h"  // collision state
#include"../Engine/Collision.h" //collision
#include"Ship_Anims.h" //explode animation
#include"Laser.h" // laser
#include"..\Engine\GameObjectManager.h" // add laser
Ship::Ship(math::vec2 startPos): 
	GameObject(startPos, 0, math::vec2{  0.75,0.75  }),
	rotateCounterKey(CS230::InputKey::Keyboard::A), 
	rotateClockKey(CS230::InputKey::Keyboard::D), 
	accelerateKey(CS230::InputKey::Keyboard::W),
	shootingKey(CS230::InputKey::Keyboard::Space),
	is_accelerate( false ),
	left_flame("assets/flame.spt",this),
	right_flame("assets/flame.spt",this)
{
	AddGOComponent(new CS230::Sprite("assets/ship.spt",this));
	AddGOComponent(new ScreenWrap(*this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
}

void Ship::Update(double dt)
{
	if (isDead == false)
	{
		if (rotateCounterKey.IsKeyDown() == true)
		{
			UpdateRotation(rotation_speed * dt);
		}
		if (rotateClockKey.IsKeyDown() == true)
		{
			UpdateRotation(-(rotation_speed * dt));
		}
		if (accelerateKey.IsKeyDown() == true)
		{
			if (is_accelerate == false)
			{
				left_flame.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				right_flame.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			}
			is_accelerate = true;
			UpdateVelocity(math::RotateMatrix(GetRotation()) * math::vec2{ 0, accel * dt });
		}
		if (accelerateKey.IsKeyReleased() == true)
		{
			if (is_accelerate == true)
			{
				left_flame.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
				right_flame.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			}
			is_accelerate = false;
		}
		if (shootingKey.IsKeyReleased() == true)
		{		
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Laser(GetMatrix() * this->GetGOComponent<CS230::Sprite>()->GetHotSpot(3) , GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * Laser::LaserVelocity));
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Laser(GetMatrix() * this->GetGOComponent<CS230::Sprite>()->GetHotSpot(4) , GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * Laser::LaserVelocity));
		}
	}
	UpdateVelocity(math::vec2{ -(GetVelocity().x * Ship::drag * dt) ,-(GetVelocity().y * Ship::drag * dt) });
	UpdatePosition(math::vec2{ GetVelocity().x * dt,GetVelocity().y * dt });
	UpdateGOComponents(dt);
	left_flame.Update(dt);
	right_flame.Update(dt);
}
void Ship::Draw(math::TransformMatrix cameraMatrix)
{
	left_flame.Draw(cameraMatrix*GetMatrix()* math::TranslateMatrix(this->GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	right_flame.Draw(cameraMatrix* GetMatrix() * math::TranslateMatrix(this->GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	GetGOComponent<CS230::Sprite>()->Draw(cameraMatrix* GetMatrix());
	ShowCollision* showCollision = Engine::GetGSComponent<ShowCollision>();
	if (showCollision != nullptr)
	{
		if (showCollision->IsEnabled() == true)
		{
			CS230::Collision* collision = GetGOComponent<CS230::Collision>();
			if (collision != nullptr)
			{
				collision->Draw(cameraMatrix);
			}
		}
	}
}

void Ship::ResolveCollision([[maybe_unused]]CS230::GameObject* objectB)
{
	left_flame.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	right_flame.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	this->RemoveGOComponent<CS230::Collision>();
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
	isDead = true;
}

bool Ship::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Ship || objectBType  == GameObjectType::Particle )
	{
		return false;
	}
	return true;
}



