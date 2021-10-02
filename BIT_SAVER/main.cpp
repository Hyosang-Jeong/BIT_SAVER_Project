/*!
@file    main.cpp
@author  pghali@digipen.edu
@date    10/11/2016

This file uses functionality defined in types GLHelper and GLApp to initialize
an OpenGL context and implement a game loop.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
// Extension loader library's header must be included before GLFW's header!!!

#include "Engine/glhelper.h"
#include "Engine/glapp.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include"Engine/Engine.h"
/*                                                   type declarations
----------------------------------------------------------------------------- */

/*                                                      function declarations
----------------------------------------------------------------------------- */
static void draw();
static void update();
static void cleanup();

/*                                                      function definitions
----------------------------------------------------------------------------- */
/*  _________________________________________________________________________ */
/*! main

@param none

@return int

Indicates how the program existed. Normal exit is signaled by a return value of
0. Abnormal termination is signaled by a non-zero return value.
Note that the C++ compiler will insert a return 0 statement if one is missing.
*/
Engine& engine = Engine::Instance();

int main() 
{
    engine.Init("Bit_Saver");

    GLApp::init();

    while (!glfwWindowShouldClose(engine.GetWindow().ptr_window)) 
    {
        update();
        draw();
    }
    cleanup();
}

static void update() 
{
    glfwPollEvents();
    double delta_time = GLHelper::update_time(1.0);
    GLApp::update(delta_time);
}

static void draw() 
{
    GLApp::draw();
    glfwSwapBuffers(engine.GetWindow().ptr_window);
}

void cleanup() {

    GLHelper::cleanup();

    GLApp::cleanup();
}

//
//#include <stdexcept>	//std::exception
//#include <iostream>		//std::cerr
//
//#include "Engine/Engine.h"
//#include "Game/Splash.h"
//#include "Game/MainMenu.h"
//#include "Game/Level1.h"
//#include "Game/Level2.h"
//#include "Game/MainMenu.h"
//#include "Game/Screens.h"
//
//
//int main(void) {
//    try {
//        Engine& engine = Engine::Instance();
//        engine.Init("Week 12");
//        Splash splash;
//        MainMenu mainmenu;
//        Level1 level1;
//        Level2 level2;
//
//        engine.AddSpriteFont("assets/font.png");
//        engine.AddSpriteFont("assets/font2.png");
//        engine.GetGameStateManager().AddGameState(splash);
//        engine.GetGameStateManager().AddGameState(mainmenu);
//        engine.GetGameStateManager().AddGameState(level1);
//        engine.GetGameStateManager().AddGameState(level2);
//
//        while (engine.HasGameEnded() == false)
//        {
//            engine.Update();
//        }
//        engine.Shutdown();
//        return 0;
//    }
//    catch (std::exception& e) {
//        std::cerr << e.what() << "\n";
//        return -1;
//    }
//}