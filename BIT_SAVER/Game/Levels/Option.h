/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Option.h
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include"..\Engine\Input\Input.h"  //input key
#include"../../Engine/Sprite/Texture.h"
#include"../../Engine/Engine.h"

enum  Select
{
    KEYBOARD,
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
    bool IsInBoxSound(glm::vec2 pos);
    bool IsInBox(glm::vec2 pos);
    void changeSound(double dt);
    InputKey UpAttackKey;
    InputKey DownAttackKey;
private:
    bool IsUpkeychanged;
    bool IsDownkeychanged;
    double KeychangeTextTimer;
    Texture* textureAll;
    Texture* bigSoundBall;
    Texture* smallSoundBall;

    InputKey escape;
    InputKey OptionUpKey;
    InputKey OptionDownKey;
    InputKey OptionSoundUpKey;
    InputKey OptionSoundDownKey;
    InputKey OptionSelectKey;
    InputKey MouseKey;
    InputKey ChangeKey;


    bool mouseSwitch;
    glm::vec2 selectedIndex;

    int select;

    glm::vec2 SoundBallPosition;
    glm::vec2 SoundBallScale;

    float w;
    float h;
    glm::mat3 world_to_ndc;
    glm::vec2 mousePosition;

    glm::vec2 smallsoundballScale;

    glm::vec2 Resume;
    glm::vec2 Restart;
    glm::vec2 Mainmenu;
    glm::vec2 Quit;
};
