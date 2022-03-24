/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnergyBar.cpp
Project: BIT_SAVER
Author: Jaewoo Choi
-----------------------------------------------------------------*/
#include"EnergyBar.h"
#include"../../Engine/Engine.h"
#include "../../Game/Objects/Hero.h"

EnergyBar::EnergyBar(glm::vec2 startPos) :
	GameObject(startPos, glm::vec2{ 1,0.2 }),
	gameover(InputKey::Keyboard::Space)
{
	AddGOComponent(new Sprite("../images/note1.png", this));
}

void EnergyBar::Update(double dt)
{
	GameObject::Update(dt);

	SetPosition({ GetPosition().x,Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().y + 1.2 });

#ifdef _DEBUG
	if (gameover.IsKeyReleased() == true)
	{
		SetScale({ -0.1,0 });
	}
#endif

}

bool EnergyBar::Isgameover()
{
		if (GetScale().x < 0)
		{
			return true;
		}
		return false;
}


