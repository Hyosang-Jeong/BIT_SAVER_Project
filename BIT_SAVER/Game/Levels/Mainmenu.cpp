/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mainmenu.cpp
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Mainmenu.h"
#include"State.h"

Mainmenu::Mainmenu() : 
ESCAPE(InputKey::Keyboard::Escape),
Level1(InputKey::Keyboard::NUM_1),
Level2(InputKey::Keyboard::NUM_2)
{
	Logo.setup_texobj("../images/Mainmenu.png");
}

void Mainmenu::Load()
{}

void Mainmenu::Update([[maybe_unused]]double dt)
{
	if (Level1.IsKeyReleased() == true)
	{
			Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
	}
	if (Level2.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level2));
	}
	if (ESCAPE.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
}

void Mainmenu::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	std::map<std::string, GLSLShader>::iterator shd_ref;
	shd_ref = Engine::GetGLShader().find("Mainmenu");
	shd_ref->second.Use();
	shd_ref = Engine::GetGLShader().find("Mainmenu");
	GLuint alpha = glGetUniformLocation(shd_ref->second.GetHandle(), "alpha");
	if (alpha < 0)
	{
		Engine::GetLogger().LogError("Uniform value doesn't exist! ");
	}
	glUniform1f(alpha, 1);
	Logo.Draw(glm::mat3{ 1,0,0,0,1,0,0,0,1 }, "Basic_model", "Mainmenu");
}
void Mainmenu::Unload()
{
}
