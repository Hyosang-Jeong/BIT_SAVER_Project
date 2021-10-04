/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 2021-03-07
-----------------------------------------------------------------*/

#include"GameStateManager.h"
#include"GameState.h"
#include"..\Engine.h" //Getlogger
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
	nextGameState = nullptr;
}
void GameStateManager::ReloadState()
{
	state = State::UNLOAD;
}
GameObjectManager GameStateManager::GetGameObjectManager()
{
	return gameObjectManager;
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
	case State::UNLOAD:
	{
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		//if (currGameState != nextGameState)
		//{
		//	Engine::GetTextureManager().Unload();
		//}
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
		state = State::EXIT;
		break;
	}
	}
}