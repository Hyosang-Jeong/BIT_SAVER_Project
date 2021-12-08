/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Option.cpp
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "Option.h"
#include "../Engine/Engine.h"   //GetGameStateManage
#include"Mainmenu.h"
#include"State.h"
#include"../Objects/Hero.h"
#include"../Levels/MainOption.h"
#include "../../Engine/Music/Sound_Num.h"


Option::Option() :
    escape(InputKey::Keyboard::Escape),
    OptionUpKey(InputKey::Keyboard::Up),
    OptionDownKey(InputKey::Keyboard::Down),
    OptionSoundUpKey(InputKey::Keyboard::Right),
    OptionSoundDownKey(InputKey::Keyboard::Left),
    OptionSelectKey(InputKey::Keyboard::Enter),
    mouseSwitch(false),
    selectedIndex(glm::vec2{ 0,1 }),
    SoundBallPosition(glm::vec2{ 0.3,3.5 }),
    SoundBallScale(glm::vec2{ 0.2,0.2 }),
    smallsoundballScale(glm::vec2{ 0.2,0.2 }),
    Resume(glm::vec2{ 0,0 }),
    Restart(glm::vec2{ 0,0 }),
    Mainmenu(glm::vec2{ 0,0 }),
    Quit(glm::vec2{ 0,0 }),
    mousePosition(glm::vec2{ 0,0 }),
    MouseKey(InputKey::Mouse::Left),
    ChangeKey(InputKey::Keyboard::Space),
    UpAttackKey(InputKey::Keyboard::None),
    DownAttackKey(InputKey::Keyboard::None)
{
    select = -1;
    w = Engine::GetWindow().GetSize().x;
    h = Engine::GetWindow().GetSize().y;
    world_to_ndc =
    {
   20 / w, 0,0,
   0,-20 / h,0,
   -10,10,1
    };

}

void Option::Load()
{
    select = RESUME;
    textureAll = Engine::GetTextureManager().Load(texture_path[Pause]);
    bigSoundBall = Engine::GetTextureManager().Load(texture_path[Sound_Bigball]);
    smallSoundBall = Engine::GetTextureManager().Load(texture_path[Sound_Smallball]);
    UpAttackKey=(static_cast<Option*>(Engine::GetGameStateManager().Find("MainOption"))->UpAttackKey);
    DownAttackKey = (static_cast<Option*>(Engine::GetGameStateManager().Find("MainOption"))->DownAttackKey);
}

void Option::Update(double dt)
{
    mousePosition = Engine::GetInput().MouseGetPosition();
    mousePosition = world_to_ndc * glm::vec3(mousePosition, 1);
    if (ChangeKey.IsKeyDown() == true && ChangeKey.IsKeyReapeated() == false)
    {
        if (select == Select::KEYBOARD)
        {
            select = -1;
        }
        else
        {
            select = Select::KEYBOARD;
            Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
             IsUpkeychanged = false;
             IsDownkeychanged = false;
             KeychangeTextTimer = 1;
        }
    }
    KeychangeTextTimer -= dt;
    GetIndex();
    changeSound(dt);
}

