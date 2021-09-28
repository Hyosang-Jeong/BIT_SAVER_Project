/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 4/16/2021
-----------------------------------------------------------------*/
#include "Bunny.h"
#include"Bunny_Anims.h"
#include"..\Engine\Collision.h"
#include"Hero.h"
#include"../Engine/Engine.h"
#include"Score.h"
Bunny::Bunny(math::vec2 pos, std::vector<double> patrolNodes, Hero* heroPtr):patrolNodes(patrolNodes),heroPtr(heroPtr),currPatrolNode(0)
{
	AddGOComponent(new CS230::Sprite("assets/Bunny.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
	SetPosition(pos);
	currState = &statePatrol;
	currState->Enter(this);
}

void Bunny::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		ChangeState(&stateDead);
	}
}



void Bunny::State_Patrol::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);	
	if (bunny->currPatrolNode == bunny->patrolNodes.size() - 1)
	{
		bunny->SetScale(math::vec2{ 1.0,1.0 });
		bunny->SetVelocity({ bunny->GetScale().x * bunny->velocity ,0 });
	}
	else
	{
		bunny->SetScale(math::vec2{ -1.0,1.0 });
		bunny->SetVelocity({ bunny->GetScale().x * bunny->velocity ,0 });
	}
}

void Bunny::State_Patrol::Update(GameObject* object, double )
{
	Bunny* bunny = static_cast<Bunny*>(object);
	
	if (bunny->currPatrolNode == bunny->patrolNodes.size() - 1)
	{
		if (bunny->GetPosition().x > bunny->patrolNodes[bunny->currPatrolNode])
		{
			bunny->currPatrolNode--;
		}
	}
	else
	{
		if (bunny->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode])
		{
			bunny->currPatrolNode++;
		}
	}
	bunny->ChangeState(this);
}


void Bunny::State_Patrol::TestForExit(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	if (bunny->currPatrolNode == bunny->patrolNodes.size() - 1)
	{
		if (bunny->heroPtr->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetPosition().x < bunny->heroPtr->GetPosition().x && bunny->GetPosition().y == bunny->heroPtr->GetPosition().y)
		{
			bunny->ChangeState(&bunny->stateAttack);
		}
	}
	else
	{
		if (bunny->heroPtr->GetPosition().x > bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetPosition().x > bunny->heroPtr->GetPosition().x && bunny->GetPosition().y == bunny->heroPtr->GetPosition().y)
		{
			bunny->ChangeState(&bunny->stateAttack);
		}
	}
}

void Bunny::State_Attack::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Attack_Anim));
	if (bunny->currPatrolNode == bunny->patrolNodes.size() - 1)
	{
		bunny->SetScale(math::vec2{ 1.0,1.0 });
		bunny->SetVelocity({ bunny->GetScale().x * bunny->velocity*2 ,0 });
	}
	else
	{
		bunny->SetScale(math::vec2{ -1.0,1.0 });
		bunny->SetVelocity({ bunny->GetScale().x * bunny->velocity*2 ,0 });
	}
}

void Bunny::State_Attack::Update(GameObject* object, double )
{
	Bunny* bunny = static_cast<Bunny*>(object);
	if (bunny->currPatrolNode == bunny->patrolNodes.size() - 1)
	{
		if (bunny->GetPosition().x > bunny->patrolNodes[bunny->currPatrolNode])
		{
			bunny->ChangeState(&bunny->statePatrol);
			bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
		}
	}
	else
	{
		if (bunny->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode])
		{
			bunny->ChangeState(&bunny->statePatrol);
			bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
		}
	}
}


void Bunny::State_Attack::TestForExit(GameObject* )
{

}

void Bunny::State_Dead::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
	bunny->RemoveGOComponent<CS230::Collision>();
	Engine::GetGSComponent<Score>()->AddScore(100);
	bunny->SetVelocity({ 0,0 });
}



void Bunny::State_Dead::Update(GameObject* , double )
{
}

void Bunny::State_Dead::TestForExit(GameObject* )
{
}
