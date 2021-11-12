/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Clear.cpp
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Mainmenu.h"
#include"State.h"
#include "Clear.h"

Clear::Clear() :
    ESCAPE(InputKey::Keyboard::Enter)
{

}

void Clear::Load()
{
    //text.Load("../font/MochiyPopOne-Regular.ttf", 48);
}

void Clear::Update([[maybe_unused]] double dt)
{

    if (ESCAPE.IsKeyDown() == true)
    {
	Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
    }

}

void Clear::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Engine::GetText().Draw("Clear!", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });
    Engine::GetText().Draw("Press Enter to go MainMenu", 0.f, 250.f, 3.f, { 0.5f,0.5f,0.5f });

}
void Clear::Unload()
{
}
