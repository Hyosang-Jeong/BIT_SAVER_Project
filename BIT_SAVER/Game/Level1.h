/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.h
Project: CS230
Author: Hyosang Jung
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "..\Engine\GameState.h" // CS230::GameState
#include "..\Engine\Texture.h"   // Texture background
#include"Background.h" //background object
#include"..\Engine\Camera.h" //camera
#include "..\Engine\GameObjectManager.h" // gameobjectmanager
#include"..\Engine\Input.h"  //input key
#include"Floor.h" //floor
class Hero;
class Level1 : public CS230::GameState {
public:
	Level1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() { return "Level1"; }
	void Draw() override;
private:
	static constexpr double floor = 126.0f;
	CS230::InputKey mainMenu;
	CS230::InputKey reload;
	
	Background* background;
	CS230::GameObjectManager *gameObjectManager;
	Hero* heroPtr;

	int lives;
	CS230::Texture livesTexture;
};
