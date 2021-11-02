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
#include "../Component.h"
#include<glm/glm.hpp>
class GameObject;

class GameObjectManager : public Component
{
public:
	void Add(GameObject* obj);
	void Add_front(GameObject* obj);
	void Unload();
	GameObject* Find(GameObjectType objType);

	void UpdateAll(double dt);
	void DrawAll(glm::mat3 camera_matrix);
	void collision_check(GameObject* object);

	std::list<GameObject*> GetgameObjects() { return gameObjects; }
private:
	std::list<GameObject*> gameObjects;
	
};


