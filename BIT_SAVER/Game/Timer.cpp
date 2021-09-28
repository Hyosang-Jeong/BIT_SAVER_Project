/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/01/2021
-----------------------------------------------------------------*/
#include"Timer.h"
#include "Fonts.h"  //Font1
#include "../Engine/Engine.h"  //GetSpriteFont

Timer::Timer(int time): timer(time)
{
	timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Time: " + std::to_string(timer), 0xFFFFFFFF, true);
}

void Timer::Update(double dt)
{
	int current_time = static_cast<int>(timer);
	timer -= dt;
	if (current_time != static_cast<int>(timer))
	{
		timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Time: " + std::to_string(static_cast<int>(timer + 1)), 0xFFFFFFFF, true);
	}
}

void Timer::Draw(math::ivec2 location)
{
	timeTexture.Draw(math::TranslateMatrix(math::ivec2(location.x - timeTexture.GetSize().x, location.y - timeTexture.GetSize().y)));
}

bool Timer::hasEnded()
{
	if(timer<=0.01)
	{
		return true;
	}
	else
	{
		return false;
	}
}
