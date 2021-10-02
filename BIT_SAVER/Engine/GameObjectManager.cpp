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

void GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void GameObjectManager::Unload()
{
	for (int i = 0; i < static_cast<int>(gameObjects.size()); i++)
	{
		delete gameObjects[i];
	}
	gameObjects.clear();
}

void GameObjectManager::UpdateAll(double dt)
{
	for (int i = 0; i < static_cast<int>(gameObjects.size()); i++)
	{
		gameObjects[i]->Update(dt);
	}
}

void GameObjectManager::DrawAll()
{
	for (int i = 0; i < static_cast<int>(gameObjects.size()); i++)
	{
		gameObjects[i]->Draw();
	}
}