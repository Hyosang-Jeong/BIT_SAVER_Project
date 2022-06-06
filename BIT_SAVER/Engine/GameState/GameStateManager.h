/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.h
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang , Hyosang Jung , Sunwoo Lee

-----------------------------------------------------------------*/
#pragma once
#include <vector>
#include"..\GameObject\GameObjectManager.h"
#include"../GameState/GameState.h"

class GameStateManager
{
public:
	GameStateManager();
	void AddGameState(GameState& gameState);
	void Update(double dt);
	void SetNextState(int initState);
	void Shutdown();
	void ReloadState();
	void ResumeState();
	bool HasGameEnded() { return state == State::EXIT; }
	GameState* Find(std::string state_name);
	GameState* GetCurrstate();
	GameState* GetNextstate();

	template<typename T>
	T* GetGSComponent()
	{ 
		return currGameState->GetGSComponent<T>(); 
	}

public:
	enum class State
	{
		START,
		LOAD,
		UPDATE,
		PAUSE,
		PAUSE_UPDATE,
		RESUME,
		UNLOAD,
		SHUTDOWN,
		EXIT,
	};

	std::vector<GameState*> gameStates;
	State state;
	GameState* currGameState;
	GameState* nextGameState;
};

