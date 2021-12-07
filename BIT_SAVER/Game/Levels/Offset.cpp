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
#include"../Objects/CheckBox.h"

Offset::Offset() :
    ESCAPE(InputKey::Keyboard::Enter),
    HitKey(InputKey::Keyboard::Space),
    result(0),
    camera({0,0})

{
    //	Engine::GetMusic().Init();
    checkBox = nullptr;
}

void Offset::Load()
{
    checkBox = new CheckBox({ -4,0 }, 0);
}

void Offset::Update([[maybe_unused]] double dt)
{
    //if (!Engine::GetMusic().isPlaying(Music::SOUND_NUM::REWIND))
    //    Engine::GetMusic().Play(Music::SOUND_NUM::REWIND);

    //		trackPtr->SetUpdate(true);
    //
    //result+= (미디의 시간과 내가 쳤을 때 시간 비교);
    if (HitKey.IsKeyDown() == true && HitKey.IsKeyReapeated() == false)
    {
        //result += 그때의 시간 - 미디 시간
    }
    else if (ESCAPE.IsKeyDown() == true)
    {
        Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
    }

}

void Offset::Draw()
{
    //const std::string font1{ font_path[MochiyPopOne] };
    //const std::string font2{ font_path[PressStart] };

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    checkBox->Draw(camera.GetMatrix());
    //Engine::GetText(font2).Draw("Clear!", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });
    //Engine::GetText(font2).Draw("Press Enter to go MainMenu", 0.f, 250.f, 3.f, { 0.5f,0.5f,0.5f });
}

void Offset::Unload()
{
    if (Engine::GetMusic().isPlaying(Music::SOUND_NUM::REWIND) == true)
    {
	Engine::GetMusic().Pause(Music::SOUND_NUM::REWIND);
    }
    checkBox = nullptr;

}
