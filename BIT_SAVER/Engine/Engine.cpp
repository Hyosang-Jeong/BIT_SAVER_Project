/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Hyosang Jung
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
	//if (!GLHelper::init(1780, 980, "BIT_SAVER"))
	//{
	//	std::cout << "Unable to create OpenGL context" << std::endl;
	//	std::exit(EXIT_FAILURE);
	//}

	time_t seed = time(NULL);
	logger.LogEvent("Engine Init");
	window.Init(1920, 1080,windowName);
	fpsCalcTime = lastTick;
	srand(static_cast<unsigned int>(seed));
	logger.LogEvent("Seed = " + std::to_string(seed));
}

void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
}
void Engine::Update()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();
#ifdef _DEBUG
	if (dt > 2 / Engine::Target_FPS) {
		dt = 1 / Engine::Target_FPS;
		Engine::GetLogger().LogEvent("Long Frame detected!");
	}
#endif
	if (dt >= (1.0 / Engine::Target_FPS))
	{
		logger.LogVerbose("Engine Update");
		//gameStateManager.Update(dt);
	//	input.Update();
		//window.Update();
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
//bool Engine::HasGameEnded()
//{
//	//return  gameStateManager.HasGameEnded();
//}

//void Engine::AddSpriteFont(const std::filesystem::path& fileName)
//{
//	//fonts.push_back(fileName);
//}
