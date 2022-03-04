/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Gameover.h
Project: BIT_SAVER
Author: Hyun Kang
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include"..\Engine\Input\Input.h"  //input key
class Gameover : public GameState
{
public:
    Gameover();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    std::string GetName() override { return "Gameover"; }
    InputKey ESCAPE;
private:
};

