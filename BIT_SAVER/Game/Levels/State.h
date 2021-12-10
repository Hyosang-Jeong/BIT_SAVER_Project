/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: State.h
Project: BIT_SAVER
Author:	Jaewoo Choi, Hyun Kang, Hyosang Jung, Sunwoo Lee
-----------------------------------------------------------------*/
#pragma once

enum class State {
	Splash,
	MainMenu,
	MainOption,
	Tutorial,
	Level0,
	Level1,
	Level2,
	Level3,
	Offset,
	Option,
	Clear,
	Gameover
};