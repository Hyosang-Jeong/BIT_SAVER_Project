/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Option.h
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang , Hyosang Jung , Sunwoo Lee

-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include"..\Engine\Input\Input.h"  //input key
#include"../../Engine/Sprite/Texture.h"
#include"../../Engine/Engine.h"

enum  Select
{
    RESUME,
    RESTART,
    MAINMENU,
    QUIT
};

class Hero;
class Option : public GameState
{
public:
    Option();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    std::string GetName() { return "Option"; }
    void Draw() override;
    void GetIndex();
    int GetSelect();
    void Wait();
    void draw_second(double second);
private:
    bool IsUpkeychanged;
    bool IsDownkeychanged;
    double KeychangeTextTimer;
    Texture* textureAll;
    Texture* bigSoundBall;
    Texture* smallSoundBall;

    Texture* wait_3;
    Texture* wait_2;
    Texture* wait_1;

    InputKey escape;
    InputKey OptionUpKey;
    InputKey OptionDownKey;
    InputKey OptionSelectKey;

    glm::vec2 selectedIndex;

    int select;

    float w;
    float h;

    glm::vec2 Resume;
    glm::vec2 Restart;
    glm::vec2 Mainmenu;
    glm::vec2 Quit;
};
