/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.cpp
Project: BIT_SAVER
Author:	Hyun Kang
-----------------------------------------------------------------*/
#include "Score.h"
#include "../Engine/Engine.h"
#include "Score Enum.h"

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
		combo++;
		break;
	case SCORE::GOOD:
		score_count[newPoints]++;
		combo++;
		break;
	case SCORE::BAD:
		score_count[newPoints]++;
		combo++;
		break;
	case SCORE::MISS:
		score_count[newPoints]++;
		combo = 0;
		return;
	default:
		break;
	}

	int combo_add( (combo / 10) );

	score += ((combo_add + 1) * (newPoints * 10));

	if (combo_add > 10)
	{
		score += (10 * (newPoints * 10));
	}
}

void Score::Draw(glm::vec2 location)
{
	//std::cout << "Combo = " << combo << "        Score= " << score<<std::endl;
	//RenderText();
	//scoreTexture.Draw(math::TranslateMatrix(math::ivec2(location.x, location.y - scoreTexture.GetSize().y)));
	const std::string font1{ font_path[MochiyPopOne] };
	const std::string font2{ font_path[PressStart] };

	constexpr glm::vec3 SHADER_COLOR(0.f, 0.f, 0.f);
	constexpr glm::vec3 SCORE_COLOR(0.7f, 0.f, 1.f);
	constexpr glm::vec3 COMBO_COLOR(1.f, 1.f, 1.f);
	constexpr glm::vec3 PERFECT_COLOR(0.2f, 0.8f, 1.f);
	constexpr glm::vec3 GOOD_COLOR(0.f, 1.f, 0.f);
	constexpr glm::vec3 BAD_COLOR(1.f, 0.f, 0.f);
	constexpr glm::vec3 MISS_COLOR(0.5f, 0.5f, 0.5f);
	constexpr float SCALE{ 1.f };
	constexpr int Y_OFFSET{ 50 };

	glm::vec2 shader_offset(4, 4);
	int offset_y{ 50 };

	Engine::GetText(font2).Draw("Score: " + std::to_string(score), location.x + shader_offset.x, location.y + shader_offset.y, SCALE, SHADER_COLOR);
	Engine::GetText(font2).Draw("Score: " + std::to_string(score), location.x, location.y, SCALE, SCORE_COLOR);

	Engine::GetText(font2).Draw("Combo: " + std::to_string(combo), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
	Engine::GetText(font2).Draw("Combo: " + std::to_string(combo), location.x, location.y + offset_y, SCALE, COMBO_COLOR);
	offset_y += Y_OFFSET;

#ifdef _DEBUG

	Engine::GetText(font2).Draw("Perfect: " + std::to_string(score_count[static_cast<int>(SCORE::PERFECT)]), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
	Engine::GetText(font2).Draw("Perfect: " + std::to_string(score_count[static_cast<int>(SCORE::PERFECT)]), location.x, location.y + offset_y, SCALE, PERFECT_COLOR);
	offset_y += Y_OFFSET;

	Engine::GetText(font2).Draw("Good: " + std::to_string(score_count[static_cast<int>(SCORE::GOOD)]), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
	Engine::GetText(font2).Draw("Good: " + std::to_string(score_count[static_cast<int>(SCORE::GOOD)]), location.x, location.y + offset_y, SCALE, GOOD_COLOR);
	offset_y += Y_OFFSET;

	Engine::GetText(font2).Draw("Bad: " + std::to_string(score_count[static_cast<int>(SCORE::BAD)]), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
	Engine::GetText(font2).Draw("Bad: " + std::to_string(score_count[static_cast<int>(SCORE::BAD)]), location.x, location.y + offset_y, SCALE, BAD_COLOR);
	offset_y += Y_OFFSET;

	Engine::GetText(font2).Draw("Miss: " + std::to_string(score_count[static_cast<int>(SCORE::MISS)]), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
	Engine::GetText(font2).Draw("Miss: " + std::to_string(score_count[static_cast<int>(SCORE::MISS)]), location.x, location.y + offset_y, SCALE, MISS_COLOR);

#endif // DEBUG
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

std::array<int, 4> Score::GetscoreCount()
{
	return score_count;
}
