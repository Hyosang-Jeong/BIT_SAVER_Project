/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Gameover.cpp
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Mainmenu.h"
#include"State.h"
#include "Gameover.h"

Gameover::Gameover() :
    ESCAPE(InputKey::Keyboard::Enter)
{

}

void Gameover::Load()
{
    text.Load("../font/MochiyPopOne-Regular.ttf", 48);
}

void Gameover::Update([[maybe_unused]] double dt)
{

    if (ESCAPE.IsKeyDown() == true)
    {
	Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
    }

}

void Gameover::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    text.Draw("Game Over!", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });
    text.Draw("Press Enter to go MainMenu", 0.f, 250.f, 2.f, { 0.5f,0.5f,0.5f });

}
void Gameover::Unload()
{
}
