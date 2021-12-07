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
#include"../Objects/Hero.h"
#include"../Objects/Track.h"
#include"../Objects/Background.h"
#include "../Objects/EnergyBar.h"

Offset::Offset() :
    ESCAPE(InputKey::Keyboard::Enter),
    HitKey(InputKey::Keyboard::Space),
    resultTime(0),
    compareTime(0),
    camera({0,0})

{
    gameObjectManager = nullptr;
    backPtr = nullptr;
    heroPtr = nullptr;
    trackPtr = nullptr;
    checkBox = nullptr;
    energyBar = nullptr;
    Engine::GetMusic().Init();
}

void Offset::Load()
{
    compareTime = 0;//시간 넣어 놓고 시작?
    gameObjectManager = new GameObjectManager();
    backPtr = new Background();
    heroPtr = new Hero({ -4,-5 });
    trackPtr = new Track(Music::SOUND_NUM::REWIND);
    checkBox = new CheckBox({ -4,0 }, 0);
    energyBar = new EnergyBar({ -4,1.2 });

    backPtr->Add(texture_path[Background_1], 0);
    backPtr->Add(texture_path[Parallax1_5], 0.5);
    backPtr->Add(texture_path[Parallax1_4], 0.8);
    backPtr->Add(texture_path[Parallax1_3], 1.1);
    backPtr->Add(texture_path[Parallax1_2], 1.3);
    backPtr->Add(texture_path[Parallax1_1], 1.5);

    AddGSComponent(gameObjectManager);
    AddGSComponent(backPtr);

    gameObjectManager->Add(energyBar);
    gameObjectManager->Add(heroPtr);
    gameObjectManager->Add(checkBox);
    gameObjectManager->Add(trackPtr);

}

void Offset::Update( double dt)
{
    if (!Engine::GetMusic().isPlaying(Music::SOUND_NUM::REWIND))
        Engine::GetMusic().Play(Music::SOUND_NUM::REWIND);

    GetGSComponent<Background>()->Update(dt);
    gameObjectManager->UpdateAll(dt);

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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    GetGSComponent<Background>()->Draw(camera.GetMatrix());
    gameObjectManager->DrawAll(camera.GetMatrix());
    //Engine::GetText(font2).Draw("Clear!", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });
    //Engine::GetText(font2).Draw("Press Enter to go MainMenu", 0.f, 250.f, 3.f, { 0.5f,0.5f,0.5f });
}



double Offset::GetResultTime()
{
    return resultTime;
}


void Offset::Unload()
{

    if (Engine::GetMusic().isPlaying(SOUND_NUM::REWIND) == true)
    {
	Engine::GetMusic().Pause(SOUND_NUM::REWIND);
    }

    checkBox = nullptr;
    heroPtr = nullptr;
    trackPtr = nullptr;
    backPtr = nullptr;
    gameObjectManager->Unload();
    Engine::GetMusic().Stop(Music::SOUND_NUM::REWIND);
    ClearGSComponent();
}


