/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainOption.cpp
Project: BIT_SAVER
Author:  Hyun Kang , Hyosang Jung , Sunwoo Lee

-----------------------------------------------------------------*/
#include "MainOption.h"
#include "../Engine/Engine.h"   //GetGameStateManage
#include"Mainmenu.h"
#include"State.h"

#include"../Objects/Hero.h"

#include "../../Engine/Music/Sound_Num.h"


MainOption::MainOption() :
    escape(InputKey::Keyboard::Escape),
    UpAttackKey(Engine::GetAttack_Key().UpAttackKey),
    DownAttackKey(Engine::GetAttack_Key().DownAttackKey),
    enter(InputKey::Keyboard::Enter),
    volume_up(InputKey::Keyboard::Right),
    volume_down(InputKey::Keyboard::Left),
    select_up(InputKey::Keyboard::Up),
    select_down(InputKey::Keyboard::Down),
    SoundBallPosition{ 0,0 },
    upkey_pos{ 0,0 },
    downkey_pos{ 0,0 }
{}

void MainOption::Load()
{
    main_screen =    Engine::GetTextureManager().Load("../images/mainmenu.png");
    volume_option  = Engine::GetTextureManager().Load("../images/volume.png");
    key_option         = Engine::GetTextureManager().Load("../images/key_setting.png");
    offset_default = Engine::GetTextureManager().Load("../images/offset_default.png");
    volume_ball       = Engine::GetTextureManager().Load("../images/volume_ball.png");
    Button1               = Engine::GetTextureManager().Load("../images/option_button1.png");
    Button2               = Engine::GetTextureManager().Load("../images/option_button2.png");
    Button3               = Engine::GetTextureManager().Load("../images/option_button3.png");

    select = MAIN_SELECT::VOLUME;
    Engine::GetMusic().Play(SOUND_NUM::JANJI);
}

void MainOption::Update(double dt)
{

    glm::vec2 size = Engine::GetWindow().GetSize();
    WholeVolume = (SoundBallPosition.x + 1.25f) / 2.5f;
    Engine::GetMusic().SetVolume(WholeVolume);
    Engine::GetMusic().Update();
    KeychangeTextTimer -= dt;

    if (escape.IsKeyReleased() == true)
    {
        Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
    }
    if (select_up.IsKeyReleased() == true)
    {
        switch (select)
        {
        case (MAIN_SELECT::VOLUME):
        {
            select = MAIN_SELECT::OFF_SET;
            break;
        }
        case MAIN_SELECT::KEY_CHANGE:
        {
            select = MAIN_SELECT::VOLUME;
            break;
        }
        case MAIN_SELECT::OFF_SET:
        {
            select = MAIN_SELECT::KEY_CHANGE;
            break;
        }
        }
    }
    if (select_down.IsKeyReleased() == true)
    {
        switch (select)
        {
        case MAIN_SELECT::VOLUME:
        {
            select = MAIN_SELECT::KEY_CHANGE;
            break;
        }
        case MAIN_SELECT::KEY_CHANGE:
        {
            select = MAIN_SELECT::OFF_SET;
            break;
        }
        case MAIN_SELECT::OFF_SET:
        {
            select = MAIN_SELECT::VOLUME;
            break;
        }
        }
    }
    if (select == MAIN_SELECT::VOLUME)
    {
        if (volume_up.IsKeyReleased() == true)
        {
            if(SoundBallPosition.x <1.1f)
                  SoundBallPosition.x += 0.25f;
        }
        if (volume_down.IsKeyReleased() == true)
        {
            if (SoundBallPosition.x > -1.1f)
                  SoundBallPosition.x -= 0.25f;
        }
    }
    if (select == MAIN_SELECT::OFF_SET)
    {
        if (enter.IsKeyReleased() == true)
        {
            Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Offset));
        }
    }
}

