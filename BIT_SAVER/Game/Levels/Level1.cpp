/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Level1.h"
#include"..\Objects\Hero.h"
#include"..\Objects\Track.h"
#include"..\Objects\Notes.h"
#include"..\Objects\Boss.h"
#include"..\Objects\Note_collisionBox.h"
#include"..\Objects\Background.h"
#include"../Levels/State.h"

Level1::Level1() : 
mainMenu(InputKey::Keyboard::Escape), 
camera({ 0,0 })
{
	//camera = glm::vec2{ 0,0 };
	heroPtr = nullptr;
	trackPtr = nullptr;
	bossPtr = nullptr;
	notebox = nullptr;
	backPtr = nullptr;
}

void Level1::Load()
{
	Engine::GetMusic().Play(Music::SOUND_NUM::ENERGY);
	gameObjectManager = new GameObjectManager();

	heroPtr = new Hero({ -6,0 });
	backPtr = new Background();
	trackPtr = new Track(Music::SOUND_NUM::ENERGY);
	notebox = new Note_box({ -4,0 });
	bossPtr = new Boss({ 8,0 });

	backPtr->Add("../images/background1.png", 0);
	backPtr->Add("../images/parallax1-5.png", 0.5);
	backPtr->Add("../images/parallax1-4.png", 0.8);
	backPtr->Add("../images/parallax1-3.png", 1.1);
	backPtr->Add("../images/parallax1-2.png", 1.3);
	backPtr->Add("../images/parallax1-1.png", 1.5);


	AddGSComponent(gameObjectManager);
	AddGSComponent(backPtr);

	gameObjectManager->Add(heroPtr);
	gameObjectManager->Add(bossPtr);
	gameObjectManager->Add(notebox);
	gameObjectManager->Add(trackPtr);
}

void Level1::Update(double dt)
{
	GetGSComponent<Background>()->Update(dt);
	gameObjectManager->UpdateAll(dt);

	//camera.Dynamic_movement(notebox->GetDestroyed(),dt);
	//camera.Update({ 0,0 },dt);

	if (mainMenu.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
}

void Level1::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 0.5f, 1.0f, 1.0f);
	GetGSComponent<Background>()->Draw(camera.GetMatrix());
	gameObjectManager->DrawAll(camera.GetMatrix());
}

void Level1::Unload()
{
	heroPtr = nullptr;
	trackPtr = nullptr;
	notebox = nullptr;
	bossPtr = nullptr;
	backPtr = nullptr;
	Engine::GetMusic().Stop(Music::SOUND_NUM::ENERGY);
	gameObjectManager->Unload();
}
