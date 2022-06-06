/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Clear.cpp
Project: BIT_SAVER
Author: Hyun Kang
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"State.h"
#include "Clear.h"
#include"../../Engine/Sprite/Texture.h"
Clear::Clear() :
    ESCAPE(InputKey::Keyboard::Enter)
{}

void Clear::Load()
{
    board = Engine::GetTextureManager().Load("../images/score_board.png");
    star_1 = Engine::GetTextureManager().Load("../images/star_score_1.png");
    star_2 = Engine::GetTextureManager().Load("../images/star_score_2.png");
    star_3 = Engine::GetTextureManager().Load("../images/star_score_3.png");
    hero = Engine::GetTextureManager().Load("../images/hero_dance.png");
}

void Clear::Update([[maybe_unused]] double dt)
{
    if (ESCAPE.IsKeyDown() == true)
    {
	Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
    }
}

void Clear::Draw()
{
    glm::vec2 window_pos = Engine::GetWindow().GetSize();

    const std::string font1{ font_path[MochiyPopOne] };
    const std::string font2{ font_path[PressStart] };
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Engine::GetText(font2).Draw("Clear!", 0.f, 50.f, 3.f, { 0.5f,0.5f,0.5f });
    //Engine::GetText(font2).Draw("Press Enter to go MainMenu", 0.f, 250.f, 3.f, { 0.5f,0.5f,0.5f });
    int timer;
    timer = static_cast<int>(glfwGetTime()) % 2;

    board->Draw({ 0,0 }, { 10,10 });

    hero->Draw({ -8,0 }, { ((timer*2) - 1)*2,2 });

    //Draw music name
    Engine::GetText(font1).Draw(currLevel, window_pos.x*0.34f, window_pos.y * 0.19f, 1.f, { 1.f,1.f,1.f });

    //Draw score
    Engine::GetText(font1).Draw("Score", window_pos.x * 0.33f, window_pos.y * 0.47f, 1.f, { 1.f,1.f,1.f });
    Engine::GetText(font1).Draw(std::to_string(score), window_pos.x * 0.52f, window_pos.y * 0.47f, 1.f, { 1.f,1.f,1.f });
    
    //Draw Accuracy
    Engine::GetText(font1).Draw("Accuracy", window_pos.x * 0.33f, window_pos.y * 0.57f, 0.9f, { 1.f,1.f,1.f });

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << accuracy;
    std::string s = stream.str();

    Engine::GetText(font1).Draw(s + "%", window_pos.x * 0.52f, window_pos.y * 0.57f, 0.9f, {1.f,1.f,1.f});

    //Draw Perfect
    Engine::GetText(font1).Draw("Perfect", window_pos.x * 0.33f, window_pos.y * 0.675f, 1.f, { 1.f,1.f,1.f });
    Engine::GetText(font1).Draw(std::to_string(score_count[3]), window_pos.x * 0.52f, window_pos.y * 0.675f, 1.f, { 1.f,1.f,1.f });

    //Draw Good
    Engine::GetText(font1).Draw("Good", window_pos.x * 0.33f, window_pos.y * 0.785f, 1.f, { 1.f,1.f,1.f });
    Engine::GetText(font1).Draw(std::to_string(score_count[2]), window_pos.x * 0.52f, window_pos.y * 0.785f, 1.f, { 1.f,1.f,1.f });

    //Draw Bad
    Engine::GetText(font1).Draw("Miss", window_pos.x * 0.33f, window_pos.y * 0.885f, 1.f, { 1.f,1.f,1.f });
    Engine::GetText(font1).Draw(std::to_string(score_count[0]), window_pos.x * 0.52f, window_pos.y * 0.885f, 1.f, { 1.f,1.f,1.f });

    Draw_star();
}
void Clear::Setstats(std::string name, int score_, std::array<int, 4> score_count_)
{
    currLevel = name;
    score = score_;
    score_count = score_count_;

    accuracy = ((float)score_count[3] + (float)score_count[2] * 0.5f) / 
                        ((float)score_count[3] + (float)score_count[2] + (float)score_count[1] + (float)score_count[0]);
    accuracy *= 100.f;
}
void Clear::Draw_star()
{
    star_3->Draw({ 0,0 }, { 10,10 });
    if(accuracy > 70.f)
         star_2->Draw({ 0,0 }, { 10,10 });
    if(accuracy > 90.f)
         star_1->Draw({ 0,0 }, { 10,10 });
}
void Clear::Unload()
{
}
