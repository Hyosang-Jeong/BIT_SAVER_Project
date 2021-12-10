/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.h
Project:
Author:
Creation date:
-----------------------------------------------------------------*/
#pragma once
#include "..\..\Engine\Sprite\Texture.h" 
#include "..\Engine\Component.h" 
#include"Score.h"


enum class Tuto_Helper_Enum
{
    GREETINGS,
    DOWN_NODE,
    UP_NODE,
    BOSS_EXPLAIN,
    BOSS,
    FEVER,
    END
};
class Tutorial_Helper : public Component
{
public:
    Tutorial_Helper();
    void AddScore(int newPoints);
    void Draw(glm::vec2 location);
    int Getflag();
private:
    void RenderText();

    int currstate;
    Score* score_ptr;
    Texture* helperPtr;
    Texture* textboxPtr;
};