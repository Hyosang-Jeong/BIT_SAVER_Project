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
#include"..\Objects\Bunny.h"
#include"..\Objects\Track.h"
#include"..\..\Engine\Music\Midi.h"
#include"..\Objects\Note_collisionBox.h"
#include<map>

Level1::Level1() : mainMenu(InputKey::Keyboard::Escape),
reload(InputKey::Keyboard::R), heroPtr(nullptr), bunnyPtr(nullptr)
{}

void Level1::Load()
{
	MidiEvent m;

	heroPtr = new Hero({ -6,0 });

	std::map<int, std::vector<long double>> mid_info;

	mid_info = m.MidiSetUp(Engine::GetMusic().MUSIC_CANON);

	Engine::GetGameStateManager().gameObjectManager.Add(heroPtr);

	Engine::GetGameStateManager().gameObjectManager.Add(new Note_box({-4,0}));

	Engine::GetGameStateManager().gameObjectManager.Add(new Track(mid_info));

}
void Level1::Update(double dt)
{
	Engine::GetGameStateManager().gameObjectManager.UpdateAll(dt);

#ifdef _DEBUG
	if (reload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#endif


}

void Level1::Unload()
{
	Engine::GetGameStateManager().gameObjectManager.Unload();
	heroPtr = nullptr;
}

void Level1::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Engine::GetGameStateManager().gameObjectManager.DrawAll();
}