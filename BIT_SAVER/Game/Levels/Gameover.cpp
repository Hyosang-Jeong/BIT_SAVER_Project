/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Gameover.cpp
Project: BIT_SAVER
Author:
Creation date: 
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"State.h"
#include "Gameover.h"

Gameover::Gameover() :
    ESCAPE(InputKey::Keyboard::Enter)
{
    gameover = nullptr;
}

void Gameover::Load()
{
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

    Engine::GetText().Draw("Game Over!", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });
    Engine::GetText().Draw("Press Enter to go MainMenu", 0.f, 250.f, 2.f, { 0.5f,0.5f,0.5f });

}
void Gameover::Unload()
{
}