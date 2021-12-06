/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.h
Project: BIT_SAVER
Author: 
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include "..\Engine\GameObject\GameObjectManager.h" // gameobjectmanager
#include"..\Engine\Input\Input.h"  //input key
#include"..\..\Engine\Physics\Camera.h"
#include"../../Engine/Sprite/Texture.h"
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


enum class STATE
{
	EXTRA,
	GENERATING,
	OPTION,
	FINISH
};

class Level1 : public GameState
{
public:
	Level1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() { return "Level1"; }
	void Draw() override;
	
private:
	InputKey escape;
	InputKey tilt;

	Hero* heroPtr;
	Boss* bossPtr;
	Track* trackPtr;
	Note_box* notebox;
	Background* backPtr;
	EnergyBar* energyBar;
	Stage_bar* stageBar;
	Fever_bar* feverBar;
	CheckBox* PcheckBox1;
	CheckBox* PcheckBox2;
	CheckBox* GcheckBox1;
	CheckBox* GcheckBox2;
	CheckBox* BcheckBox1;
	CheckBox* BcheckBox2;
	Camera camera;
	GameObjectManager* gameObjectManager;
	STATE gamestate;
	//GLText* text;
	bool a = false;
};
