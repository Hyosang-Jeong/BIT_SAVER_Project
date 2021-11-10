/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Note_collisionBox.cpp
Project: BIT_SAVER
Author:
Creation date: 11/02/2021
-----------------------------------------------------------------*/
#include"EnergyBar.h"
#include"../../Engine/Engine.h"
#include "../../Game/Objects/Hero.h"

EnergyBar::EnergyBar(glm::vec2 startPos) :
    GameObject(startPos, glm::vec2{ 1,0.2 })
{
    AddGOComponent(new Sprite("../images/note1.png", this));
}

void EnergyBar::Update(double dt)
{
    GameObject::Update(dt);

    SetPosition({GetPosition().x,
	Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().y + 1.2});

}

