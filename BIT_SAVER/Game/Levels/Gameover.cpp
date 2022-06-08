/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Gameover.cpp
Project: BIT_SAVER
Author: Hyun Kang
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"State.h"
#include "Gameover.h"

Gameover::Gameover() :
    ESCAPE(InputKey::Keyboard::Enter)
{}

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
    const std::string font1{ font_path[MochiyPopOne] };
    const std::string font2{ font_path[PressStart] };

  //  glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //Engine::GetGameStateManager().GetCurrstate()->Draw();
    Engine::GetText(font2).Draw("Game Over!", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });
    Engine::GetText(font2).Draw("Press Enter to go MainMenu", 0.f, 250.f, 2.f, { 0.5f,0.5f,0.5f });

}
void Gameover::Unload()
{
}
