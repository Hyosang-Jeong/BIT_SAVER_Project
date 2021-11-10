/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/01/2021
-----------------------------------------------------------------*/
#include "Score.h"
#include "../Engine/Engine.h"

Score::Score() :
score(0),combo(0)
{}

void Score::AddScore(int newPoints)
{
	combo++;
	if (newPoints == 0)
	{
		combo = 0;
	}

	score += (combo *newPoints);
}

void Score::Draw([[maybe_unused]]glm::vec2 location)
{
	//std::cout << "Combo = " << combo << "        Score= " << score<<std::endl;
	//RenderText();
	//scoreTexture.Draw(math::TranslateMatrix(math::ivec2(location.x, location.y - scoreTexture.GetSize().y)));
}

void Score::RenderText()
{
	//std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);

	//if (fontToUse == Fonts::Font1)
	//{
	//	scoreTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
	//}
	//else
	//{
	//	scoreTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, false);
	//}
}

int Score::Getscore()
{
	return score;
}