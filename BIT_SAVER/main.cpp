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
	
	while (!glfwWindowShouldClose(engine.GetWindow().ptr_window))
	{
		engine.Update();
		Engine::GetMusic().Play(0);
		Engine::GetMusic().pSystem[0]->update();
	}

	engine.Shutdown();
	return 0;
}
