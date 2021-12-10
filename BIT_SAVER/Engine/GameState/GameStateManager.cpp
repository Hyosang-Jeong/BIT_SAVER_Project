/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang , Hyosang Jung , Sunwoo Lee

-----------------------------------------------------------------*/

#include"GameStateManager.h"
#include"GameState.h"
#include"..\Engine.h" //Getlogger
#include "..\Music\Sound_Num.h"

GameStateManager::GameStateManager()
{
	currGameState = nullptr;
	nextGameState = nullptr;
	state = State::START;
}

void GameStateManager::AddGameState(GameState& gameState)
{
	GameStateManager::gameStates.push_back(&gameState);
}

void GameStateManager::SetNextState(int initState)
{
	nextGameState = gameStates[initState];
}

void GameStateManager::Shutdown()
{
	if (state == State::PAUSE_UPDATE)
	{
		nextGameState->Unload();
		state = State::SHUTDOWN;
	}
	nextGameState = nullptr;
}
void GameStateManager::ReloadState()
{
	nextGameState = currGameState;
	state = State::UNLOAD;
}
void GameStateManager::ResumeState()
{
	state = State::RESUME;
}
GameState* GameStateManager::Find(std::string state_name)
{
	for (auto  i = 0; i < gameStates.size(); i++)
	{
		if (gameStates[i]->GetName() == state_name)
		{
			return gameStates[i];
		}
	}
	return nullptr;
}
GameState* GameStateManager::GetCurrstate()
{
	return currGameState;
}
GameState* GameStateManager::GetNextstate()
{
	return nextGameState;
}
void GameStateManager::Update(double dt)
{
	switch (state)
	{
	case State::START:
	{
		if (gameStates.empty() == true)
		{
			Engine::GetLogger().LogError("Don't have game states");
			state = State::SHUTDOWN;
		}
		else
		{
			nextGameState = gameStates[0];
			state = State::LOAD;
		}
		break;
	}
	case State::LOAD:
	{
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		state = State::UPDATE;
		break;
	}
	case State::UPDATE:
	{
		if (currGameState != nextGameState)
		{
			state = State::UNLOAD;
			if (nextGameState != nullptr)
			{
				if (nextGameState->GetName() == "Option")
				{
					state = State::PAUSE;
					if (currGameState->GetcurrentMusic() != SOUND_NUM::MUSIC_END)
					{
						Engine::GetMusic().Pause(currGameState->GetcurrentMusic());
					}
				}
			}
		}
		else
		{
			Engine::GetLogger().LogVerbose("Update" + currGameState->GetName());
			glfwSwapBuffers(Engine::GetWindow().ptr_window);
			currGameState->Update(dt);
			currGameState->Draw();
		}

		break;
	}
	case State::PAUSE:
	{
		Engine::GetLogger().LogEvent("Load OPTION");
		nextGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		state = State::PAUSE_UPDATE;
		break;
	}
	case State::PAUSE_UPDATE:
	{
		Engine::GetLogger().LogVerbose("Update" + nextGameState->GetName());
		glfwSwapBuffers(Engine::GetWindow().ptr_window);
		nextGameState->Update(dt);
		if (nextGameState != nullptr)
		{
			nextGameState->Draw();
		}
		if (nextGameState == nullptr)
		{
			currGameState->Unload();
		}
		break;
	}
	case State::RESUME:
	{
		nextGameState = currGameState;
		Engine::GetMusic().Resume(currGameState->GetcurrentMusic());
		state = State::UPDATE;
		break;
	}
	case State::UNLOAD:
	{
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		currGameState->Unload();
		if (nextGameState == nullptr)
		{
			state = State::SHUTDOWN;
		}
		else
		{
			state = State::LOAD;
		}
		break;
	}
	case State::SHUTDOWN:
	{
		Engine::GetTextureManager().Unload();
		state = State::EXIT;
		break;
	}
	}
}