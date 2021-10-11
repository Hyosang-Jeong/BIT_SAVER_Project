

#include <iostream>
#include <sstream>
#include <iomanip>
#include"Engine/Engine.h"
#include "..\BIT_SAVER\Engine\Music\music.h"
#include"Game\Levels\Level1.h"
#include"Engine/Input/Input.h"
//#include<crtdbg.h>
//#if _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define malloc(s) _malloc_dbg(s,_NORMAL_BLOCK,__FILE__,__LINE__)
//#endif

Engine& engine = Engine::Instance();
int main()
{
	engine.Init("Bit_Saver");
	InputKey exit(InputKey::Keyboard::Enter);

	
	Level1 level1;
	engine.GetGameStateManager().AddGameState(level1);

	while (!glfwWindowShouldClose(engine.GetWindow().ptr_window))
	{
		engine.Update();
		Engine::GetMusic().Play(Engine::GetMusic().MUSIC_CANON);
	}


	//_CrtDumpMemoryLeaks();
	engine.Shutdown();
	return 0;
	// cleanup();
}
