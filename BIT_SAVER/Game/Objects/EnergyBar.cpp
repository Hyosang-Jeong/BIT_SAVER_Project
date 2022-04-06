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
	GameObject(startPos, glm::vec2{ 3,4 }),
	gameover(InputKey::Keyboard::Space)
{
	AddGOComponent(new Sprite("../images/HP.png", this));
}

void EnergyBar::Update(double dt)
{
	GameObject::Update(dt);

	//SetPosition({ -8.f,5.f });

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


