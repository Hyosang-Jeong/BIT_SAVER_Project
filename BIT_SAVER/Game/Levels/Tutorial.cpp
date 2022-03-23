/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tutorial.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang 

-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Tutorial.h"
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
#include "../Objects/Tutorial_Helper.h"
#include"../Objects/Score.h"
#include"../Objects/fever.h"
#include"../Objects/CheckBox.h"
#include"../Levels/Option.h"
#include"..\..\Engine\Physics\Camera.h"

Tutorial::Tutorial() :
	escape(InputKey::Keyboard::Escape)
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
	camera = nullptr;
	gamestate = TUTO_LEVEL_STATE::EXTRA;
}

void Tutorial::Load()
{
	isMusicEnd = false;
	gameObjectManager = new GameObjectManager();
	heroPtr = new Hero({ -4,-5 });
	backPtr = new Background();
	trackPtr = new Track(SOUND_NUM::OFFSET);
	notebox = new Note_box({ -4,0 });
	bossPtr = new Boss({ 15,-5 });
	energyBar = new EnergyBar({ -4,1.2 });
	stageBar = new Stage_bar({ -10,9 }, 110, 82);   // total music time 204  ,  extra time 82
	camera = new Camera({0,0 });
	currstate = Tuto_Helper_Enum::GREETINGS;


	backPtr->Add(texture_path[Background_1], 0);
	backPtr->Add(texture_path[Parallax1_5], 0.5);
	backPtr->Add(texture_path[Parallax1_4], 0.8);
	backPtr->Add(texture_path[Parallax1_3], 1.1);
	backPtr->Add(texture_path[Parallax1_2], 1.3);
	backPtr->Add(texture_path[Parallax1_1], 1.5);

	AddGSComponent(gameObjectManager);
	AddGSComponent(backPtr);
	AddGSComponent(camera);

	gameObjectManager->Add(heroPtr);
	gameObjectManager->Add(notebox);
	gameObjectManager->Add(bossPtr);
	gameObjectManager->Add(energyBar);
	gameObjectManager->Add(stageBar);
	gameObjectManager->Add(trackPtr);
	gameObjectManager->Add(new CheckBox({ -4.4,0 }, 0));
	gameObjectManager->Add(new CheckBox({ -3.2,0 }, 0));
	gameObjectManager->Add(new CheckBox({ -4.6,0 }, 1));
	gameObjectManager->Add(new CheckBox({ -2.6,0 }, 1));
	gameObjectManager->Add(new CheckBox({ -4.8,0 }, 2));
	gameObjectManager->Add(new CheckBox({ -2.0,0 }, 2));

	AddGSComponent(new Tutorial_Helper());
	AddGSComponent(new HitEmitter());
	AddGSComponent(new PerfectEmitter());
	AddGSComponent(new GoodEmitter());
	AddGSComponent(new BadEmitter());
	AddGSComponent(new MissEmitter());
	AddGSComponent(new Score());

	trackPtr->track_info[0].erase(trackPtr->track_info[0].begin(), trackPtr->track_info[0].begin() + 4);
	trackPtr->track_info[1].erase(trackPtr->track_info[1].begin(), trackPtr->track_info[1].begin() + 2);

}

void Tutorial::Update(double dt)
{


	GetGSComponent<Background>()->Update(dt);
	Update_currstate(dt);

}

