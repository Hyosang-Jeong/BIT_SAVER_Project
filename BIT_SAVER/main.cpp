#include"Engine/Engine.h"
#include "..\BIT_SAVER\Engine\Music\music.h"
#include "Game\Levels\Tutorial.h"
#include"Game\Levels\Level1.h"
#include "Game\Levels\Offset.h"
#include"Game\Levels\Option.h"
#include"Game\Levels\Gameover.h"
#include"Game\Levels\Clear.h"
#include"Game\Levels\Splash.h"
#include"Game\Levels\Mainmenu.h"
#include"Engine/Input/Input.h"
#include"Game\Levels\Gameover.h"

int main()
{
	Engine& engine = Engine::Instance();
	engine.Init("Bit_Saver");
	InputKey exit(InputKey::Keyboard::Enter);
	Splash splash;
	Mainmenu main_menu;
	Tutorial tutorial;
	Level1 level1;
	Offset offset;
	Option option;
	Clear clear;
	Gameover gameover;

	engine.GetGameStateManager().AddGameState(splash);
	engine.GetGameStateManager().AddGameState(main_menu);
	engine.GetGameStateManager().AddGameState(tutorial);
	engine.GetGameStateManager().AddGameState(level1);
	engine.GetGameStateManager().AddGameState(offset);
	engine.GetGameStateManager().AddGameState(option);
	engine.GetGameStateManager().AddGameState(clear);
	engine.GetGameStateManager().AddGameState(gameover);
	
	while (engine.HasGameEnded() == false)
	{
		engine.Update();
	}

	engine.Shutdown();
	return 0;
}
