/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mainmenu.cpp
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Mainmenu.h"
#include"State.h"
#include"../../Engine/Sprite/Texture.h"
Mainmenu::Mainmenu() :
	ChangeOffset(InputKey::Keyboard::Q),
	MainOption(InputKey::Keyboard::O),
	Tutorial(InputKey::Keyboard::T),
	Level0(InputKey::Keyboard::NUM_0),
	Level1(InputKey::Keyboard::NUM_1),
	Level2(InputKey::Keyboard::NUM_2),
	Level3(InputKey::Keyboard::NUM_3),
	ESCAPE(InputKey::Keyboard::Escape)
{
}

void Mainmenu::Load()
{
	mainmenu = Engine::GetTextureManager().Load("../images/mainmenu.png");
}

void Mainmenu::Update([[maybe_unused]] double dt)
{
	if (Tutorial.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Tutorial));
	}
	else if (Level0.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level0));
	}
	else if (Level1.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
	}
	else if (Level2.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level2));
	}
	else if (Level3.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level3));
	}
	else if (ChangeOffset.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Offset));
	}
	else if (ESCAPE.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
	else if (MainOption.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainOption));
	}
}

void Mainmenu::Draw()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mainmenu->Draw({ 0,0 }, { 10,10 });

}
void Mainmenu::Unload()
{
}
