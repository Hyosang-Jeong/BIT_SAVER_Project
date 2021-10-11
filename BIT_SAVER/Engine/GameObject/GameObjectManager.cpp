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
#include"..\Math\TransformMatrix.h"  //TransformMatrix

void GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void GameObjectManager::Unload()
{
	for (GameObject* a : gameObjects)
	{
		delete a;
	}

	gameObjects.clear();
}

void GameObjectManager::UpdateAll(double dt)
{
	std::list<GameObject* > removelist;
	for (GameObject* a : gameObjects)
	{
		a->Update(dt);
		if (a->Destroy() == true)
		{
			removelist.push_back(a);
		}
	}

	for (GameObject* remove : removelist)
	{
		gameObjects.remove(remove);
		delete remove;
	}
}

void GameObjectManager::DrawAll()
{
	for (GameObject* a : gameObjects)
	{
		a->Draw();
	}
}

bool GameObjectManager::collision_check(GameObject* object1, GameObject* object2)
{
	AABB Box1 = object1->GetAABB();
	AABB Box2 = object2->GetAABB();


	if (Box1.max.x < Box2.min.x || Box1.min.x > Box2.max.x)
	{
		return false;
	}

	if ((Box1.max.y < Box2.min.y || Box1.min.y > Box2.max.y))
	{
		return false;
	}
	return true;
}

