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

Mainmenu::Mainmenu() :
	ChangeOffset(InputKey::Keyboard::Q),
	MainOption(InputKey::Keyboard::O),
	Tutorial(InputKey::Keyboard::NUM_0),
	Level1(InputKey::Keyboard::NUM_1),
	Level2(InputKey::Keyboard::NUM_2),
	Level3(InputKey::Keyboard::NUM_3),
	ESCAPE(InputKey::Keyboard::Escape)
{
}

void Mainmenu::Load()
{}

void Mainmenu::Update([[maybe_unused]] double dt)
{
	if (Tutorial.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Tutorial));
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
	const std::string font1{ font_path[MochiyPopOne] };
	const std::string font2{ font_path[PressStart] };

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//mainmenu->Draw(glm::mat3{ 1,0,0,0,1,0,0,0,1 }, model, "Hero");
	Engine::GetText(font2).Draw("Press 0 for Level 0", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });
	Engine::GetText(font2).Draw("Press 1 for Level 1", 0.f, 150.f, 3.f, { 0.5f,0.5f,0.5f });
	Engine::GetText(font2).Draw("Press 2 for Level 2", 0.f, 250.f, 3.f, { 0.5f,0.5f,0.5f });
	Engine::GetText(font2).Draw("Press 3 for Level 3", 0.f, 350.f, 3.f, { 0.5f,0.5f,0.5f });
	Engine::GetText(font2).Draw("Press Q to offset", 0.f, 450.f, 3.f, { 0.5f,0.5f,0.5f });
	Engine::GetText(font2).Draw("Press O to main option", 0.f, 550.f, 3.f, { 0.5f,0.5f,0.5f });
}
void Mainmenu::Unload()
{
}
