///*--------------------------------------------------------------
//Copyright (C) 2021 DigiPen Institute of Technology.
//Reproduction or disclosure of this file or its contents without the prior
//written consent of DigiPen Institute of Technology is prohibited.
//File Name: Input_Doodle.cpp
//Purpose: Interface between doodle and our engine
//Project: CS230
//Author: Hyosang Jung
//Creation date: 2021-03-06
//-----------------------------------------------------------------*/
//#include <doodle/input.hpp>	
//#include "Input.h"
//#include "Engine.h"			// GetLogger, GetInput
//#include<GLFW/glfw3.h>
//CS230::InputKey::Keyboard DoodleKeyToCS230Key(int key)
//{
//	if (key == GLFW_KEY_DOWN)
//	{
//		return CS230::InputKey::Keyboard::Down;
//	}
//	if (key == GLFW_KEY_UP)
//	{
//		return CS230::InputKey::Keyboard::Up;
//	}
//	if (key == GLFW_KEY_RIGHT)
//	{
//		return CS230::InputKey::Keyboard::Right;
//	}
//	if (key == GLFW_KEY_LEFT)
//	{
//		return CS230::InputKey::Keyboard::Left;
//	}
//
//	return CS230::InputKey::Keyboard::None;
//}
//
//void on_key_pressed(doodle::KeyboardButtons doodleButton) {
//	//	CS230::InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
//	CS230::InputKey::Keyboard button = CS230::InputKey::Keyboard::None;
//	if (doodleButton == doodle::KeyboardButtons::Down)
//	{
//		int key = static_cast<int>(GLFW_KEY_DOWN);
//		button = DoodleKeyToCS230Key(key);
//	}
//	if (button != CS230::InputKey::Keyboard::None)
//	{
//		Engine::GetLogger().LogDebug("on_key_pressed");
//		Engine::GetInput().SetKeyDown(button, true);
//	}
//}
//
////void on_key_released(doodle::KeyboardButtons doodleButton) {
////	CS230::InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
////	if (button != CS230::InputKey::Keyboard::None)
////	{
////		Engine::GetLogger().LogDebug("on_key_released");
////		Engine::GetInput().SetKeyDown(button, false);
////	}
////}


/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input_Doodle.cpp
Purpose: Interface between doodle and our engine
Project: CS230
Author: Hyosang Jung
Creation date: 2021-03-06
-----------------------------------------------------------------*/
#include <doodle/input.hpp>	
#include "Input.h"
#include "Engine.h"			// GetLogger, GetInput

CS230::InputKey::Keyboard DoodleKeyToCS230Key(doodle::KeyboardButtons button) {
	if (button == doodle::KeyboardButtons::Enter) {
		return CS230::InputKey::Keyboard::Enter;
	}
	else if (button == doodle::KeyboardButtons::Escape) {
		return CS230::InputKey::Keyboard::Escape;
	}
	else if (button == doodle::KeyboardButtons::Space) {
		return CS230::InputKey::Keyboard::Space;
	}
	else if (button == doodle::KeyboardButtons::Left) {
		return CS230::InputKey::Keyboard::Left;
	}
	else if (button == doodle::KeyboardButtons::Right) {
		return CS230::InputKey::Keyboard::Right;
	}
	else if (button == doodle::KeyboardButtons::Up) {
		return CS230::InputKey::Keyboard::Up;
	}
	else if (button == doodle::KeyboardButtons::Down) {
		return CS230::InputKey::Keyboard::Down;
	}
	else if (button == doodle::KeyboardButtons::Tilde) {
		return CS230::InputKey::Keyboard::tilde;
	}
	else if (button >= doodle::KeyboardButtons::A && button <= doodle::KeyboardButtons::Z) {
		int offset = static_cast<int>(button) - static_cast<int>(doodle::KeyboardButtons::A);
		return static_cast<CS230::InputKey::Keyboard>(static_cast<int>(CS230::InputKey::Keyboard::A) + offset);
	}
	return CS230::InputKey::Keyboard::None;
}

void on_key_pressed(doodle::KeyboardButtons doodleButton) {
	CS230::InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
	if (button != CS230::InputKey::Keyboard::None)
	{
		Engine::GetLogger().LogDebug("on_key_pressed");
		Engine::GetInput().SetKeyDown(button, true);
	}
}

void on_key_released(doodle::KeyboardButtons doodleButton) {
	CS230::InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
	if (button != CS230::InputKey::Keyboard::None)
	{
		Engine::GetLogger().LogDebug("on_key_released");
		Engine::GetInput().SetKeyDown(button, false);
	}
}
