/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainOption.h
Project: BIT_SAVER
Author:  Hyun Kang , Hyosang Jung , Sunwoo Lee

-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include"..\Engine\Input\Input.h"  //input key
#include"../../Engine/Sprite/Texture.h"
#include"../../Engine/Engine.h"

enum class MAIN_SELECT
{
    VOLUME,
    KEY_CHANGE,
    OFF_SET,
    QUIT,
};

class MainOption : public GameState
{
public:
    MainOption();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    SOUND_NUM GetcurrentMusic() override
    {
        return SOUND_NUM::JANJI;
    }
    std::string GetName() { return "MainOption"; }
    void Draw() override;
    float GetVolume();
 
    void SetOffsetTime(long double offsetTime_);
    long double GetOffsetTime();
    InputKey UpAttackKey;
    InputKey DownAttackKey;
    float WholeVolume = 0.5f;
private:
    bool IsUpkeychanged;
    bool IsDownkeychanged;
    double KeychangeTextTimer;
    Texture* main_screen;
    Texture* volume_option;
    Texture* key_option;
    Texture* offset_default;
    Texture* volume_ball;
    Texture* Button1;
    Texture* Button2;
    Texture* Button3;

    InputKey escape;
    InputKey enter;
    InputKey volume_up;
    InputKey volume_down;
    InputKey select_up;
    InputKey select_down;

    MAIN_SELECT select;
    glm::vec2 SoundBallPosition;
    glm::vec2 upkey_pos;
    glm::vec2 downkey_pos;

    long double offset_time;
};
