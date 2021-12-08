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
#include "MainOption.h"


Offset::Offset() :
    ESCAPE(InputKey::Keyboard::Enter),
    HitKey(InputKey::Keyboard::Space),
    resultTime(0.),
    compareTime(0),
    currentTime(0.),
    hitNumber(0),
    isHit(false),
    x_pos(-100,-100)

{
    gameObjectManager = nullptr;
    trackPtr = nullptr;
}

void Offset::Load()
{
    resultTime = 0.;
    gameObjectManager = new GameObjectManager();

    trackPtr = new Track(SOUND_NUM::OFFSET);

    AddGSComponent(gameObjectManager);

    gameObjectManager->Add(trackPtr);

    offset_x = Engine::GetTextureManager().Load(texture_path[OFFSET_X]);

    //trackPtr->track_time.erase(trackPtr->track_time.begin(), trackPtr->track_time.begin() + 4);

    for (auto& i : trackPtr->track_time)
    {
        compareTime.push_back(i.time);

    }
    currentTime = compareTime[0];
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(Engine::GetWindow().ptr_window);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Engine::GetMusic().Play(SOUND_NUM::OFFSET);
}


void Offset::Update(double dt)
{
    if (HitKey.IsKeyDown())
        isHit = true;

    if (isHit == true)
    {
        currentTime += dt;
        gameObjectManager->UpdateAll(dt);
        if (HitKey.IsKeyDown() == true && HitKey.IsKeyReapeated() == false)
        {

            if (hitNumber < compareTime.size())
                resultTime += (currentTime - compareTime[hitNumber]);

            if(hitNumber < compareTime.size()-1)
                hitNumber++;
            
            if (gameObjectManager->GetgameObjects().size() >= 2)
            {
                x_pos = gameObjectManager->Find(GameObjectType::Note)->GetPosition();
            }

        }
        else if (ESCAPE.IsKeyDown() == true)
        {
            Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
        }
    }

}

void Offset::Draw()
{
    offset_x->Draw({ x_pos.x + 6.f , x_pos.y + 5.f }, { 1,1 });
}



long double Offset::GetResultTime()
{
    return resultTime;
}


void Offset::Unload()
{
    resultTime *= (1. / hitNumber);
    static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->SetOffsetTime(resultTime);
    currentTime = 0;
    hitNumber = 0;
    isHit = false;
    trackPtr = nullptr;

    gameObjectManager->Unload();
    Engine::GetMusic().Stop(SOUND_NUM::OFFSET);
    Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    ClearGSComponent();
}


