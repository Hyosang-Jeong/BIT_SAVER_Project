

#include <iostream>
#include <sstream>
#include <iomanip>
#include"Engine/Engine.h"
#include "..\BIT_SAVER\Engine\Music\music.h"
#include"Game\Level1.h"

Engine& engine = Engine::Instance();
int main() 
{
    engine.Init("Bit_Saver");

    Music music;
    music.SoundSystem();
    Level1 level1;
    engine.GetGameStateManager().AddGameState(level1);

    while (!glfwWindowShouldClose(engine.GetWindow().ptr_window)) 
    {
       engine.Update();
	   //music.Play(0);
    }
   // cleanup();
}
