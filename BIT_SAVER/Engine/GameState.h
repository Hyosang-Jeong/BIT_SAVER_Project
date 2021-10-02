/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameState.h 
Purpose: Base class for different game states
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once
#include <string>


	class GameState
	{
	public:
		virtual void Load() = 0;
		virtual void Update(double dt) = 0;
		virtual void Unload() = 0;
		virtual std::string GetName() = 0;
		virtual void Draw() = 0;
	private:
	};