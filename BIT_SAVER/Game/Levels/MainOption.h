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

enum class MAIN_SELECT
{
    NONE,
    VOLUME,
    VOLUME_SELECTED,
    KEY_CHANGE,
    KEY_CHANGE_SELECTED,
    OFF_SET,
    SOUND,
    QUIT,
};

class Hero;

class MainOption : public GameState
{
public:
    MainOption();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    std::string GetName() { return "MainOption"; }
    void Draw() override;

    void GetIndex();
    void SetOffsetTime(long double offsetTime_);
    long double GetOffsetTime();
    bool IsInBoxSound();
    void IsInBox();
    void changeSound(double dt);
    InputKey UpAttackKey;
    InputKey DownAttackKey;

private:
    bool IsUpkeychanged;
    bool IsDownkeychanged;
    double KeychangeTextTimer;
    Texture* textureAll;
    Texture* soundbar;
    Texture* bigSoundBall;
    Texture* smallSoundBall;
    Texture* Cursor;

    InputKey escape;
    InputKey MouseKey;

    float w;
    float h;
    bool mouseSwitch;
    MAIN_SELECT select;

    glm::vec2 selectedIndex;
    glm::vec2 SoundBallPosition;
    glm::vec2 SoundBallScale;
    glm::mat3 world_to_ndc;
    glm::vec2 mousePosition;
    glm::vec2 smallsoundballScale;
    
    glm::vec2 volume_pos;
    glm::vec2 key_pos;
    glm::vec2 offset_pos;
    glm::vec2 upkey_pos;
    glm::vec2 downkey_pos;

    long double offset_time;
};
