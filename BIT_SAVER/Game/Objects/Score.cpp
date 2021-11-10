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
#include "Notes.h"


Score::Score()
{
	score = 0;
	combo = 0;
	score_count = {0,0,0,0};
}

void Score::AddScore(int newPoints)
{
	switch (static_cast<SCORE>(newPoints))
	{
	case SCORE::PERFECT:
		score_count[newPoints]++;
		break;
	case SCORE::GOOD:
		score_count[newPoints]++;
		break;
	case SCORE::BAD:
		score_count[newPoints]++;
		break;
	case SCORE::MISS:
		score_count[newPoints]++;
		break;
	default:
		break;
	}

	combo++;
	if (newPoints == 0)
	{
		combo = 0;
	}

	score += (combo *newPoints);
}

void Score::Draw(glm::vec2 location)
{
	//std::cout << "Combo = " << combo << "        Score= " << score<<std::endl;
	//RenderText();
	//scoreTexture.Draw(math::TranslateMatrix(math::ivec2(location.x, location.y - scoreTexture.GetSize().y)));

	scoreTexture.Draw("Score: " + std::to_string(score), location.x+5, location.y+5, 1.f, glm::vec3(0.f, 0.f, 0.f));
	scoreTexture.Draw("Score: " + std::to_string(score), location.x, location.y, 1.f, glm::vec3(1.f,1.f,1.f));

	scoreTexture.Draw("Perfect: " + std::to_string(score_count[static_cast<int>(SCORE::PERFECT)]), location.x + 5, location.y + 5 + 50, 1.f, glm::vec3(0.f, 0.f, 0.f));
	scoreTexture.Draw("Perfect: " + std::to_string(score_count[static_cast<int>(SCORE::PERFECT)]), location.x, location.y + 50, 1.f, glm::vec3(1.f, 1.f, 1.f));

	scoreTexture.Draw("Good: " + std::to_string(score_count[static_cast<int>(SCORE::GOOD)]), location.x + 5, location.y + 5 + 100, 1.f, glm::vec3(0.f, 0.f, 0.f));
	scoreTexture.Draw("Good: " + std::to_string(score_count[static_cast<int>(SCORE::GOOD)]), location.x, location.y + 100, 1.f, glm::vec3(1.f, 1.f, 1.f));

	scoreTexture.Draw("Bad: " + std::to_string(score_count[static_cast<int>(SCORE::BAD)]), location.x + 5, location.y + 5 + 150, 1.f, glm::vec3(0.f, 0.f, 0.f));
	scoreTexture.Draw("Bad: " + std::to_string(score_count[static_cast<int>(SCORE::BAD)]), location.x, location.y + 150, 1.f, glm::vec3(1.f, 1.f, 1.f));

	scoreTexture.Draw("Miss: " + std::to_string(score_count[static_cast<int>(SCORE::MISS)]), location.x + 5, location.y + 5 + 200, 1.f, glm::vec3(0.f, 0.f, 0.f));
	scoreTexture.Draw("Miss: " + std::to_string(score_count[static_cast<int>(SCORE::MISS)]), location.x, location.y + 200, 1.f, glm::vec3(1.f, 1.f, 1.f));

	scoreTexture.Draw("Combo: " + std::to_string(combo), location.x + 5, location.y + 5 + 250, 1.f, glm::vec3(0.f, 0.f, 0.f));
	scoreTexture.Draw("Combo: " + std::to_string(combo), location.x, location.y + 250, 1.f, glm::vec3(1.f, 1.f, 1.f));
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