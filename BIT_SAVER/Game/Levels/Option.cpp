/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Option.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang , Hyosang Jung , Sunwoo Lee

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
    OptionSelectKey(InputKey::Keyboard::Enter),
    selectedIndex(glm::vec2{ 0,1 })
{
    select = -1;
    w = Engine::GetWindow().GetSize().x;
    h = Engine::GetWindow().GetSize().y;

    Resume=glm::vec2{ 0,0 };
    Restart=glm::vec2{ 0,0 };
    Mainmenu=glm::vec2{ 0,0 };
    Quit=glm::vec2{ 0,0 };
}

void Option::Load()
{
    select = RESUME;
    textureAll = Engine::GetTextureManager().Load(texture_path[Pause]);
    bigSoundBall = Engine::GetTextureManager().Load(texture_path[Sound_Bigball]);
    smallSoundBall = Engine::GetTextureManager().Load(texture_path[Sound_Smallball]);
    wait_3 = Engine::GetTextureManager().Load("../images/3.png" );
    wait_2 = Engine::GetTextureManager().Load("../images/2.png" );
    wait_1 = Engine::GetTextureManager().Load("../images/1.png" );
   
}

void Option::Update(double )
{
    GetIndex();
    if (OptionUpKey.IsKeyReleased() == true)
    {
        switch (select)
        {
        case (Select::RESUME):
        {
            select = Select::QUIT;
            break;
        }
        case Select::RESTART:
        {
            select = Select::RESUME;
            break;
        }
        case Select::MAINMENU:
        {
            select = Select::RESTART;
            break;
        }
        case Select::QUIT:
        {
            select = Select::MAINMENU;
            break;
        }
        }
    }
    if (OptionDownKey.IsKeyReleased() == true)
    {
        switch (select)
        {
        case (Select::RESUME):
        {
            select = Select::RESTART;
            break;
        }
        case Select::RESTART:
        {
            select = Select::MAINMENU;
            break;
        }
        case Select::MAINMENU:
        {
            select = Select::QUIT;
            break;
        }
        case Select::QUIT:
        {
            select = Select::RESUME;
            break;
        }
        }
    }
}

void Option::Draw()
{
    if (static_cast<int>(Engine::GetGameStateManager().state) == 5)
    {
        return;
    }
    const std::string font1{ font_path[MochiyPopOne] };
    const std::string font2{ font_path[PressStart] };

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    Engine::GetGameStateManager().GetCurrstate()->Draw();

    textureAll->Draw({ 0,0 }, { 10,10 });

    glm::vec2 window_pos = Engine::GetWindow().GetSize();
    window_pos.x *= 0.5;
    window_pos.y *= 0.5;

    glm::vec2 offset(w*0.03, h*0.1);

    Engine::GetText(font2).Draw("RESUME", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));

    if (select == Select::RESUME)
    {
        Engine::GetText(font2).Draw("RESUME", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(1.f, 1.f, 1.f));

    }
    Resume = { window_pos.x - offset.x ,window_pos.y - offset.y };

    offset.y -= h * 0.1f;

    Engine::GetText(font2).Draw("RESTART", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
    if (select == Select::RESTART)
    {
        Engine::GetText(font2).Draw("RESTART", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(1.f, 1.f, 1.f));

    }
    Restart = { window_pos.x - offset.x ,window_pos.y - offset.y };
    offset.y -= h * 0.11f;

    Engine::GetText(font2).Draw("MAIN MENU", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));

    if (select == Select::MAINMENU)
    {
        Engine::GetText(font2).Draw("MAIN MENU", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(1.f, 1.f, 1.f));
    }
    Mainmenu = { window_pos.x - offset.x ,window_pos.y - offset.y };


    offset.y -= h * 0.11f;

    Engine::GetText(font2).Draw("QUIT", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(0.5f, 0.5f, 0.5f));
    if (select == Select::QUIT)
    {
        Engine::GetText(font2).Draw("QUIT", window_pos.x - offset.x, window_pos.y - offset.y, 1.f, glm::vec3(1.f, 1.f, 1.f));
    }
    Quit = { window_pos.x - offset.x ,window_pos.y - offset.y };

}


void Option::GetIndex()
{
    if (OptionSelectKey.IsKeyReleased() == true)
    {
        switch (select)
        {
        case RESUME:
        {
            Wait();
            Engine::GetGameStateManager().ResumeState(); 
            break;
        }
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

void Option::Wait()
{
    double timer = glfwGetTime();
    Engine::GetMusic().Play(SOUND_NUM::WAIT);
    while (glfwGetTime() - timer < 4)
    {
        glfwSwapBuffers(Engine::GetWindow().ptr_window);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        Engine::GetGameStateManager().GetCurrstate()->Draw();
        draw_second(glfwGetTime() - timer);
    }
    Engine::GetMusic().Pause(SOUND_NUM::WAIT);
}

void Option::draw_second(double second)
{
    if(second <=1.5)
        wait_3->Draw({ 0,5 }, { 1,2 });
    else if(second <=2.8)
        wait_2->Draw({ 0,5 }, { 1,2 });
    else
        wait_1->Draw({ 0,5 }, { 1,2 });
}


void Option::Unload()
{
    textureAll = nullptr;
    bigSoundBall = nullptr;
    smallSoundBall = nullptr;
}
