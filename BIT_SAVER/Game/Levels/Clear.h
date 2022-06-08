/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Clear.h
Project: BIT_SAVER
Author: Hyun Kang
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include"..\Engine\Input\Input.h"  //input key

class Clear : public GameState
{
public:
    Clear();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    void Setstats(std::string name,int score, std::array<int, 4> score_count);
    void Update_star_scale(double dt);
    void Draw_star();
    void Set_lose(bool lose);
    std::string GetName() override { return "Clear"; }
    std::string currLevel;
    int score;
    float accuracy;
    std::array<int, 4> score_count;
    InputKey ESCAPE;
    Texture* board;
    Texture* star_1;
    Texture* star_2;
    Texture* star_3;
    Texture* main_menu;

    float star_1_scale;
    float star_2_scale;
    float star_3_scale;

    bool is_lose;
private:
};

