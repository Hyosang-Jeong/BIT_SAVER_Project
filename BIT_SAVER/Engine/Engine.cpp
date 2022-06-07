/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Purpose: This is the service provider for our games engine services
Project: BIT_SAVER
Author:  Hyosang Jung , Sunwoo Lee

-----------------------------------------------------------------*/
#include"Engine.h"
#include<time.h>  //time
#include <glm/gtc/matrix_transform.hpp>

Engine::Engine() :frameCount(0),  lastTick(std::chrono::system_clock::now()),easy(false),
#ifdef _DEBUG				
logger(Logger::Severity::Debug, true, lastTick)
#else 						
logger(Logger::Severity::Event, false, lastTick)
#endif
{

	attackKey.UpAttackKey = InputKey::Keyboard::F;
	attackKey.DownAttackKey = InputKey::Keyboard::J;

}
Engine::~Engine() {}

void Engine::Init(std::string windowName)
{
	logger.LogEvent("Engine Init");
	window.Init(1600, 800,windowName);

	init_shdrpgms();
	fpsCalcTime = lastTick;
	GetMusic().Init();
	init_fonts();
	GetText(font_path[PressStart]).Load(font_path[PressStart], 20);
	GetText(font_path[MochiyPopOne]).Load(font_path[MochiyPopOne], 48);

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
void Engine::init_fonts()
{
	GLText text1 , text2;
	std::string text2path{ font_path[MochiyPopOne] };
	std::string text1path{ font_path[PressStart] };

	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(Engine::GetWindow().GetSize().x), static_cast<float>(Engine::GetWindow().GetSize().y), 0.0f);

	text1.shd_ref = Engine::GetGLShader().find("Text");
	if (text1.shd_ref == Engine::GetGLShader().end())
	{
		Engine::GetLogger().LogError("Shader not found!");
		std::exit(EXIT_FAILURE);
	}
	text2.shd_ref = Engine::GetGLShader().find("Text");


	text1.shd_ref->second.Use();

	GLint uniform_var_loc1 =
		glGetUniformLocation(text1.shd_ref->second.GetHandle(), "projection");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix4fv(uniform_var_loc1, 1, GL_FALSE, &proj[0].x);
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}

	GLint uniform_var_loc2 =
		glGetUniformLocation(text1.shd_ref->second.GetHandle(), "text");
	if (uniform_var_loc2 >= 0) {
		glUniform1i(uniform_var_loc2, 0);
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}

	text1.shd_ref->second.UnUse();


	text2.shd_ref->second.Use();

	uniform_var_loc1 =
		glGetUniformLocation(text2.shd_ref->second.GetHandle(), "projection");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix4fv(uniform_var_loc1, 1, GL_FALSE, &proj[0].x);
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}

	uniform_var_loc2 =
		glGetUniformLocation(text2.shd_ref->second.GetHandle(), "text");
	if (uniform_var_loc2 >= 0) {
		glUniform1i(uniform_var_loc2, 0);
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}

	text2.shd_ref->second.UnUse();

	glGenVertexArrays(1, &text1.VAO);
	glGenBuffers(1, &text1.VBO);
	glBindVertexArray(text1.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, text1.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &text2.VAO);
	glGenBuffers(1, &text2.VBO);
	glBindVertexArray(text2.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, text2.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	texts[text1path] = text1;
	texts[text2path] = text2;
	
}
bool Engine::GetDifficulty()
{
    return easy;
}
void Engine::SetDifficulty(bool difficulty)
{
	easy = difficulty;
}
bool Engine::HasGameEnded()
{
	if (glfwWindowShouldClose(Engine::GetWindow().ptr_window))
	{
			return true;
	}
	return  gameStateManager.HasGameEnded();
}
