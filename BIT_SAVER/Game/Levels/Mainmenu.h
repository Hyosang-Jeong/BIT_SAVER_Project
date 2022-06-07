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
	OPTION,
	ESCAPE
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
	void play_music(int num);
	void stop_music(int num);
	void difficulty_select();
	InputKey Next;
	InputKey Previous;
	InputKey Right;
	InputKey Left;
	InputKey Select;
	InputKey escape;
	InputKey T;
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
	Texture* LP;
	Texture* LP_2;
	Texture* Quit_screen;
	float alpha = 0;
	float text_alpha = 0;
	int currstate;
	double timer = 0;
	double lp_rotate=0;
	bool escape_game;
	bool is_selected;
	int previous_state;
	glm::vec2 updown_pos;

};

