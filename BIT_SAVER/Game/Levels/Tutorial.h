/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tutorial.h
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang 

-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include "..\Engine\GameObject\GameObjectManager.h" // gameobjectmanager
#include"..\Engine\Input\Input.h"  //input key
#include"..\..\Engine\Physics\Camera.h"
#include"../../Engine/Sprite/Texture.h"
#include "../../Engine/Music/Sound_Num.h"

class Tutorial_Helper;
class Hero;
class Boss;
class Track;
class Note_box;
class Background;
class EnergyBar;
class Stage_bar;
class GLText;
class Fever_bar;
class CheckBox;


enum class TUTO_LEVEL_STATE
{
	EXTRA,
	GENERATING,
	OPTION,
	FINISH
};

enum class Tuto_Helper_Enum
{
	GREETINGS,
	UP_NOTE_GENERATE,
	UP_NOTE_HIT,
	DOWN_NOTE_GENERATE,
	DOWN_NOTE_HIT,
	END
};

class Tutorial : public GameState
{
public:
	Tutorial();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() { return "Tutorial"; }
	void Draw() override;
private:
	void Update_currstate(double dt);
	InputKey escape;
	Hero* heroPtr;
	Boss* bossPtr;
	Track* trackPtr;
	Note_box* notebox;
	Background* backPtr;
	EnergyBar* energyBar;
	Stage_bar* stageBar;
	Fever_bar* feverBar;
	Camera camera;
	GameObjectManager* gameObjectManager;
	TUTO_LEVEL_STATE gamestate;
	Tuto_Helper_Enum currstate;
	bool isMusicEnd;
};
