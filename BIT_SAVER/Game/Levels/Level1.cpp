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
#include"..\Objects\Hero.h"
#include"..\Objects\Bunny.h"
#include"..\Objects\Track.h"
#include<map>
#include"..\..\Engine\Music\Midi.h"
//#include"Screens.h" //Screens::Level2
//#include"Hero.h" // add Hero
//#include"Ball.h" // add Ball
//#include"Bunny.h" //add bunny
//#include "Fonts.h" //Font1
//#include "Score.h" //score
//#include "Timer.h" //timer
//#include"TreeStump.h" //add TreeStump
//#include"../Engine/ShowCollision.h" //collision box
//#include"Gravity.h" //hero,ball gravity
//#include"Exit.h"
//#include"GameParticles.h"

Level1::Level1() : mainMenu(InputKey::Keyboard::Escape),
reload(InputKey::Keyboard::R), heroPtr(nullptr), bunnyPtr(nullptr)
/*background(nullptr),
),bunnyPtr(nullptr)
gameObjectManager(nullptr)
lives(3)*/
{}

void Level1::Load()
{
	MidiEvent m;
	heroPtr = new Hero({ 0,0 });
	bunnyPtr = new Bunny({ 0.5,0.5 });
	
	std::map<int, std::vector<long double>> a;
	a = m.MidiSetUp("Still_Dre.mid");


	Engine::GetGameStateManager().gameObjectManager.Add(heroPtr);
	Engine::GetGameStateManager().gameObjectManager.Add(bunnyPtr);

	for (auto& track : a)
	{
		Engine::GetGameStateManager().gameObjectManager.Add(new Track(track.first,track.second));
	}

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

	//background.Draw(camera);
	//math::TransformMatrix cameraMatrix = camera.GetMatrix();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	Engine::GetGameStateManager().gameObjectManager.DrawAll();
	//math::ivec2 winSize = Engine::GetWindow().GetSize();
	
}