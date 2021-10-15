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
#include<map>

Level1::Level1() : mainMenu(InputKey::Keyboard::Escape), camera({ 0,0 }),heroPtr(nullptr), trackPtr(nullptr)
{}

void Level1::Load()
{
	heroPtr = new Hero({ -6,0 });
	trackPtr = new Track(Music::SOUND_NUM::ENERGY);
	notebox = new Note_box({ -4,0 });
	bossPtr = new Boss({ 8,0 });

	gameObjectManager.Add(heroPtr);
	gameObjectManager.Add(bossPtr);
	gameObjectManager.Add(notebox);
	gameObjectManager.Add(trackPtr);

}
void Level1::Update(double dt)
{
	gameObjectManager.UpdateAll(dt);
	Engine::GetMusic().Play(Music::SOUND_NUM::ENERGY);
	if (trackPtr->GetNote_flag() == true) // To generate note with track's info
	{
		glm::vec2 pos = trackPtr->GetNoteinfo().first;
		glm::vec2 vel = trackPtr->GetNoteinfo().second;
		gameObjectManager.Add(new Note(pos, vel));
		trackPtr->Set_Note_flag(false);
	}
	notebox->set_attack_flag(heroPtr->Get_Attack_flag().first, heroPtr->Get_Attack_flag().second);

	camera.Dynamic_movement(notebox->GetDestroyed(),dt);
	camera.Update({ 0,0 },dt);
	if (mainMenu.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
}

void Level1::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.36f, 0.36f, 0.52f, 1.0f);
	gameObjectManager.DrawAll(camera.GetMatrix());
}
void Level1::Unload()
{
	heroPtr = nullptr;
	trackPtr = nullptr;
	notebox = nullptr;
	bossPtr = nullptr;
	gameObjectManager.Unload();
}
