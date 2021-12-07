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
#include "Offset.h"

Offset::Offset() :
    ESCAPE(InputKey::Keyboard::Enter),
    BIT_SAVER(InputKey::Keyboard::Space)
{
    //	Engine::GetMusic().Init();
}

void Offset::Load()
{}

void Offset::Update([[maybe_unused]] double dt)
{
    //if (!Engine::GetMusic().isPlaying(Music::SOUND_NUM::REWIND))
    //    Engine::GetMusic().Play(Music::SOUND_NUM::REWIND);

    //		trackPtr->SetUpdate(true);

    if (BIT_SAVER.IsKeyDown() == true && BIT_SAVER.IsKeyReapeated() == false)
    {
    }
    else if (ESCAPE.IsKeyDown() == true)
    {
        Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
    }

}

void Offset::Draw()
{
    const std::string font1{ font_path[MochiyPopOne] };
    const std::string font2{ font_path[PressStart] };

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Engine::GetText(font2).Draw("Clear!", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });
    Engine::GetText(font2).Draw("Press Enter to go MainMenu", 0.f, 250.f, 3.f, { 0.5f,0.5f,0.5f });

}
void Offset::Unload()
{
}
