/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 4/15/2021
-----------------------------------------------------------------*/
#include"GameObjectManager.h"
#include"GameObject.h"   // gameobject
#include"TransformMatrix.h"  //TransformMatrix
#include"Engine.h"
#include"Collision.h"
void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

CS230::GameObjectManager::~GameObjectManager()
{
	for (CS230::GameObject* gob : gameObjects)
	{
		delete gob;
	}
	gameObjects.clear();
}

void CS230::GameObjectManager::CollideTest()
{
	for (CS230::GameObject* gob1 : gameObjects)
	{
		for (CS230::GameObject* gob2 : gameObjects)
		{
			if (gob1 != nullptr && gob2 != nullptr)
			{
				if (gob1 != gob2)
				{
					if (gob1->CanCollideWith(gob2->GetObjectType()) == true)
					{
						if (gob1->DoesCollideWith(gob2) == true)
						{
							Engine::GetLogger().LogEvent("Collision Detected : " + gob1->GetObjectTypeName() + " and " + gob2->GetObjectTypeName());
							gob1->ResolveCollision(gob2);
						}
					}
				}
			}
		}
	}

}

void CS230::GameObjectManager::Update(double dt)
{
	std::list< CS230::GameObject*> destroyed_list;
	for (CS230::GameObject* gob : gameObjects)
	{
		gob->Update(dt);
		if (gob->is_destroyed() == true)
		{
			destroyed_list.push_back(gob);
		}
	}
	for (CS230::GameObject* gob : destroyed_list)
	{
		gameObjects.remove(gob);
		delete gob;
	}
}

void CS230::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (CS230::GameObject* gob : gameObjects)
	{
		gob->Draw(cameraMatrix);
	}


}