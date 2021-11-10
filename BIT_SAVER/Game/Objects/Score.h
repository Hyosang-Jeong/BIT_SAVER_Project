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
#include "..\..\Engine\Sprite\Sprite.h"

class Score : public Component
{
public:
    Score();
    void AddScore(int newPoints);
    void Draw(glm::vec2 location);
    int Getscore();
private:
    void RenderText();
    unsigned int combo;
    unsigned int score;
    GLText scoreTexture;
    std::array<int,4> score_count;
};