void Tutorial::Update_currstate(double dt)
{
	switch (currstate)
	{
	case Tuto_Helper_Enum::GREETINGS:
	{
		Engine::GetGSComponent<Tutorial_Helper>()->Set_state(static_cast<int>(currstate));
		if (Engine::GetGSComponent<Tutorial_Helper>()->Getflag() == true)
		{
			currstate = Tuto_Helper_Enum::UP_NOTE_GENERATE;
			Engine::GetGSComponent<Tutorial_Helper>()->Setflag(false);
		}
		break;
	}
	case Tuto_Helper_Enum::UP_NOTE_GENERATE:
	{
		Engine::GetGSComponent<Tutorial_Helper>()->Set_state(static_cast<int>(currstate));
		if (!Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET) && isMusicEnd == false)
		{
			Engine::GetMusic().Play(SOUND_NUM::OFFSET);
			isMusicEnd = true;
		}
		gameObjectManager->UpdateAll(dt);
		Note* note = static_cast<Note*>(gameObjectManager->Find(GameObjectType::Note));
		if (note != nullptr)
		{
			if (note->GetPosition().y > 0 && note->GetPosition().x < -4)
			{
				currstate = Tuto_Helper_Enum::UP_NOTE_HIT;
				Engine::GetGSComponent<Tutorial_Helper>()->Set_state(static_cast<int>(currstate));
				Engine::GetMusic().Pause(SOUND_NUM::OFFSET);
				Engine::GetGSComponent<Tutorial_Helper>()->Setflag(false);
			}
		}
		break;
	}
	case Tuto_Helper_Enum::UP_NOTE_HIT:
	{
		Hero* hero = static_cast<Hero*>(gameObjectManager->Find(GameObjectType::Hero));
		hero->Update(dt);

		if (Engine::GetGSComponent<Tutorial_Helper>()->Getflag() == true)
		{
			currstate = Tuto_Helper_Enum::DOWN_NOTE_GENERATE;
			Engine::GetGSComponent<Tutorial_Helper>()->Setflag(false);
			Engine::GetGSComponent<Tutorial_Helper>()->Set_state(static_cast<int>(currstate));
		}
		break;
	}
	case Tuto_Helper_Enum::DOWN_NOTE_GENERATE:
	{
		Engine::GetMusic().Resume(SOUND_NUM::OFFSET);
		gameObjectManager->UpdateAll(dt);

		if (gameObjectManager->Find(GameObjectType::Note) != nullptr)
		{
			if (gameObjectManager->Find(GameObjectType::Note)->GetPosition().y < 0 &&
				gameObjectManager->Find(GameObjectType::Note)->GetPosition().x < -4)
			{
				currstate = Tuto_Helper_Enum::DOWN_NOTE_HIT;
				Engine::GetMusic().Pause(SOUND_NUM::OFFSET);
				Engine::GetGSComponent<Tutorial_Helper>()->Set_state(static_cast<int>(currstate));
			}
		}
		break;
	}
	case Tuto_Helper_Enum::DOWN_NOTE_HIT:
	{
		Hero* hero = static_cast<Hero*>(gameObjectManager->Find(GameObjectType::Hero));
		hero->Update(dt);
		if (Engine::GetGSComponent<Tutorial_Helper>()->Getflag() == true)
		{
			currstate = Tuto_Helper_Enum::END;
			Engine::GetGSComponent<Tutorial_Helper>()->Setflag(false);
			Engine::GetGSComponent<Tutorial_Helper>()->Set_state(static_cast<int>(currstate));
		}
		break;
	}
	case Tuto_Helper_Enum::END:
	{
		Engine::GetMusic().Resume(SOUND_NUM::OFFSET);
		gameObjectManager->UpdateAll(dt);
		Hero* hero = static_cast<Hero*>(gameObjectManager->Find(GameObjectType::Hero));
		hero->Update(dt);
		if (Engine::GetGSComponent<Tutorial_Helper>()->Getflag() == true)
		{
			Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level0));
		}
		break;
	}
	}
}

void Tutorial::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	GetGSComponent<Background>()->Draw(camera->GetMatrix());
	GetGSComponent<Score>()->Draw({ 0,100 });
	Engine::GetGSComponent<Tutorial_Helper>()->Draw();
	gameObjectManager->DrawAll(camera->GetMatrix());
}


void Tutorial::Unload()
{
	heroPtr = nullptr;
	trackPtr = nullptr;
	notebox = nullptr;
	bossPtr = nullptr;
	backPtr = nullptr;
	energyBar = nullptr;
	stageBar = nullptr;
	gameObjectManager->Unload();

	if (Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET) == true)
	{
		Engine::GetMusic().pitchDefault(SOUND_NUM::OFFSET);
		Engine::GetMusic().Stop(SOUND_NUM::OFFSET);
	}

	Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET);
	ClearGSComponent();
}
