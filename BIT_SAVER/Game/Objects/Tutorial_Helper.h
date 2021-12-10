/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tutorial_Helper.h
Project:BIT_SAVER
Author:  Hyosang Jung , Sunwoo Lee

-----------------------------------------------------------------*/
#pragma once
#include "..\..\Engine\Sprite\Texture.h" 
#include "..\Engine\Component.h" 
#include"../../Engine/Input/Input.h"
#include"Score.h"


class Tutorial_Helper : public Component
{
public:
    Tutorial_Helper();
    void AddScore(int newPoints);
    void Draw();
    void Set_state(int state);
    void Setflag(bool value);
    bool Getflag();
private:
    Texture* sound_bar;
    Texture* helper;
    InputKey nextKey;
    void RenderText();
    glm::vec2 winsize;
    glm::vec2 sound_bar_pos;
    bool flag;
    int index;
    int currstate;
};