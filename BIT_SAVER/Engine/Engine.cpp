/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Purpose: This is the service provider for our games engine services
Project: BIT_SAVER
Author: 
Creation date: 2021-03-07
-----------------------------------------------------------------*/
#include"Engine.h"
#include<time.h>  //time
Engine::Engine() :frameCount(0), lastTick(std::chrono::system_clock::now()),
#ifdef _DEBUG				
logger(Logger::Severity::Debug, true, lastTick)
#else 						
logger(Logger::Severity::Event, false, lastTick)
#endif
{}
Engine::~Engine() {}

void Engine::Init(std::string windowName)
{
	logger.LogEvent("Engine Init");
	window.Init(1600, 1000,windowName);

	init_shdrpgms();
	fpsCalcTime = lastTick;
	GetMusic().Init();
}

void Engine::Shutdown()
{
	Engine::GetMusic().Release();
	logger.LogEvent("Engine Shutdown");
}
void Engine::Update()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();
#ifdef _DEBUG
	if (dt > 2 / Engine::Target_FPS)
	{
		dt = 1 / Engine::Target_FPS;
		Engine::GetLogger().LogEvent("Long Frame detected!");
	}
#endif
	if (dt >= (1.0 / Engine::Target_FPS))
	{
		logger.LogVerbose("Engine Update");
		window.Update();
		gameStateManager.Update(dt);
		input.Update();
		GetMusic().Update();
		frameCount++;
		if (frameCount >= Engine::FPS_IntervalFrameCount)
		{
			double averageFrameRate = frameCount / std::chrono::duration<double>(now - fpsCalcTime).count();
			logger.LogEvent("FPS:  " + std::to_string(averageFrameRate));
			frameCount = 0;
			fpsCalcTime = now;
		}
		lastTick = now;
	}
}
void Engine::init_shdrpgms()
{
	std::vector<std::pair<GLenum, std::string>> shdr_file0
	{
		std::make_pair(GL_VERTEX_SHADER, "../shaders/Hero.vert"),
		std::make_pair(GL_FRAGMENT_SHADER,  "../shaders/Hero.frag")
	};
	GLSLShader shdr_pgm;
	shdr_pgm.CompileLinkValidate(shdr_file0);
	if (GL_FALSE == shdr_pgm.IsLinked())
	{
		std::cout << "Unable to compile/link/validate shader programs\n";
		std::cout << shdr_pgm.GetLog() << "\n";
		std::exit(EXIT_FAILURE);
	}

	shdrpgms["Hero"] = shdr_pgm;

	//collision box shader
	std::vector<std::pair<GLenum, std::string>> shdr_file1
	{
		std::make_pair(GL_VERTEX_SHADER, "../shaders/collision.vert"),
		std::make_pair(GL_FRAGMENT_SHADER,  "../shaders/collision.frag")
	};
	GLSLShader shdr_pgm1;
	shdr_pgm1.CompileLinkValidate(shdr_file1);
	if (GL_FALSE == shdr_pgm1.IsLinked())
	{
		std::cout << "Unable to compile/link/validate shader programs\n";
		std::cout << shdr_pgm1.GetLog() << "\n";
		std::exit(EXIT_FAILURE);
	}
	shdrpgms["Collision"] = shdr_pgm1;

	std::vector<std::pair<GLenum, std::string>> shdr_file2
	{
		std::make_pair(GL_VERTEX_SHADER, "../shaders/Mainmenu.vert"),
		std::make_pair(GL_FRAGMENT_SHADER,  "../shaders/Mainmenu.frag")
	};
	GLSLShader shdr_pgm2;
	shdr_pgm2.CompileLinkValidate(shdr_file2);
	if (GL_FALSE == shdr_pgm2.IsLinked())
	{
		std::cout << "Unable to compile/link/validate shader programs\n";
		std::cout << shdr_pgm2.GetLog() << "\n";
		std::exit(EXIT_FAILURE);
	}
	shdrpgms["Mainmenu"] = shdr_pgm2;

	std::vector<std::pair<GLenum, std::string>> shdr_file3
	{
		std::make_pair(GL_VERTEX_SHADER, "../shaders/Option.vert"),
		std::make_pair(GL_FRAGMENT_SHADER,  "../shaders/Option.frag")
	};
	GLSLShader shdr_pgm3;
	shdr_pgm3.CompileLinkValidate(shdr_file3);
	if (GL_FALSE == shdr_pgm3.IsLinked())
	{
	    std::cout << "Unable to compile/link/validate shader programs\n";
	    std::cout << shdr_pgm3.GetLog() << "\n";
	    std::exit(EXIT_FAILURE);
	}
	shdrpgms["Option"] = shdr_pgm3;

	std::vector<std::pair<GLenum, std::string>> shdr_file4
	{
		std::make_pair(GL_VERTEX_SHADER, "../shaders/Text.vert"),
		std::make_pair(GL_FRAGMENT_SHADER,  "../shaders/Text.frag")
	};
	GLSLShader shdr_pgm4;
	shdr_pgm4.CompileLinkValidate(shdr_file4);
	if (GL_FALSE == shdr_pgm4.IsLinked())
	{
		std::cout << "Unable to compile/link/validate shader programs\n";
		std::cout << shdr_pgm4.GetLog() << "\n";
		std::exit(EXIT_FAILURE);
	}
	shdrpgms["Text"] = shdr_pgm4;
}
bool Engine::HasGameEnded()
{
	return  gameStateManager.HasGameEnded();
}
