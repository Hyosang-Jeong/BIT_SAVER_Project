/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.h
Project: CS230
Author: Hyosang Jung
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "..\Engine\GameState.h" // CS230::GameState
#include "..\Engine\GameObjectManager.h" // gameobjectmanager
#include"../Engine/TransformMatrix.h"
class Ship;

class Level2 : public CS230::GameState {
public:
	Level2();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	std::string GetName() override { return "Level2"; }
private:
	Ship* shipPtr;

	CS230::Texture GameOverTexture;
	CS230::Texture RestartTexture;

	CS230::InputKey mainMenu;
	CS230::InputKey reload;
	CS230::GameObjectManager* gameObjectManager;
	math::TransformMatrix camera;
};
