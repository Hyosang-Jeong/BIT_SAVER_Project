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
#include"../Objects/Hero.h"
#include"../Objects/Track.h"
#include"../Objects/Notes.h"
#include"../Objects/Boss.h"
#include"../Objects/Note_collisionBox.h"
#include"../Objects/Background.h"
#include"../Levels/State.h"
#include "../Objects/EnergyBar.h"
#include "../Objects/stage_bar.h"
#include"../../Engine/Sprite/GameParticles.h"
#include"../Objects/Score.h"
#include"../Objects/fever.h"
#include"../Objects/CheckBox.h"
#include"../Levels/Option.h"
Level1::Level1() :
	escape(InputKey::Keyboard::Escape),
	camera({ 0,0 })
{
	gameObjectManager = nullptr;
	heroPtr = nullptr;
	trackPtr = nullptr;
	bossPtr = nullptr;
	notebox = nullptr;
	backPtr = nullptr;
	energyBar = nullptr;
	stageBar = nullptr;
	feverBar = nullptr;
	PcheckBox1 = nullptr;
	PcheckBox2 = nullptr;
	GcheckBox1 = nullptr;
	GcheckBox2 = nullptr;
	BcheckBox1 = nullptr;
	BcheckBox2 = nullptr;
	gamestate = LEVEL_STATE::EXTRA;
	Engine::GetMusic().Init();
}

void Level1::Load()
{

			gameObjectManager = new GameObjectManager();
			heroPtr = new Hero({ -4,-5 });
			backPtr = new Background();
			trackPtr = new Track(Music::SOUND_NUM::REWIND);
			notebox = new Note_box({ -4,0 });
			bossPtr = new Boss({ 15,-5 });
			energyBar = new EnergyBar({ -4,1.2 });

			PcheckBox1 = new CheckBox({ -4.4,0 }, 0);
			PcheckBox2 = new CheckBox({ -3.2,0 }, 0);
			GcheckBox1 = new CheckBox({ -4.6,0 }, 1);
			GcheckBox2 = new CheckBox({ -2.6,0 }, 1);
			BcheckBox1 = new CheckBox({ -4.8,0 }, 2);
			BcheckBox2 = new CheckBox({ -2.0,0 }, 2);

			stageBar = new Stage_bar({ -10,9 }, 204, 82);   // total music time 204  ,  extra time 82


			backPtr->Add(texture_path[Background_1], 0);
			backPtr->Add(texture_path[Parallax1_5], 0.5);
			backPtr->Add(texture_path[Parallax1_4], 0.8);
			backPtr->Add(texture_path[Parallax1_3], 1.1);
			backPtr->Add(texture_path[Parallax1_2], 1.3);
			backPtr->Add(texture_path[Parallax1_1], 1.5);

			AddGSComponent(gameObjectManager);
			AddGSComponent(backPtr);

			gameObjectManager->Add(heroPtr);
			gameObjectManager->Add(notebox);
			gameObjectManager->Add(bossPtr);
			gameObjectManager->Add(energyBar);

			gameObjectManager->Add(PcheckBox1);
			gameObjectManager->Add(PcheckBox2);
			gameObjectManager->Add(GcheckBox1);
			gameObjectManager->Add(GcheckBox2);
			gameObjectManager->Add(BcheckBox1);
			gameObjectManager->Add(BcheckBox2);

			gameObjectManager->Add(stageBar);
			gameObjectManager->Add(trackPtr);
			AddGSComponent(new HitEmitter());
			AddGSComponent(new PerfectEmitter());
			AddGSComponent(new GoodEmitter());
			AddGSComponent(new BadEmitter());
			AddGSComponent(new MissEmitter());
			AddGSComponent(new Score());

}

void Level1::Update(double dt)
{
	if (!Engine::GetMusic().isPlaying(Music::SOUND_NUM::REWIND))
		Engine::GetMusic().Play(Music::SOUND_NUM::REWIND);
	
	GetGSComponent<Background>()->Update(dt);
	gameObjectManager->UpdateAll(dt);

	if (stageBar->Getchangeflag() == 1)
	{
		gamestate = LEVEL_STATE::GENERATING;
		Engine::GetMusic().Pause(Music::SOUND_NUM::REWIND);
		bossPtr->GenerateBoss();
		trackPtr->SetUpdate(false);
		stageBar->SetUpdate(false);
		Engine::GetMusic().Play(Music::SOUND_NUM::BOSS_ENTRANCE);
		Engine::GetMusic().volumeUp(Music::SOUND_NUM::BOSS_ENTRANCE);
	}
	if (gamestate == LEVEL_STATE::GENERATING && bossPtr->GetVelocity().x == 0)
	{
		Engine::GetMusic().Resume(Music::SOUND_NUM::REWIND);
		Engine::GetMusic().pitchUp(Music::SOUND_NUM::REWIND);
		trackPtr->SetUpdate(true);
		stageBar->SetUpdate(true);

		feverBar = new Fever_bar({ -20,-9 });
		gameObjectManager->Add(feverBar);
		gamestate = LEVEL_STATE::FINISH;
	}

	if (energyBar->Isgameover() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Gameover));
	}
	
	if (Engine::GetMusic().isPlaying(Music::SOUND_NUM::REWIND) == false)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Clear));
	}
	if (escape.IsKeyDown() == true)
	{
	    Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Offset));
	}

}

void Level1::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	GetGSComponent<Background>()->Draw(camera.GetMatrix());
	GetGSComponent<Score>()->Draw({ 0,100 });
	gameObjectManager->DrawAll(camera.GetMatrix());
}


void Level1::Unload()
{
		heroPtr = nullptr;
		trackPtr = nullptr;
		notebox = nullptr;
		bossPtr = nullptr;
		backPtr = nullptr;
		energyBar = nullptr;
		stageBar = nullptr;
		gameObjectManager->Unload();
		Engine::GetMusic().Stop(Music::SOUND_NUM::REWIND);
		ClearGSComponent();
}
