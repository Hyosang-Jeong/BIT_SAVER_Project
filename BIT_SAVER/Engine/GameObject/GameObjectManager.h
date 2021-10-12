/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.h
Project: BIT_SAVER
Author: 
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once
#include<list>
#include"../../Game/Objects/GameObjectType.h"
class GameObject;

class GameObjectManager
{
public:
	void Add(GameObject* obj);
	void Unload();

	void UpdateAll(double dt);
	void DrawAll();
	bool collision_check(GameObject* object1, GameObject*object2);

	std::list<GameObject*> GetgameObjects() { return gameObjects; }
private:
	std::list<GameObject*> gameObjects;
};


