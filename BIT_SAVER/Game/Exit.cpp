/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Exit.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/20/2021
-----------------------------------------------------------------*/
#include "Exit.h"
#include"..\Engine\Rect.h"
#include"..\Engine\Collision.h" //Rectcollision
#include"..\Engine\Engine.h" //GetGameStateManager()
#include"Screens.h" //MainMenu

Exit::Exit(math::irect2 rect): GameObject(rect.point1)
{
	this->AddGOComponent(new CS230::RectCollision(math::irect2{ {0,0},{rect.Size().x,rect.Size().y} }, this));
}

void Exit::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
}
