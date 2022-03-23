/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mainmenu.h
Project: BIT_SAVER
Author:	Hyun Kang
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include "..\Engine\GameObject\GameObjectManager.h" // gameobjectmanager
#include"..\Engine\Input\Input.h"  //input key
#include"..\..\Engine\Physics\Camera.h"

enum class state
{
	START =2,
	TUTORIAL,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	OPTION
};

class Mainmenu : public GameState
{
public:

	Mainmenu();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	std::string GetName() override { return "MainMenu"; }

	InputKey Next;
	InputKey Previous;
	InputKey Select;
	InputKey escape;
private:
	Texture* mainmenu;
	Texture* gamelogo;
	Texture* levels;
	Texture* option;
	Texture* option_button;
	Texture* level_1;
	Texture* level_2;
	Texture* level_3;
	Texture* level_4;
	float alpha = 0;
	int currstate;
	glm::vec2 updown_pos;
};

