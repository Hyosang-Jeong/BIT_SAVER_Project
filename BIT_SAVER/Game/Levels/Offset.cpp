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
#include "../../Engine/Music/Sound_Num.h"

#include <iostream>

Offset::Offset() :
    ESCAPE(InputKey::Keyboard::Enter),
    HitKey(InputKey::Keyboard::Space),
    resultTime(0),
    compareTime(0),
    currentTime(0),
    hitNumber(0),
    isHit(false),
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

    gameObjectManager = new GameObjectManager();
    backPtr = new Background();
    heroPtr = new Hero({ -4,-5 });
    trackPtr = new Track(SOUND_NUM::OFFSET);
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

    trackPtr->track_time.erase(trackPtr->track_time.begin(), trackPtr->track_time.begin() + 4);
    for(auto & i : trackPtr->track_time)
        compareTime.push_back(i.time);
}

void Offset::Update(double dt)
{
    if (HitKey.IsKeyDown())
        isHit = true;

    if (isHit == true)
    {
        if (!Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET))
            Engine::GetMusic().Play(SOUND_NUM::OFFSET);
        currentTime += dt;

        GetGSComponent<Background>()->Update(dt);
        gameObjectManager->UpdateAll(dt);
        //CheckNextNote();

        if (HitKey.IsKeyDown() == true && HitKey.IsKeyReapeated() == false)
        {
            if(hitNumber==0)
                currentTime = static_cast<double>(compareTime[0]);

            hitNumber++;
            if (hitNumber < compareTime.size())
                resultTime += currentTime - compareTime[hitNumber];
        }
        else if (ESCAPE.IsKeyDown() == true)
        {
            Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
        }

        std::cout << resultTime/ static_cast<long double>(hitNumber) << std::endl;
        std::cout << hitNumber << std::endl;
    }
}

void Offset::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    GetGSComponent<Background>()->Draw(camera.GetMatrix());
    gameObjectManager->DrawAll(camera.GetMatrix());

}

void Offset::CheckNextNote()
{
    if (heroPtr->GetPosition().x -
        Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Note)->GetPosition().x > 2.0)
    {
        hitNumber++;
    }
}



//double Offset::GetResultTime()
//{
//    return resultTime;
//}


void Offset::Unload()
{
    currentTime = 0;
    hitNumber = 0;
    isHit = false;
    checkBox = nullptr;
    heroPtr = nullptr;
    trackPtr = nullptr;
    backPtr = nullptr;
    gameObjectManager->Unload();
    Engine::GetMusic().Stop(SOUND_NUM::OFFSET);
    Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET);
    ClearGSComponent();
}


