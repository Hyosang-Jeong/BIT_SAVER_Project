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
ESCAPE(InputKey::Keyboard::Escape),
Level1(InputKey::Keyboard::P)
{
	model.init({ 1,1 });
}

void Mainmenu::Load()
{
    text.Load("../font/MochiyPopOne-Regular.ttf", 48);
	//mainmenu = Engine::GetTextureManager().Load("../images/mainmenu.png");
}

void Mainmenu::Update([[maybe_unused]]double dt)
{
	if (Level1.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
	}

	if (ESCAPE.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}

}

void Mainmenu::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	//mainmenu->Draw(glm::mat3{ 1,0,0,0,1,0,0,0,1 }, model, "Hero");
	text.Draw("Press P to play", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });

}
void Mainmenu::Unload()
{
}