void MainOption::Draw()
{
    const std::string font1{ font_path[MochiyPopOne] };
    const std::string font2{ font_path[PressStart] };
    glm::vec2 size = Engine::GetWindow().GetSize();
    upkey_pos.x = size.x * 0.52f;
    downkey_pos.x = size.x * 0.52f;

    upkey_pos.y = size.y * 0.26f;
    downkey_pos.y = size.y * 0.49f;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    main_screen->Draw({ 0,0 }, { 10,10 });
    if (select == MAIN_SELECT::VOLUME)
    {
        IsUpkeychanged = false;
        IsDownkeychanged = false;
         volume_option->Draw({ 0,0 }, { 10,10 });
         volume_ball->Draw(SoundBallPosition, {10,10 });
         Button1->Draw({ 0,0 }, { 10,10 });
    }
    if (select == MAIN_SELECT::KEY_CHANGE)
    {
        key_option->Draw({ 0,0 }, { 10,10 });
        Button2->Draw({ 0,0 }, { 10,10 });
        if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None)
        {
            if (Engine::GetInput().GetLastPressedButton() >= InputKey::Keyboard::A && Engine::GetInput().GetLastPressedButton() <= InputKey::Keyboard::Z)
            {
                if (IsUpkeychanged == false)
                {
                    UpAttackKey.button = Engine::GetInput().GetLastPressedButton();
                    Engine::GetAttack_Key().UpAttackKey = UpAttackKey;
                    Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
                    IsUpkeychanged = true;
                    KeychangeTextTimer = 1;
                }
                else if (IsDownkeychanged == false && Engine::GetInput().GetLastPressedButton() != UpAttackKey.button)
                {
                    DownAttackKey.button = Engine::GetInput().GetLastPressedButton();
                    Engine::GetAttack_Key().DownAttackKey = DownAttackKey;
                    Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
                    IsDownkeychanged = true;
                }
            }
        }

        char Upkey = 'A' + static_cast<char>((static_cast<int>(UpAttackKey.button) - static_cast<int>(InputKey::Keyboard::A)));
        char Downkey = 'A' + static_cast<char>((static_cast<int>(DownAttackKey.button) - static_cast<int>(InputKey::Keyboard::A)));
        std::string Upresult(1, Upkey);
        std::string Downresult(1, Downkey);
        float scale = 0.7f;
        if (IsUpkeychanged == false)
        {
            if (KeychangeTextTimer > 0.5)
            {
                Engine::GetText(font2).Draw("Up attack Key      " + Upresult, upkey_pos.x, upkey_pos.y, scale, glm::vec3(0.5f, 0.5f, 0.5f));
                Engine::GetText(font2).Draw("Down attack Key    " + Downresult, downkey_pos.x, downkey_pos.y, scale, glm::vec3(0.5f, 0.5f, 0.5f));
            }
            else
            {
                Engine::GetText(font2).Draw("Up attack Key      " + Upresult, upkey_pos.x, upkey_pos.y, scale, glm::vec3(1.f, 1.f, 1.f));
                Engine::GetText(font2).Draw("Down attack Key    " + Downresult, downkey_pos.x, downkey_pos.y, scale, glm::vec3(0.5f, 0.5f, 0.5f));
            }
            if (KeychangeTextTimer < 0)
            {
                KeychangeTextTimer = 1;
            }
        }
        else if (IsDownkeychanged == false)
        {
            if (KeychangeTextTimer > 0.5)
            {
                Engine::GetText(font2).Draw("Up attack Key      " + Upresult, upkey_pos.x, upkey_pos.y, scale, glm::vec3(0.5f, 0.5f, 0.5f));
                Engine::GetText(font2).Draw("Down attack Key    " + Downresult, downkey_pos.x, downkey_pos.y, scale, glm::vec3(0.5f, 0.5f, 0.5f));
            }
            else
            {
                Engine::GetText(font2).Draw("Up attack Key      " + Upresult, upkey_pos.x, upkey_pos.y, scale, glm::vec3(0.5f, 0.5f, 0.5f));
                Engine::GetText(font2).Draw("Down attack Key    " + Downresult, downkey_pos.x, downkey_pos.y, scale, glm::vec3(1.f, 1.f, 1.f));
            }
            if (KeychangeTextTimer < 0)
            {
                KeychangeTextTimer = 1;
            }
        }
        else
        {
            Engine::GetText(font2).Draw("Up attack Key      " + Upresult, upkey_pos.x, upkey_pos.y, scale, glm::vec3(1.f, 1.f, 1.f));
            Engine::GetText(font2).Draw("Down attack Key    " + Downresult, downkey_pos.x, downkey_pos.y, scale, glm::vec3(1.f, 1.f, 1.f));
        }
    } 
    if (select == MAIN_SELECT::OFF_SET)
    {
        offset_default->Draw({ 0,0 }, { 10,10 });
        Button3->Draw({ 0,0 }, { 10,10 });
        IsUpkeychanged = false;
        IsDownkeychanged = false;
    }
}

void MainOption::SetOffsetTime(long double offsetTime_)
{
    offset_time = offsetTime_;
}

long double MainOption::GetOffsetTime()
{
    return offset_time;
}


void MainOption::Unload()
{
    Engine::GetMusic().Stop(SOUND_NUM::JANJI);
}

float MainOption::GetVolume()
{
    return WholeVolume;
}