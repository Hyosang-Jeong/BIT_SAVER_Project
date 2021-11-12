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

enum class STATE
{
	EXTRA,
	GENERATING,
	OPTION,
	FINISH
};
Level1::Level1() : 
escape(InputKey::Keyboard::Escape),
OptionUpKey(InputKey::Keyboard::Up),
OptionDownKey(InputKey::Keyboard::Down),
OptionSoundUpKey(InputKey::Keyboard::Right),
OptionSoundDownKey(InputKey::Keyboard::Left),
OptionSelectKey(InputKey::Keyboard::Enter),
isOption(false),
selectedIndex(glm::vec2{ 0,1 }),
camera({ 0,0 })
{
	//camera = glm::vec2{ 0,0 };
	gameObjectManager = nullptr;
	heroPtr = nullptr;
	trackPtr = nullptr;
	bossPtr = nullptr;
	notebox = nullptr;
	backPtr = nullptr;
	energyBar = nullptr;
	stageBar = nullptr;
	feverBar = nullptr;
	curr_state = 0;
	Engine::GetMusic().Init();
}

void Level1::Load()
{
	Engine::GetMusic().Play(Music::SOUND_NUM::REWIND);
	gameObjectManager = new GameObjectManager();
	isOption = false;
	selectedIndex = glm::vec2{ 0,1 };


	heroPtr = new Hero({ -4,-5 });

	backPtr = new Background();
	trackPtr = new Track(Music::SOUND_NUM::REWIND);
	notebox = new Note_box({ -4,0 });
	bossPtr = new Boss({ 15,-5 });
	energyBar = new EnergyBar({ -4,1.2 });
	stageBar = new Stage_bar({ -10,9 },204,82);   // total music time 204  ,  extra time 82

	//text = new GLText();
	//text->Load("../font/MochiyPopOne-Regular.ttf", 48);

	textureAll = Engine::GetTextureManager().Load("../images/Pause_screen.png");
	sound1 = Engine::GetTextureManager().Load("../images/pause_volume1.png");
	sound2 = Engine::GetTextureManager().Load("../images/pause_volume2.png");
	sound3 = Engine::GetTextureManager().Load("../images/pause_volume3.png");
	sound4 = Engine::GetTextureManager().Load("../images/pause_volume4.png");
	Restart = Engine::GetTextureManager().Load("../images/Pause_Restart.png");
	Quit = Engine::GetTextureManager().Load("../images/Pause_Quit.png");
	GLModel tempModel;
	tempModel.init({ 1,1 });
	model = tempModel;
	curr_state = static_cast<int>(STATE::EXTRA);
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
	gameObjectManager->Add(energyBar);
	gameObjectManager->Add(stageBar);
	AddGSComponent(new HitEmitter());
	AddGSComponent(new PerfectEmitter());
	AddGSComponent(new GoodEmitter());
	AddGSComponent(new BadEmitter());
	AddGSComponent(new MissEmitter());
	AddGSComponent(new Score());
}

void Level1::Update(double dt)
{
	GetGSComponent<Background>()->Update(dt);
	gameObjectManager->UpdateAll(dt);

	if (stageBar->Getchangeflag() == 1)
	{
		curr_state = static_cast<int>(STATE::GENERATING);
		Engine::GetMusic().Pause(Music::SOUND_NUM::REWIND);
		bossPtr->GenerateBoss();
		trackPtr->SetUpdate(false);
		stageBar->SetUpdate(false);
		Engine::GetMusic().Play(Music::SOUND_NUM::BOSS_ENTRANCE);
		Engine::GetMusic().volumeUp(Music::SOUND_NUM::BOSS_ENTRANCE);
	}
	if (curr_state == static_cast<int>(STATE::GENERATING) && bossPtr->GetVelocity().x == 0)
	{
		Engine::GetMusic().Resume(Music::SOUND_NUM::REWIND);
		Engine::GetMusic().pitchUp(Music::SOUND_NUM::REWIND);
		trackPtr->SetUpdate(true);
		stageBar->SetUpdate(true);

		feverBar = new Fever_bar({ -20,-9 });
		gameObjectManager->Add(feverBar);

		curr_state = static_cast<int>(STATE::FINISH);
	}

	if (escape.IsKeyDown() == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
	if (OptionSoundUpKey.IsKeyDown() == true)
	{
	    Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Option));
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
	//Engine::GetMusic().Stop(Music::SOUND_NUM::REWIND);
	gameObjectManager->Unload();
	ClearGSComponent();
}
