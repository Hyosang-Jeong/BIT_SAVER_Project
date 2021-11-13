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
    MouseKey(InputKey::Mouse::Left)
{
    select = -1;
    w = Engine::GetWindow().GetSize().x;
    h = Engine::GetWindow().GetSize().y;
    textureAll = Engine::GetTextureManager().Load("../images/Pause_screen.png");
    bigSoundBall = Engine::GetTextureManager().Load("../images/sound_bigball.png");
    smallSoundBall = Engine::GetTextureManager().Load("../images/sound_smallball.png");
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
    model.init({ 1,1 });
}

void Option::Update(double dt)
{
    mousePosition = Engine::GetInput().MouseGetPosition();
    mousePosition = world_to_ndc * glm::vec3(mousePosition, 1);

    GetIndex();
    std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
    changeSound(dt);
}

void Option::Draw()
{
    const std::string font1{ "../font/MochiyPopOne-Regular.ttf" };
    const std::string font2{ "../font/PressStart2P-Regular.ttf" };

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    textureAll->Draw(10, model, "Option", { 0,0 }, { 10,10 });
    bigSoundBall->Draw(10, model, "Option", SoundBallPosition, { 0.3,0.3 });
    smallSoundBall->Draw(10, model, "Option", SoundBallPosition, smallsoundballScale);


    glm::vec2 window_pos = Engine::GetWindow().GetSize();
    window_pos.x *= 0.5;
    window_pos.y *= 0.5;

    glm::vec2 offset(50, 100);

    //int offset_x = 0;
    //int offset_y = 0;

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
    std::cout << select << std::endl;
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
    else
    {
        select = -1;
    }

    //   if (OptionUpKey.IsKeyReleased() == true)
    //   {
      //if (select > Select::RESUME)
      //{
      //    select--;
      //}
      //else if (select == Select::RESUME)
      //{
      //    select = Select::QUIT;
      //}
    //   }
    //   else if (OptionDownKey.IsKeyReleased() == true)
    //   {
      //if (select < Select::QUIT)
      //{
      //    select++;
      //}
      //else if (select == Select::QUIT)
      //{
      //    select = Select::RESUME;
      //}
    //   }
    if (/*OptionSelectKey.IsKeyDown() == true ||*/ MouseKey.MouseIsKeyDown() == true)
    {
        switch (select)
        {
        case RESUME:
            Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
            break;
        case RESTART:
            Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
            break;
        case MAINMENU:
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
        Engine::GetMusic().SetVolume(Engine::GetMusic().REWIND, ((SoundBallPosition.x) + 1.5f) / 3.8f);
    }
}