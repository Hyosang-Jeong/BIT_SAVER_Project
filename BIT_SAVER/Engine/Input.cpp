/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Purpose: Interface between doodle and our engine
Project: CS230
Author: Hyosang Jung
Creation date: 2021-03-07
-----------------------------------------------------------------*/
#include"Input.h"
#include"Engine.h"  //GetInput
InputKey::InputKey(Keyboard button)
{
	InputKey::button = button;
}

bool InputKey::IsKeyDown() const
{
	return Engine::GetInput().IsKeyDown(button);
}

bool InputKey::IsKeyReleased() const
{
	return Engine::GetInput().IsKeyReleased(button);
}

Input::Input()
{
	keyDown.resize(static_cast<size_t>(InputKey::Keyboard::Count));
	wasKeyDown.resize(static_cast<size_t>(InputKey::Keyboard::Count));
}

void Input::Update()
{
	wasKeyDown = keyDown;
}

bool Input::IsKeyDown(InputKey::Keyboard key) const
{
	return keyDown[static_cast<int>(key)];
}

bool Input::IsKeyReleased(InputKey::Keyboard key) const
{
	if (keyDown[static_cast<int>(key)] == false && wasKeyDown[static_cast<int>(key)] == true)
	{
		return true;
	}
	return false;
}

void  Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	keyDown[static_cast<int>(key)] = value;
}