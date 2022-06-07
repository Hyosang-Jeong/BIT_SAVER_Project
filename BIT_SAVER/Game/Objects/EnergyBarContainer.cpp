/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnergyBar.cpp
Project: BIT_SAVER
Author: Jaewoo Choi
-----------------------------------------------------------------*/
#include"EnergyBarContainer.h"
#include"../../Engine/Engine.h"

EnergyBarContainer::EnergyBarContainer(glm::vec2 startPos) :
    GameObject(startPos, glm::vec2{ 3,4 })
{
    AddGOComponent(new Sprite("../images/HP_Container.png", this));
}

void EnergyBarContainer::Draw(glm::mat3 camera_matrix)
{
    GameObject::Draw(camera_matrix);
}




