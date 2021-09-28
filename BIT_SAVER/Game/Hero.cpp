/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"Hero.h"
#include"Gravity.h"  //gamestate gravity
#include"../Engine/Engine.h" //get window
#include"Level1.h"  // Level1's floor
#include"Hero_Anims.h" //use enum value
#include "../Engine/Animation.h" //animation
#include"../Engine/Collision.h"
#include"Score.h"
#include"..\Engine\GameObjectManager.h"
#include"GameParticles.h"

Hero::Hero(math::vec2 startPos) :
	moveLeftKey(CS230::InputKey::Keyboard::Left),
	moveRightKey(CS230::InputKey::Keyboard::Right),
	jumpKey(CS230::InputKey::Keyboard::Up),
	GameObject(startPos),isDead(false),standingOnObject(nullptr),hurtTimer(0),drawHero(true)
{
	AddGOComponent(new CS230::Sprite("assets/hero.spt", this));
	currState = &stateIdle;
	currState->Enter(this);
	for (CS230::GameObject* object : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
	{
		if (object->GetObjectType() == GameObjectType::Floor)
		{
			if (object->DoesCollideWith(GetPosition()) == true)
			{
				SetPosition({ GetPosition().x, object->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().point2.y });
				standingOnObject = object;
			}
		}
	}

}


void Hero::Update(double dt)
{
	GameObject::Update(dt);
	if (hurtTimer != 0)
	{
		hurtTimer -= dt;
		drawHero = !drawHero;
	}
	if (hurtTimer <= 0)
	{
		drawHero = true;
	}
	if (Getposition().x - GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().point1.x / 2 <= 0)
	{
		SetPosition(math::vec2{ GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().point1.x / 2.0 ,GetPosition().y });
		SetVelocity(math::vec2{ 0,GetVelocity().y });
	}
	if (GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().point2.x >= Engine::GetWindow().GetSize().x + Engine::GetGSComponent<CS230::Camera>()->GetPosition().x)
	{
		SetPosition(math::vec2{ GetPosition().x ,GetPosition().y });
		SetVelocity(math::vec2{ 0,GetVelocity().y });
	}
	
}

math::vec2 Hero::Getposition()
{
	return GameObject::GetPosition();
}

void Hero::Draw(math::TransformMatrix displayMatrix)
{
	if (drawHero == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

void Hero::ResolveCollision(GameObject* objectB)
{
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 heroRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType())
	{
	case GameObjectType::Floor:
	{
		[[fallthrough]];
	}
	case GameObjectType::TreeStump:
	{
		hurtTimer = 0;
		if (objectB->DoesCollideWith(GetPosition()) == true && currState == &stateFalling && heroRect.Top()>collideRect.Top())
		{
			SetPosition({ GetPosition().x, collideRect.Top() });
			if (GetVelocity().y < -(jumpVelocity))
			{
				Engine::GetGSComponent<SmokeEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			}
			standingOnObject = objectB;		
			currState->TestForExit(this);
		}
		else if (this->Getposition().x <= objectB->GetPosition().x)
		{
			SetPosition({ Getposition().x - (heroRect.Right() - collideRect.Left()), Getposition().y });
			SetVelocity({ 0,GetVelocity().y });
		}
		else
		{
			SetPosition({ Getposition().x + (collideRect.Right()-heroRect.Left()), Getposition().y });
			SetVelocity({ 0,GetVelocity().y });
		}
		break;
	}
	case GameObjectType::Bunny:
	{
		if (currState == &stateFalling)
		{
			SetVelocity({ GetVelocity().x  ,jumpVelocity/2.0 });
			objectB->ResolveCollision(this);
			Engine::GetGSComponent<SmokeEmitter>()->Emit(1, { GetPosition().x, collideRect.Top() - (collideRect.Top() - heroRect.Bottom()) / 2.0 }, { 0,0 }, { 0,0 }, 0);
		}

		else if (this->Getposition().x <= objectB->GetPosition().x)
		{
			if (currState == &stateSkidding)
			{
				objectB->ResolveCollision(this);
				Engine::GetGSComponent<SmokeEmitter>()->Emit(1, { heroRect.Right() - (heroRect.Right() - collideRect.Left()) / 2.0, Getposition().y }, GetVelocity(), { 0,0 },0);

			}
			else
			{
				hurtTimer = hurtTime;
				SetPosition({ Getposition().x - (heroRect.Right() - collideRect.Left()), Getposition().y });
				SetVelocity({ -acceleration   , jumpVelocity / 2.0  });
				ChangeState(&stateJumping);
			}
		}
		else
		{
			if (currState == &stateSkidding)
			{
				objectB->ResolveCollision(this);
				Engine::GetGSComponent<SmokeEmitter>()->Emit(1, { collideRect.Right() - (collideRect.Right() - heroRect.Left())/2.0, Getposition().y }, GetVelocity(), { 0,0 }, 3.1415926535);
			}
			else
			{
				hurtTimer = hurtTime;
				SetPosition({ Getposition().x + (collideRect.Right() - heroRect.Left()), Getposition().y });
				SetVelocity({ acceleration  ,jumpVelocity / 2.0});
				ChangeState(&stateJumping);
			}
		}		
	}
	break;
	case GameObjectType::Ball:
	{		
		if (currState == &stateFalling)
		{
			SetVelocity({ GetVelocity().x  ,jumpVelocity });
		}
		else if (this->Getposition().x <= objectB->GetPosition().x)
		{
			hurtTimer = hurtTime;
			SetPosition({ Getposition().x - (heroRect.Right() - collideRect.Left()), Getposition().y });

			SetVelocity({ -acceleration  ,jumpVelocity });
			ChangeState(&stateFalling);
		}
		else
		{
			hurtTimer = hurtTime;
			SetPosition({ Getposition().x + (collideRect.Right() - heroRect.Left()), Getposition().y });
			SetVelocity({ acceleration  ,jumpVelocity  });
			ChangeState(&stateFalling);
		}
	}
	break;

	case GameObjectType::Trigger:
	{
		objectB->ResolveCollision(this);
	}
	break;
	}

}

bool Hero::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType != GameObjectType::Hero && objectBType != GameObjectType::Particle)
	{
		return true;
	}
	return false;
}

