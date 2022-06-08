/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Offset.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Hyosang Jung 

-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Mainmenu.h"
#include"State.h"
#include "Offset.h"
#include"../Objects/CheckBox.h"
#include"../Objects/Hero.h"
#include"../Objects/Background.h"
#include "../Objects/EnergyBar.h"
#include "../../Engine/Music/Sound_Num.h"
#include "MainOption.h"


Offset::Offset() :
    ESCAPE(InputKey::Keyboard::Enter),
    HitKey(InputKey::Keyboard::Space),
    resultTime(0),
    currentResultTime(0.),
    compareTime(0),
    currentTime(0.),
    hitNumber(0),
    yourOffset(0),

    x_pos(-100,-100)

{
    gameObjectManager = nullptr;
    trackPtr = nullptr;
}

void Offset::Load()
{
    isHit = false;
    isoffset = false;
    isStart = false;
    isMusicEnd = false;
    RealCompareNumber = 0;
    resultTime = 0.;
    currentResultTime = 0.;
    pos.clear();
    x_pos = { -100, -100 };
    gameObjectManager = new GameObjectManager();

    trackPtr = new Track(SOUND_NUM::OFFSET);

    AddGSComponent(gameObjectManager);

    gameObjectManager->Add(trackPtr);

    offset_x = Engine::GetTextureManager().Load(texture_path[OFFSET_X]);
    offset_screen = Engine::GetTextureManager().Load("../images/offset_screen.png");
    offset_background = Engine::GetTextureManager().Load("../images/offset_background.png");
    //trackPtr->track_time.erase(trackPtr->track_time.begin(), trackPtr->track_time.begin() + 4);
    size_t _size = trackPtr->track_time.size();
    for (size_t i = 0; i < _size; i++)
    {
        track_time_vector.push_back(trackPtr->track_time.front());
        trackPtr->track_time.pop();
    }
    for (auto& i : track_time_vector)
    {
        compareTime.push_back(i.time);
    }
    for (size_t i = 0; i < _size; i++)
    {
        trackPtr->track_time.push(track_time_vector[i]);
    }
    currentTime = compareTime[0];
    interval = (compareTime[1] - compareTime[0]) * (1.2);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(Engine::GetWindow().ptr_window);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


void Offset::Update(double dt)
{
      
    if (HitKey.IsKeyDown())
        isHit = true;

    if (isHit == true)
    {
        if (!Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET) && isMusicEnd == false)
        {
            Engine::GetMusic().Play(SOUND_NUM::OFFSET);
            isMusicEnd = true;
        }
        currentTime += dt;
        intervalTime += dt;

        if (intervalTime > interval)
        {
            intervalTime = 0;
            if (RealCompareNumber < compareTime.size() - 1)
            {
                RealCompareNumber++;
            }
        }

        gameObjectManager->UpdateAll(dt);
        if (HitKey.IsKeyDown() == true && HitKey.IsKeyReapeated() == false && isoffset==false)
        {
            intervalTime = 0;

            if (hitNumber < compareTime.size())
            {
                currentResultTime = (currentTime - compareTime[RealCompareNumber]);
                resultTime += (currentTime - compareTime[RealCompareNumber]);
            }
            if (hitNumber < compareTime.size() - 1 && RealCompareNumber < compareTime.size() - 1)
            {
                hitNumber++;
                RealCompareNumber++;

            }
            if (gameObjectManager->GetgameObjects().size() >= 2)
            {
                if (hitNumber != 0)
                {
                    x_pos.x = (static_cast<float>(currentResultTime / static_cast<long double>(RealCompareNumber))) * 20.f;
                    pos.push_back(x_pos.x);
                }
            }
        }
        if (hitNumber != 0)
            yourOffset = resultTime / static_cast<long double>(RealCompareNumber);
    }

    if (ESCAPE.IsKeyDown() == true)
    {
        Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
        Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
    }
}

void Offset::Draw()
{

    offset_background->Draw({ 0  , 0 }, { 10,10 });
    offset_screen->Draw({ 0  , 0 }, { 10,10 });
    for (auto& i : pos)
    {
       offset_x->Draw({ i  , 0 }, { 10,10 });
    }

    const std::string font1{ font_path[MochiyPopOne] };
    if (isHit == false)
    {
        Engine::GetText(font1).Draw("Hit space bar at regular intervals to the music.!", 0.f, 50.f, 1.f, { 0.5f,0.5f,0.5f });
        Engine::GetText(font1).Draw("It starts when you hit!", 500.f, 130.f, 1.f, { 0.5f,0.5f,0.5f });
        Engine::GetText(font1).Draw("Press enter key to go out!", 500.f, 730.f, 1.f, { 0.5f,0.5f,0.5f });
    }
    if (isHit == true && Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET) == false)
    {
        if (isoffset == false)
            miliSeconds = static_cast<int>(yourOffset * 1000.f);

        Engine::GetText(font1).Draw("Your offset is " + std::to_string(miliSeconds) + "  milliSeconds.", 500.f, 530.f, 1.f, {0.5f,0.5f,0.5f});
        isoffset = true;
    }


}



long double Offset::GetResultTime()
{
    return resultTime;
}


void Offset::Unload()
{
    if (RealCompareNumber == 0)
    {
        RealCompareNumber = 1;
    }
    resultTime *= (1. / RealCompareNumber);
    static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->SetOffsetTime(resultTime);
    currentTime = 0;
    hitNumber = 0;
    RealCompareNumber = 0;
    intervalTime = 0;
    interval = 0;
    miliSeconds = 0;
    yourOffset = 0;
    isHit = false;
    isStart = false;
    isoffset = false;
    isMusicEnd = false;
    trackPtr = nullptr;

    gameObjectManager->Unload();
    if (Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET) == true)
        Engine::GetMusic().Stop(SOUND_NUM::OFFSET);

    Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    ClearGSComponent();
}


