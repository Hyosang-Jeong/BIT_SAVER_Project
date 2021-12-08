/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Option.cpp
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "MainOption.h"
#include "../Engine/Engine.h"   //GetGameStateManage
#include"Mainmenu.h"
#include"State.h"

#include"../Objects/Hero.h"

#include "../../Engine/Music/Sound_Num.h"


MainOption::MainOption() :
    escape(InputKey::Keyboard::Escape),
    mouseSwitch(false),
    selectedIndex(glm::vec2{ 0,1 }),
    SoundBallPosition(glm::vec2{ 6.0625,5.74 }),
    SoundBallScale(glm::vec2{ 0.6,0.6 }),
    smallsoundballScale(glm::vec2{ 0.2,0.2 }),
    mousePosition(glm::vec2{ 0,0 }),
    MouseKey(InputKey::Mouse::Left),
    UpAttackKey(InputKey::Keyboard::F),
    DownAttackKey(InputKey::Keyboard::J)
{}

void MainOption::Load()
{
    textureAll = Engine::GetTextureManager().Load(texture_path[Main_Option]);
    soundbar = Engine::GetTextureManager().Load(texture_path[MAIN_SOUND_BAR]);
    bigSoundBall = Engine::GetTextureManager().Load(texture_path[Sound_Bigball]);
    smallSoundBall = Engine::GetTextureManager().Load(texture_path[Sound_Smallball]);
    Cursor = Engine::GetTextureManager().Load(texture_path[MOUSE_CURSOR]);
    select = MAIN_SELECT::NONE;
    w = Engine::GetWindow().GetSize().x;
    h = Engine::GetWindow().GetSize().y;
    world_to_ndc =
    {
   20 / w, 0,0,
   0,-20 / h,0,
   -10,10,1
    };
}

void MainOption::Update(double dt)
{
    glm::vec2 window_pos = Engine::GetWindow().GetSize();
    window_pos.x *= 0.5;
    window_pos.y *= 0.5;
    volume_pos = { window_pos.x - 70.f , window_pos.y - 280.f };
    key_pos = { window_pos.x - 100.f , window_pos.y - 50.f };
    offset_pos = { window_pos.x - 60.f, window_pos.y + 220.f };
    upkey_pos = { key_pos.x + 300, key_pos.y - 20 };
    downkey_pos= { key_pos.x + 300, key_pos.y + 20 };
    mousePosition = Engine::GetInput().MouseGetPosition();
    mousePosition = world_to_ndc * glm::vec3(mousePosition, 1);
    IsInBox();
    GetIndex();
    changeSound(dt);
    KeychangeTextTimer -= dt;

    if (escape.IsKeyReleased() == true)
    {
        Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
    }
}