void Hero::UpdateXVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		UpdateVelocity(math::vec2{ -(acceleration * dt),0 });
		if (GetVelocity().x < -max_velocity)
		{
			SetVelocity(math::vec2{ -max_velocity,GetVelocity().y });
		}
	}
	else if (moveRightKey.IsKeyDown() == true)
	{
		UpdateVelocity(math::vec2{ (acceleration * dt),0 });

		if (GetVelocity().x > max_velocity)
		{
			SetVelocity(math::vec2{ max_velocity,GetVelocity().y });
		}
	}

	else if (moveLeftKey.IsKeyDown() == false && moveRightKey.IsKeyDown() == false)
	{
		if (GetVelocity().x < 0)
		{
			UpdateVelocity(math::vec2{ (drag * dt),0 });
			if (GetVelocity().x > 0)
			{
				SetVelocity(math::vec2{ 0,GetVelocity().y });
			}
		}
		else if (GetVelocity().x > 0)
		{
			UpdateVelocity(math::vec2{ -(drag * dt),0 });
			if (GetVelocity().x < 0)
			{
				SetVelocity(math::vec2{ 0,GetVelocity().y });
			}
		}
	}
}

void Hero::State_Jumping::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->SetVelocity(math::vec2{ hero->GetVelocity().x, Hero::jumpVelocity });
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->standingOnObject = nullptr;
}

void Hero::State_Jumping::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity(math::vec2{ 0,-(Engine::GetGSComponent<Gravity>()->GetValue() * dt) });
	hero->UpdateXVelocity(dt);  //Change X Velocity stuff
}

void Hero::State_Jumping::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == false) {  //Jump Key not pressed
		hero->SetVelocity(math::vec2{ hero->GetVelocity().x,0 });
	}
	if (hero->GetVelocity().y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Idle::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
	if (hero->standingOnObject == nullptr)
	{
		Engine::GetLogger().LogError("Hero standing on null!");
	}
}

void Hero::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{

}

void Hero::State_Idle::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	else if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Running::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->SetScale(math::vec2{ -1.0,1.0 });
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->SetScale(math::vec2{ 1.0,1.0 });
	}
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (hero->standingOnObject == nullptr)
	{
		Engine::GetLogger().LogError("Hero standing on null!");
	}
}

void Hero::State_Running::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}

void Hero::State_Running::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetVelocity().x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	else if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->GetVelocity().x > 0 && hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateSkidding);
	}

	else if (hero->GetVelocity().x < 0 && hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
	
	if (hero->standingOnObject != nullptr)
	{
		if (hero->standingOnObject->DoesCollideWith(hero->GetPosition()) == false)
		{
			hero->ChangeState(&hero->stateFalling);
			hero->standingOnObject = nullptr;
		}
	}

}

void Hero::State_Skidding::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}

void Hero::State_Skidding::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetVelocity().x < 0)
	{
		hero->UpdateVelocity(math::vec2{ (drag * 2 * dt) ,0 });
	}
	else if (hero->GetVelocity().x > 0)
	{
		hero->UpdateVelocity(math::vec2{ -(drag * 2 * dt) ,0 });
	}

}

void Hero::State_Skidding::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x <= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x >= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == false && hero->moveLeftKey.IsKeyDown() == false)
	{
		hero->ChangeState(&hero->stateRunning);
	}
}

void Hero::State_Falling::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}

void Hero::State_Falling::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity(math::vec2{ 0,-(Engine::GetGSComponent<Gravity>()->GetValue() * dt) });
	hero->UpdateXVelocity(dt);
}

void Hero::State_Falling::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->standingOnObject !=nullptr)
	{
		hero->SetVelocity(math::vec2{ hero->GetVelocity().x,0 });
		if (hero->GetVelocity().x > 0)
		{
			if (hero->moveLeftKey.IsKeyDown() == false)
			{
				hero->ChangeState(&hero->stateRunning);
			}
			else if (hero->moveLeftKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
		}
		else if (hero->GetVelocity().x < 0)
		{
			if (hero->moveRightKey.IsKeyDown() == false)
			{
				hero->ChangeState(&hero->stateRunning);
			}
			else if (hero->moveRightKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
		}
		else if (hero->GetVelocity().x == 0)
		{
			hero->ChangeState(&hero->stateIdle);
		}
	}
		if (hero->GetPosition().y < -300)
		{
			hero->isDead = true;
		}
}