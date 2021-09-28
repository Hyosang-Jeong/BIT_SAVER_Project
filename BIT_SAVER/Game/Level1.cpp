/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Level1.h"
#include"Screens.h" //Screens::Level2
#include"Hero.h" // add Hero
#include"Ball.h" // add Ball
#include"Bunny.h" //add bunny
#include "Fonts.h" //Font1
#include "Score.h" //score
#include "Timer.h" //timer
#include"TreeStump.h" //add TreeStump
#include"../Engine/ShowCollision.h" //collision box
#include"Gravity.h" //hero,ball gravity
#include"Exit.h"
#include"GameParticles.h"
Level1::Level1() : mainMenu(CS230::InputKey::Keyboard::Escape),
reload(CS230::InputKey::Keyboard::R),
heroPtr( nullptr ),
background(nullptr),
gameObjectManager(nullptr),
lives(3)
{}


void Level1::Load() 
{
	CS230::Camera* cameraPtr = new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } });
	AddGSComponent(cameraPtr);
	gameObjectManager = new CS230::GameObjectManager();
	background = new Background;
	
	AddGSComponent(gameObjectManager);
	AddGSComponent(new Score(0, Fonts::Font1));
	AddGSComponent(new Timer(60));
	AddGSComponent(new Gravity(2000));
	AddGSComponent(new SmokeEmitter());
	gameObjectManager->Add(new Ball({ 600, Level1::floor }));
	gameObjectManager->Add(new Ball({ 2700, Level1::floor }));
	gameObjectManager->Add(new Ball({ 4800, Level1::floor }));

	gameObjectManager->Add(new TreeStump({ 300, Level1::floor }, 3));
	gameObjectManager->Add(new TreeStump({ 1200, Level1::floor }, 2));
	gameObjectManager->Add(new TreeStump({ 2200, Level1::floor }, 1));
	gameObjectManager->Add(new TreeStump({ 2800, Level1::floor }, 5));
	gameObjectManager->Add(new TreeStump({ 5100, Level1::floor }, 5));
	gameObjectManager->Add(new Floor({ {0, 0}, {1471, static_cast<int>(Level1::floor)} }));
	gameObjectManager->Add(new Floor({ {1602, 0}, {4262, static_cast<int>(Level1::floor)} }));
	gameObjectManager->Add(new Floor({ {4551, 0}, {5760, static_cast<int>(Level1::floor)} }));
	gameObjectManager->Add(new Exit({ {5550, static_cast<int>(Level1::floor)}, {5760, 683} }));

	
	heroPtr = new Hero({ 100, Level1::floor - 1 });
	gameObjectManager->Add(new Bunny({ 1000, floor }, { 674, 1132 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 2000, floor }, { 1635, 2135 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 3200, floor }, { 2860, 4250 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 3800, floor }, { 2860, 4250 }, heroPtr));

	gameObjectManager->Add(heroPtr);

	AddGSComponent(background);
	
	background->Add("assets/clouds.png", 4);
	background->Add("assets/Moutains.png", 2);
	background->Add("assets/foreground.png", 1);
	cameraPtr->SetPosition(math::vec2{ 0, 0 });
	cameraPtr->SetExtent({ { 0,0 }, { background->Size() - Engine::GetWindow().GetSize() } });
	
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Lives: "+std::to_string(lives), 0xFFFFFFFF, true);
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::tilde));
#endif

}
void Level1::Update(double dt) 
{
	GetGSComponent<Timer>()->Update(dt);
	if(GetGSComponent<Timer>()->hasEnded() == true || heroPtr->IsDead() == true)
	{
		lives--;

		if(lives ==0)
		{
			lives = 3;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
		}
		else
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}
	gameObjectManager->Update(dt);
	GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());
		if (mainMenu.IsKeyReleased() == true) {

			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}
#ifdef _DEBUG
		if (reload.IsKeyReleased() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
		GetGSComponent<ShowCollision>()->Update(dt);
#endif

}

void Level1::Unload()
{
	heroPtr = nullptr;
	ClearGSComponent();
}

void Level1::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);

	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	 
	background->Draw(*cameraPtr);

	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();

	gameObjectManager->DrawAll(cameraMatrix);

	math::ivec2 winSize = Engine::GetWindow().GetSize();

	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y -  5 });
	
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x/2 - livesTexture.GetSize().x/2, winSize.y - livesTexture.GetSize().y - 5 }));
	
	GetGSComponent<Timer>()->Draw(math::ivec2{ winSize.x  - 10, winSize.y  - 5 });

}