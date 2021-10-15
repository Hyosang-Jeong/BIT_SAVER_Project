#include <iostream>
#include <sstream>
#include <iomanip>
#include"Engine/Engine.h"
#include "..\BIT_SAVER\Engine\Music\music.h"
#include"Game\Levels\Level1.h"
#include"Engine/Input/Input.h"

int main()
{
	Engine& engine = Engine::Instance();
	engine.Init("Bit_Saver");
	InputKey exit(InputKey::Keyboard::Enter);

	Level1 level1;
	engine.GetGameStateManager().AddGameState(level1);
	


	while (engine.HasGameEnded() == false)

	{
		engine.Update();

	}

	engine.Shutdown();
	return 0;
}
