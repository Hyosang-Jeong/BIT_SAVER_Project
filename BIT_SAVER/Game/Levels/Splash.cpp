/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: BIT_SAVER
Author:	Hyosang Jung
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Splash.h"
#include"State.h"
#include"../Levels/Clear.h"
Splash::Splash() : PlayKey(InputKey::Keyboard::Enter),timer(6)
{
}

void Splash::Load()
{
	Digipen_Splash = Engine::GetTextureManager().Load(texture_path[DigipenLogo_Splash]);
	Logo = Engine::GetTextureManager().Load(texture_path[Gamelogo_Splash]);
}

void Splash::Update(double dt)
{
	timer -= dt;
	if (PlayKey.IsKeyReleased() == true)
	{
		if (timer <3)
		{
			Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
		}
	}
	if (timer < 0)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
	}

}

void Splash::Draw()
{
	if (timer > 3)
	{
		Digipen_Splash->Draw(glm::mat3{ 2 / 3.0,0,0,0,1 / 3.0,0,0,0,1 });
	}
	else
	{
		Logo->Draw(glm::mat3{ 1,0,0,0,1,0,0,0,1 });
	}
}
void Splash::Unload()
{
	Logo = nullptr;
}