void MainOption::Draw()
{
    const std::string font1{ font_path[MochiyPopOne] };
    const std::string font2{ font_path[PressStart] };
    std::cout << mousePosition.x << "     " << mousePosition.y << std::endl;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    textureAll->Draw({ 0,0 }, { 10,10 });

    Cursor->Draw({ mousePosition.x + 0.1, mousePosition.y - 0.5 }, { 0.5,0.5 });

    Engine::GetText(font2).Draw("VOLUME", volume_pos.x, volume_pos.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));

    if (select == MAIN_SELECT::VOLUME)
    {
        Engine::GetText(font2).Draw("VOLUME", volume_pos.x, volume_pos.y, 1.f, glm::vec3(0.4f, 0.f, 0.6f));
    }

    if (select == MAIN_SELECT::VOLUME_SELECTED)
    {
        soundbar->Draw({ 0,0 }, { 10,10 });
        bigSoundBall->Draw(SoundBallPosition, { 0.5,0.5 });
        smallSoundBall->Draw(SoundBallPosition, smallsoundballScale);
    }

    Engine::GetText(font2).Draw("KEY CHANGE",key_pos.x,key_pos.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));

    if (select == MAIN_SELECT::KEY_CHANGE)
    {
        Engine::GetText(font2).Draw("KEY CHANGE", key_pos.x, key_pos.y, 1.f, glm::vec3(0.4f, 0.f, 0.6f));
    }

    Engine::GetText(font2).Draw("OFFSET", offset_pos.x,offset_pos.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));

    if (select == MAIN_SELECT::OFF_SET)
    {
        Engine::GetText(font2).Draw("OFFSET", offset_pos.x, offset_pos.y, 1.f, glm::vec3(0.4f, 0.f, 0.6f));
    }

    if (select == MAIN_SELECT::KEY_CHANGE_SELECTED)
    {
        if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None)
        {
            if (Engine::GetInput().GetLastPressedButton() >= InputKey::Keyboard::A && Engine::GetInput().GetLastPressedButton() <= InputKey::Keyboard::Z)
            {
                if (IsUpkeychanged == false)
                {
                    UpAttackKey.button = Engine::GetInput().GetLastPressedButton();
                    Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
                    IsUpkeychanged = true;
                    KeychangeTextTimer = 1;
                }
                else if (IsDownkeychanged == false && Engine::GetInput().GetLastPressedButton() != UpAttackKey.button)
                {
                    DownAttackKey.button = Engine::GetInput().GetLastPressedButton();
                    Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
                    IsDownkeychanged = true;
                }
            }
        }

        char Upkey = 'A' + static_cast<char>((static_cast<int>(UpAttackKey.button) - static_cast<int>(InputKey::Keyboard::A)));
        char Downkey = 'A' + static_cast<char>((static_cast<int>(DownAttackKey.button) - static_cast<int>(InputKey::Keyboard::A)));
        std::string Upresult(1, Upkey);
        std::string Downresult(1, Downkey);

        if (IsUpkeychanged == false)
        {
            if (KeychangeTextTimer > 0.5)
            {
                Engine::GetText(font2).Draw("Up attack Key : " + Upresult, upkey_pos.x, upkey_pos.y, 1.f, glm::vec3(0.f, 0.f, 0.f));
                Engine::GetText(font2).Draw("Down attack Key : " + Downresult, downkey_pos.x, downkey_pos.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
            }
            else
            {
                Engine::GetText(font2).Draw("Up attack Key : " + Upresult, upkey_pos.x, upkey_pos.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
                Engine::GetText(font2).Draw("Down attack Key : " + Downresult, downkey_pos.x, downkey_pos.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
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
                Engine::GetText(font2).Draw("Up attack Key : " + Upresult, upkey_pos.x, upkey_pos.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
                Engine::GetText(font2).Draw("Down attack Key : " + Downresult, downkey_pos.x, downkey_pos.y, 1.f, glm::vec3(0.f, 0.f, 0.f));
            }
            else
            {
                Engine::GetText(font2).Draw("Up attack Key : " + Upresult, upkey_pos.x, upkey_pos.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
                Engine::GetText(font2).Draw("Down attack Key : " + Downresult, downkey_pos.x, downkey_pos.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
            }
            if (KeychangeTextTimer < 0)
            {
                KeychangeTextTimer = 1;
            }
        }
        else
        {
            Engine::GetText(font2).Draw("Up attack Key : " + Upresult, upkey_pos.x, upkey_pos.y, 1.f, glm::vec3(0.f, 0.f, 0.f));
            Engine::GetText(font2).Draw("Down attack Key : " + Downresult, downkey_pos.x , downkey_pos.y, 1.f, glm::vec3(0.f, 0.f, 0.f));
        }
    }

}


void MainOption::GetIndex()
{
    if (MouseKey.MouseIsKeyReleased() == true)
    {
        switch (select)
        {
        case MAIN_SELECT::VOLUME:
            select = MAIN_SELECT::VOLUME_SELECTED;
            break;
        case MAIN_SELECT::KEY_CHANGE:
            select = MAIN_SELECT::KEY_CHANGE_SELECTED;
            Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
            IsUpkeychanged = false;
            IsDownkeychanged = false;
            break;
        case MAIN_SELECT::OFF_SET:
            Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Offset));
            break;
        default:
            break;
        }
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


bool MainOption::IsInBoxSound()
{
    if (SoundBallPosition.x+SoundBallScale.x > mousePosition.x && SoundBallPosition.x - SoundBallScale.x < mousePosition.x)
    {
        if (SoundBallPosition.y + SoundBallScale.y > mousePosition.y && SoundBallPosition.y - SoundBallScale.y < mousePosition.y)
        {
            return true;
        }
    }
    return false;
}

void MainOption::IsInBox()
{
    if (mousePosition.x > -1.8 && mousePosition.x < 1.65)
    {
        if(mousePosition.y > 4.5 && mousePosition.y < 7)
        {
            if (select != MAIN_SELECT::VOLUME_SELECTED)
            {
                select = MAIN_SELECT::VOLUME;
            }
        }

        else if (mousePosition.y > 0.5 && mousePosition.y < 2)
        {
            if (select != MAIN_SELECT::KEY_CHANGE_SELECTED)
            {
                select = MAIN_SELECT::KEY_CHANGE;
            }
        }

        else  if (mousePosition.y > -5.5 && mousePosition.y < -3)
        {
                select = MAIN_SELECT::OFF_SET;    
        }

        else
        {
            if (select != MAIN_SELECT::VOLUME_SELECTED)
            {
                select = MAIN_SELECT::NONE;
            }
        }
    }

    else
    {
        if (select != MAIN_SELECT::VOLUME_SELECTED)
        {
            select = MAIN_SELECT::NONE;
        }
    }

}


void MainOption::Unload()
{
}

void MainOption::changeSound(double dt)
{
    if (IsInBoxSound())
    {
        if (smallsoundballScale.x < 0.59f)
        {
            smallsoundballScale.x += static_cast<float>(dt);
        }
        if (smallsoundballScale.y < 0.59f)
        {
            smallsoundballScale.y += static_cast<float>(dt);
        }

        if (MouseKey.MouseIsKeyDown() == true)
        {
            mouseSwitch = true;
        }
        else
        {
            mouseSwitch = false;
        }
    }
    else if (IsInBoxSound() == false)
    {
        if (smallsoundballScale.x > 0.2f)
        {
            smallsoundballScale.x -= static_cast<float>(dt);
        }
        if (smallsoundballScale.y > 0.2f)
        {
            smallsoundballScale.y -= static_cast<float>(dt);
        }
    }
    if (mouseSwitch == true && MouseKey.MouseIsKeyDown() == true)
    {
        if (mousePosition.x >= 3.575f && mousePosition.x <= 8.55f)
        {
            SoundBallPosition.x = mousePosition.x;
        }

        Engine::GetMusic().SetVolume((SoundBallPosition.x - 3.55f) / 5.f);
    }
}