/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScreenWrap.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/01/2021
-----------------------------------------------------------------*/
#include "ScreenWrap.h"
#include "../Engine/Engine.h"

void ScreenWrap::Update(double )
{
	if (object.GetPosition().x - (object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2) > Engine::GetWindow().GetSize().x)
	{
		object.SetPosition(math::vec2{ -(object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) ,object.GetPosition().y });
	}
	else if (object.GetPosition().x + (object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2) < 0)
	{
		object.SetPosition(math::vec2{ static_cast<double>(Engine::GetWindow().GetSize().x) + static_cast<double>(object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2) ,object.GetPosition().y });
	}
	else if (object.GetPosition().y - (object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) > Engine::GetWindow().GetSize().y)
	{
		object.SetPosition(math::vec2{ object.GetPosition().x  ,-(object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) });
	}
	else if (object.GetPosition().y + (object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2) < 0)
	{
		object.SetPosition(math::vec2{ object.GetPosition().x  ,static_cast<double>(Engine::GetWindow().GetSize().y) + static_cast<double>(object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2) });
	}
}