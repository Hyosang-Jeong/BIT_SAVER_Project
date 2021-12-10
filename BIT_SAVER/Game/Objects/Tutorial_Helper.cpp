/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/01/2021
-----------------------------------------------------------------*/
#include "Tutorial_Helper.h"
#include "../Engine/Engine.h"
#include "Notes.h"

//Fever_bar::Fever_bar(glm::vec2 startPos) :
//	GameObject(startPos, glm::vec2{ 10,1 })
//{
//	fever_gazePtr = Engine::GetTextureManager().Load("../images/fever_gaze.png");
//	fever_barPtr = Engine::GetTextureManager().Load("../images/fever_gaze_bar.png");
//	fever_barModel.init({ 1, 1 });
//	score_ptr = Engine::GetGSComponent<Score>();
//	initial_score = score_ptr->Getscore();
//	is_fever_mode = false;
//}
Tutorial_Helper::Tutorial_Helper()
{
	currstate = static_cast<int>(Tuto_Helper_Enum::GREETINGS);
	helperPtr = Engine::GetTextureManager().Load("../images/extra1.png");
	textboxPtr = Engine::GetTextureManager().Load("../images/sound_bar.png");
	score_ptr = Engine::GetGSComponent<Score>();

}

void Tutorial_Helper::AddScore(int )
{
	
}

void Tutorial_Helper::Draw(glm::vec2 )
{

}

int Tutorial_Helper::Getflag()
{
	return currstate;
}

//void Tutorial_Helper::RenderText()
//{
//	const std::string font1{ font_path[MochiyPopOne] };
//	const std::string font2{ font_path[PressStart] };
//
//	constexpr glm::vec3 SHADER_COLOR(0.f, 0.f, 0.f);
//	constexpr glm::vec3 SCORE_COLOR(0.7f, 0.f, 1.f);
//	constexpr glm::vec3 PERFECT_COLOR(0.2f, 0.8f, 1.f);
//	constexpr glm::vec3 GOOD_COLOR(0.f, 1.f, 0.f);
//	constexpr glm::vec3 BAD_COLOR(1.f, 0.f, 0.f);
//	constexpr glm::vec3 MISS_COLOR(0.5f, 0.5f, 0.5f);
//	constexpr glm::vec3 COMBO_COLOR(1.f, 1.f, 1.f);
//	constexpr float SCALE{ 1.f };
//	constexpr int Y_OFFSET{ 50 };
//
//	glm::vec2 shader_offset(4, 4);
//	int offset_y{ 50 };
//
//	Engine::GetText(font2).Draw("Score: " + std::to_string(score), location.x + shader_offset.x, location.y + shader_offset.y, SCALE, SHADER_COLOR);
//	Engine::GetText(font2).Draw("Score: " + std::to_string(score), location.x, location.y, SCALE, SCORE_COLOR);
//
//	Engine::GetText(font2).Draw("Perfect: " + std::to_string(score_count[static_cast<int>(SCORE::PERFECT)]), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
//	Engine::GetText(font2).Draw("Perfect: " + std::to_string(score_count[static_cast<int>(SCORE::PERFECT)]), location.x, location.y + offset_y, SCALE, PERFECT_COLOR);
//	offset_y += Y_OFFSET;
//
//	Engine::GetText(font2).Draw("Good: " + std::to_string(score_count[static_cast<int>(SCORE::GOOD)]), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
//	Engine::GetText(font2).Draw("Good: " + std::to_string(score_count[static_cast<int>(SCORE::GOOD)]), location.x, location.y + offset_y, SCALE, GOOD_COLOR);
//	offset_y += Y_OFFSET;
//
//	Engine::GetText(font2).Draw("Bad: " + std::to_string(score_count[static_cast<int>(SCORE::BAD)]), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
//	Engine::GetText(font2).Draw("Bad: " + std::to_string(score_count[static_cast<int>(SCORE::BAD)]), location.x, location.y + offset_y, SCALE, BAD_COLOR);
//	offset_y += Y_OFFSET;
//
//	Engine::GetText(font2).Draw("Miss: " + std::to_string(score_count[static_cast<int>(SCORE::MISS)]), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
//	Engine::GetText(font2).Draw("Miss: " + std::to_string(score_count[static_cast<int>(SCORE::MISS)]), location.x, location.y + offset_y, SCALE, MISS_COLOR);
//	offset_y += Y_OFFSET;
//
//	Engine::GetText(font2).Draw("Combo: " + std::to_string(combo), location.x + shader_offset.x, location.y + shader_offset.y + offset_y, SCALE, SHADER_COLOR);
//	Engine::GetText(font2).Draw("Combo: " + std::to_string(combo), location.x, location.y + offset_y, SCALE, COMBO_COLOR);
//}