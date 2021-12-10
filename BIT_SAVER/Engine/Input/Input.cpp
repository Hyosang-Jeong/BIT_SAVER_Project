/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Purpose: Interface between doodle and our engine
Project: BIT_SAVER
Author:  Hyosang Jung 

-----------------------------------------------------------------*/
#include"Input.h"
#include"..\Engine.h"  //GetInput
InputKey::InputKey(Keyboard button)
{
	InputKey::button = button;
}
InputKey::InputKey(Mouse button)
{
    InputKey::mouseButton = button;
}
bool InputKey::IsKeyDown() const
{
	return Engine::GetInput().IsKeyDown(button);
}
bool InputKey::IsKeyReleased() const
{
	return Engine::GetInput().IsKeyReleased(button);
}
bool InputKey::IsKeyReapeated() const
{
    return Engine::GetInput().IsKeyReapeated(button);
}
bool InputKey::MouseIsKeyDown() const {
    return Engine::GetInput().MouseIsKeyDown(mouseButton);
}
bool InputKey::MouseIsKeyReleased() const {
    return Engine::GetInput().MouseIsKeyReleased(mouseButton);
}
bool InputKey::MouseIsKeyReapeated() const {
    return Engine::GetInput().MouseIsKeyReapeated(mouseButton);
}


Input::Input()
{
	keyDown.resize(static_cast<size_t>(InputKey::Keyboard::Count));
	wasKeyDown.resize(static_cast<size_t>(InputKey::Keyboard::Count));
	mouseKeyDown.resize(static_cast<size_t>(InputKey::Mouse::Count));
	mouseWasKeyDown.resize(static_cast<size_t>(InputKey::Mouse::Count));
}

void Input::Update()
{
	wasKeyDown = keyDown;
	mouseWasKeyDown = mouseKeyDown;
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

bool Input::IsKeyReapeated(InputKey::Keyboard key) const
{
    if (keyDown[static_cast<int>(key)] == true && wasKeyDown[static_cast<int>(key)] == true)
    {
	return true;
    }
    return false;
}

void  Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	keyDown[static_cast<int>(key)] = value;
}

void Input::SetLastpressedButton(InputKey::Keyboard key)
{
	button = key;
}

bool Input::MouseIsKeyDown(InputKey::Mouse key) const {
    return mouseKeyDown[static_cast<int>(key)];
}

bool Input::MouseIsKeyReleased(InputKey::Mouse key) const {
    return mouseKeyDown[static_cast<int>(key)] == false && mouseWasKeyDown[static_cast<int>(key)] == true;
}

bool Input::MouseIsKeyReapeated(InputKey::Mouse key) const {
    return mouseKeyDown[static_cast<int>(key)] == true && mouseWasKeyDown[static_cast<int>(key)] == true;
}

void Input::MouseSetKeyDown(InputKey::Mouse key, bool value) {
    mouseKeyDown[static_cast<int>(key)] = value;
}

void Input::MouseSetPosition(glm::vec2 newPosition) {
    mousePosition = newPosition;
}

glm::vec2 Input::MouseGetPosition() const {
    return mousePosition;
}

void Input::MouseUpdate() {
    mouseWasKeyDown = mouseKeyDown;
}

InputKey::Keyboard Input::GetLastPressedButton()
{
	return button;
}
