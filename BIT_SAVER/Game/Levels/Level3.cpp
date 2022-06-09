/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level3.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Sunwoo Lee

-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Level3.h"
#include"../Objects/Hero.h"
#include"../Objects/Track.h"
//#include"../Objects/Notes.h"
#include"../Objects/Boss.h"
#include"../Objects/Note_collisionBox.h"
#include"../Objects/Background.h"
#include"../Levels/State.h"
#include "../Objects/EnergyBar.h"
#include "../Objects/EnergyBarContainer.h"
#include "../Objects/stage_bar.h"
#include"../../Engine/Sprite/GameParticles.h"
#include"../Objects/Score.h"
#include"../Objects/fever.h"
#include"../Objects/CheckBox.h"
#include"../Levels/Option.h"
#include"../../Engine/Physics/Camera.h"
#include"../Levels/Clear.h"

Level3::Level3() :
	escape(InputKey::Keyboard::Escape)
{
	gameObjectManager = nullptr;
	heroPtr = nullptr;
	trackPtr = nullptr;
	bossPtr = nullptr;
	notebox = nullptr;
	backPtr = nullptr;
	energyBar = nullptr;
	energyBarContainer = nullptr;
	stageBar = nullptr;
	feverBar = nullptr;
	PcheckBox1 = nullptr;
	PcheckBox2 = nullptr;
	GcheckBox1 = nullptr;
	GcheckBox2 = nullptr;
	BcheckBox1 = nullptr;
	BcheckBox2 = nullptr;
	gamestate = LEVEL3_STATE::EXTRA;
	doonce = true;
}

void Level3::Load()
{
	isMusicEnd = false;
	gameObjectManager = new GameObjectManager();
	heroPtr = new Hero({ -6,-5 });
	backPtr = new Background();
	trackPtr = new Track(SOUND_NUM::ENERGY);
	notebox = new Note_box({ -4,0 });
	bossPtr = new Boss({ 15,-5 });
	energyBar = new EnergyBar({ -7.5,7.5 });
	energyBarContainer = new EnergyBarContainer({ -7.5,7.5 });
	camera = new Camera({ 0,0 });
	PcheckBox1 = new CheckBox({ -4.4,0 }, 0);
	PcheckBox2 = new CheckBox({ -3.2,0 }, 0);
	GcheckBox1 = new CheckBox({ -4.6,0 }, 1);
	GcheckBox2 = new CheckBox({ -2.6,0 }, 1);
	BcheckBox1 = new CheckBox({ -4.8,0 }, 2);
	BcheckBox2 = new CheckBox({ -2.0,0 }, 2);

	stageBar = new Stage_bar({ -10,9 }, 163, 104);   // total music time 204  ,  extra time 82


	backPtr->Add(texture_path[Background_1_10], 0);
	backPtr->Add(texture_path[Background_1_9], 0);
	backPtr->Add(texture_path[Background_1_8], 0.0005);
	backPtr->Add(texture_path[Background_1_7], 0.0015);
	backPtr->Add(texture_path[Background_1_6], 0.007);
	backPtr->Add(texture_path[Background_1_5], 0.022);
	backPtr->Add(texture_path[Background_1_4], 0.05);
	backPtr->Add(texture_path[Background_1_3], 0.1);
	backPtr->Add(texture_path[Background_1_2], 0.5);
	backPtr->Add(texture_path[Background_1_1], 0.8);

	AddGSComponent(gameObjectManager);
	AddGSComponent(backPtr);
	AddGSComponent(camera);
	gameObjectManager->Add(heroPtr);
	gameObjectManager->Add(notebox);
	gameObjectManager->Add(bossPtr);
	gameObjectManager->Add(energyBar);
	gameObjectManager->Add(energyBarContainer);

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
	GetGSComponent<Camera>()->zoom_effect({ 2.f,2.f });
}

void Level3::Update(double dt)
{
	if (doonce)
	{
		Engine::GetGameStateManager().ReloadState();
		doonce = false;
	}

	gameObjectManager->UpdateAll(dt);
    if (!Engine::GetMusic().isPlaying(SOUND_NUM::ENERGY) && isMusicEnd == false)
    {
	Engine::GetMusic().Play(SOUND_NUM::ENERGY);
	Engine::GetMusic().pitchDefault(SOUND_NUM::ENERGY);
	isMusicEnd = true;
    }

	GetGSComponent<Background>()->Update(dt);
	GetGSComponent<Camera>()->Update({ 0,0 }, dt);

	if (stageBar->Getchangeflag() == 1)
	{
		gamestate = LEVEL3_STATE::GENERATING;
		Engine::GetMusic().Pause(SOUND_NUM::ENERGY);
		bossPtr->GenerateBoss();
		trackPtr->SetUpdate(false);
		stageBar->SetUpdate(false);
		Engine::GetMusic().Play(SOUND_NUM::BOSS_ENTRANCE);
		Engine::GetMusic().volumeUp(SOUND_NUM::BOSS_ENTRANCE);
	}
	if (gamestate == LEVEL3_STATE::GENERATING && bossPtr->GetVelocity().x == 0)
	{
		Engine::GetMusic().Resume(SOUND_NUM::ENERGY);
		Engine::GetMusic().pitchUp(SOUND_NUM::ENERGY);
		trackPtr->SetUpdate(true);
		stageBar->SetUpdate(true);

		feverBar = new Fever_bar({ -20,-9 });
		gameObjectManager->Add(feverBar);
		gamestate = LEVEL3_STATE::FINISH;
	}

	if (energyBar->Isgameover() == true)
	{
		heroPtr->die();
	}

	if (Engine::GetMusic().isPlaying(SOUND_NUM::ENERGY) == false)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Clear));
		static_cast<Clear*>(Engine::GetGameStateManager().Find("Clear"))->Setstats("Energy", GetGSComponent<Score>()->Getscore(), GetGSComponent<Score>()->GetscoreCount());

	}
	if (escape.IsKeyDown() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Option));
	}

}

void Level3::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	GetGSComponent<Background>()->Draw(camera->GetMatrix());
	GetGSComponent<Score>()->Draw({ 0,200 });
	gameObjectManager->DrawAll(camera->GetMatrix());
}


void Level3::Unload()
{
	heroPtr = nullptr;
	trackPtr = nullptr;
	notebox = nullptr;
	bossPtr = nullptr;
	backPtr = nullptr;
	energyBar = nullptr;
	energyBarContainer = nullptr;
	stageBar = nullptr;
	if (Engine::GetMusic().isPlaying(SOUND_NUM::ENERGY) == true)
	{
	    Engine::GetMusic().pitchDefault(SOUND_NUM::ENERGY);
	    Engine::GetMusic().Stop(SOUND_NUM::ENERGY);
	}

	Engine::GetMusic().isPlaying(SOUND_NUM::ENERGY);
	ClearGSComponent();
}
