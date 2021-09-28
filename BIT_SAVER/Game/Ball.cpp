/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/25/2021
-----------------------------------------------------------------*/
#include"Ball.h"
#include "Gravity.h" //gravity
#include"../Engine/Engine.h"  //get gs component
#include"..\Engine\Collision.h"
Ball::Ball(math::vec2 startPos) : GameObject(startPos)
{
	AddGOComponent(new CS230::Sprite("assets/Ball.spt",this));
	currState = &bounce;
	currState->Enter(this);
}



void Ball::State_Bounce::Enter(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
	ball->UpdateVelocity({ 0, Ball::bounceVelocity });
}


void Ball::State_Bounce::Update(GameObject* object, double dt)
{
	static_cast<Ball*>(object)->UpdateVelocity(math::vec2{ 0,-(Engine::GetGSComponent<Gravity>()->GetValue() * dt) });
}


void Ball::State_Bounce::TestForExit(GameObject* ) 
{

}

bool Ball::CanCollideWith(GameObjectType objectBType) {
	if (objectBType == GameObjectType::Floor) {
		return true;
	}
	return false;
}

void Ball::ResolveCollision(CS230::GameObject* objectB) {
	if (objectB->GetObjectType() == GameObjectType::Floor) {
		CS230::RectCollision* collideRect =
			static_cast<CS230::RectCollision*>(objectB->GetGOComponent<CS230::RectCollision>());
		SetPosition({ GetPosition().x, collideRect->GetWorldCoorRect().Top() });
		SetVelocity({ GetVelocity().x, 0 });
		ChangeState(&land);
	}
}

void Ball::State_Land::Enter(GameObject* object) {
	Ball* ball = static_cast<Ball*>(object);
	ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
}


void Ball::State_Land::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
	
}


void Ball::State_Land::TestForExit(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
		if (ball->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
		{
			ball->ChangeState(&ball->bounce);
		}

}