/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.h
Project: BIT_SAVER
Author:	Hyun Kang
-----------------------------------------------------------------*/
#pragma once
#include "..\..\Engine\Sprite\Texture.h" 
#include "..\Engine\Component.h" 

class Score : public Component
{
public:
    Score();
    void AddScore(int newPoints);
    void Draw(glm::vec2 location);
    int Getscore();
    std::array<int, 4> GetscoreCount();
private:
    void RenderText();
    unsigned int combo;
    unsigned int score;
    std::array<int,4> score_count;
};