/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Level2.h"
#include "Fonts.h" //font2
#include"Ship.h"
#include"Level1.h"  // Level1::floor
#include"Meteor.h" //Meteor
#include "Score.h"
#include "Screens.h" //SCREEN
#include"../Engine/ShowCollision.h" //ShowCollision
#include"GameParticles.h"
#include"EnemyShip.h"
Level2::Level2() : mainMenu(CS230::InputKey::Keyboard::Escape), reload(CS230::InputKey::Keyboard::R),gameObjectManager(nullptr),shipPtr(nullptr) {}

void Level2::Load() 
{
	gameObjectManager = new CS230::GameObjectManager();
	AddGSComponent(gameObjectManager);
	AddGSComponent(new Score(0, Fonts::Font2));
	shipPtr = new Ship({ Engine::GetWindow().GetSize() / 2.0 });
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(shipPtr);
	gameObjectManager->Add(new EnemyShip(shipPtr));
	AddGSComponent(new MeteorBitEmitter());
	AddGSComponent(new HitEmitter());
	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, true);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, true);
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::tilde));
#endif
}


void Level2::Update(double dt) 
{
	gameObjectManager->Update(dt);

		if (mainMenu.IsKeyReleased() == true) 
		{
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}


#ifdef _DEBUG
		GetGSComponent<ShowCollision>()->Update(dt);
		if (reload.IsKeyReleased() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
#else
		if (shipPtr->IsDead() == true && reload.IsKeyReleased() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
#endif
}

void Level2::Unload() 
{
	shipPtr = nullptr;
	ClearGSComponent();
}

void Level2::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	gameObjectManager->DrawAll(camera);
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, Engine::GetWindow().GetSize().y - 5 });

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	if (shipPtr->IsDead() == true)
	{
		GameOverTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, winSize.y/2 + GameOverTexture.GetSize().y / 2 }));
		RestartTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - RestartTexture.GetSize().x / 2, winSize.y / 2 - GameOverTexture.GetSize().y / 2 }));
	}
}