void Option::Draw()
{
    const std::string font1{ font_path[MochiyPopOne] };
    const std::string font2{ font_path[PressStart] };

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    Engine::GetGameStateManager().GetCurrstate()->Draw();


    textureAll->Draw({ 0,0 }, { 10,10 });
    bigSoundBall->Draw(SoundBallPosition, { 0.3,0.3 });
    smallSoundBall->Draw(SoundBallPosition, smallsoundballScale);


    glm::vec2 window_pos = Engine::GetWindow().GetSize();
    window_pos.x *= 0.5;
    window_pos.y *= 0.5;

    glm::vec2 offset(50, 100);
    Engine::GetText(font2).Draw("Press Spacebar to change Attack key", 0.f, 50.f, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
    if (select == Select::KEYBOARD)
    {
        if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None)
        {
            if (Engine::GetInput().GetLastPressedButton() >= InputKey::Keyboard::A && Engine::GetInput().GetLastPressedButton() <= InputKey::Keyboard::Z)
            {
                if (IsUpkeychanged == false)
                {
                    static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->UpAttackKey.button = Engine::GetInput().GetLastPressedButton();
                    Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
                    IsUpkeychanged = true;
                    KeychangeTextTimer = 1;
                }
                else if (IsDownkeychanged == false && Engine::GetInput().GetLastPressedButton() != UpAttackKey.button)
                {
                    static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->DownAttackKey.button = Engine::GetInput().GetLastPressedButton();
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
             if (KeychangeTextTimer >0.5)
             {
                 Engine::GetText(font2).Draw("Up attack Key : " + Upresult, 0.f, 75.f, 1.f, glm::vec3(1.f, 1.f, 1.f));
                 Engine::GetText(font2).Draw("Down attack Key : " + Downresult, 0.f, 100.f, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
             }
             else
             {
                 Engine::GetText(font2).Draw("Up attack Key : " + Upresult, 0.f, 75.f, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
                 Engine::GetText(font2).Draw("Down attack Key : " + Downresult, 0.f, 100.f, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
             }
             if (KeychangeTextTimer < 0)
             {
                 KeychangeTextTimer = 1;
             }
         }
         else if(IsDownkeychanged == false)
         {
             if (KeychangeTextTimer > 0.5)
             {
                 Engine::GetText(font2).Draw("Up attack Key : " + Upresult, 0.f, 75.f, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
                 Engine::GetText(font2).Draw("Down attack Key : " + Downresult, 0.f, 100.f, 1.f, glm::vec3(1.f, 1.f, 1.f));
             }
             else
             {
                 Engine::GetText(font2).Draw("Up attack Key : " + Upresult, 0.f, 75.f, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
                 Engine::GetText(font2).Draw("Down attack Key : " + Downresult, 0.f, 100.f, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));        
             }
             if (KeychangeTextTimer < 0)
             {
                 KeychangeTextTimer = 1;
             }
         }
         else
         {
             Engine::GetText(font2).Draw("Up attack Key : " + Upresult, 0.f, 75.f, 1.f, glm::vec3(1.f, 1.f, 1.f));
             Engine::GetText(font2).Draw("Down attack Key : " + Downresult, 0.f, 100.f, 1.f, glm::vec3(1.f, 1.f, 1.f));
         }
        Engine::GetText(font2).Draw("Press Spacebar to change Attack key", 0.f, 50.f, 1.f, glm::vec3(1.f, 1.f, 1.f));

    }

    Engine::GetText(font2).Draw("RESUME", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));

    if (select == Select::RESUME)
    {
        Engine::GetText(font2).Draw("RESUME", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(1.f, 1.f, 1.f));

    }
    Resume = { window_pos.x - offset.x ,window_pos.y - offset.y };
    Resume = world_to_ndc * glm::vec3(Resume, 1);

    offset.y -= 105;

    Engine::GetText(font2).Draw("RESTART", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
    if (select == Select::RESTART)
    {
        Engine::GetText(font2).Draw("RESTART", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(1.f, 1.f, 1.f));

    }
    Restart = { window_pos.x - offset.x ,window_pos.y - offset.y };
    Restart = world_to_ndc * glm::vec3(Restart, 1);
    offset.y -= 105;

    Engine::GetText(font2).Draw("MAIN MENU", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));

    if (select == Select::MAINMENU)
    {
        Engine::GetText(font2).Draw("MAIN MENU", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(1.f, 1.f, 1.f));
    }
    Mainmenu = { window_pos.x - offset.x ,window_pos.y - offset.y };
    Mainmenu = world_to_ndc * glm::vec3(Mainmenu, 1);

    offset.y -= 105;

    Engine::GetText(font2).Draw("QUIT", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
    if (select == Select::QUIT)
    {
        Engine::GetText(font2).Draw("QUIT", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(1.f, 1.f, 1.f));
    }
    Quit = { window_pos.x - offset.x ,window_pos.y - offset.y };
    Quit = world_to_ndc * glm::vec3(Quit, 1);

}


void Option::GetIndex()
{
    if (IsInBox(Resume) == true)
    {
        select = Select::RESUME;
    }
    else if (IsInBox(Restart) == true)
    {
        select = Select::RESTART;
    }
    else if (IsInBox(Mainmenu) == true)
    {
        select = Select::MAINMENU;
    }
    else if (IsInBox(Quit) == true)
    {
        select = Select::QUIT;
    }
    
    else if(select != Select::KEYBOARD)
    {
        select = -1;
    }

    if (MouseKey.MouseIsKeyReleased() == true)
    {
        switch (select)
        {
        case RESUME:
            Engine::GetGameStateManager().ResumeState();
            break;
        case RESTART:
            Engine::GetGameStateManager().ReloadState();
            break;
        case MAINMENU:
            Engine::GetGameStateManager().ReloadState();
            Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
            break;
        case QUIT:
            Engine::GetGameStateManager().Shutdown();
            break;
        default:
            break;
        }
    }



}

int Option::GetSelect()
{
    return select;
}

bool Option::IsInBoxSound(glm::vec2 pos)
{
    if (pos.x + 0.5 > mousePosition.x &&
        pos.x - 0.5 < mousePosition.x &&
        pos.y + 0.5 > mousePosition.y &&
        pos.y - 0.5 < mousePosition.y)
    {
        return true;
    }
    return false;
}

bool Option::IsInBox(glm::vec2 pos)
{
    if (pos.x + 2.9 > mousePosition.x &&
        pos.x - 1.7 < mousePosition.x &&
        pos.y + 0.8 > mousePosition.y &&
        pos.y - 1 < mousePosition.y)
    {
        return true;
    }
    return false;
}


void Option::Unload()
{
    textureAll = nullptr;
    bigSoundBall = nullptr;
    smallSoundBall = nullptr;
}

void Option::changeSound(double dt)
{
    if (IsInBoxSound(SoundBallPosition))
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
    else if (IsInBoxSound(SoundBallPosition) == false)
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
        if (mousePosition.x >= -1.5f && mousePosition.x <= 2.3f)
        {
            SoundBallPosition.x = mousePosition.x;
        }
        Engine::GetMusic().SetVolume(SOUND_NUM::REWIND, ((SoundBallPosition.x) + 1.5f) / 3.8f);
    }
}