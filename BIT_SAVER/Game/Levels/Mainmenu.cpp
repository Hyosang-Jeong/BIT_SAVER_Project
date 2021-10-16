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

MainMenu::MainMenu() : PlayKey(InputKey::Keyboard::Enter)
{
	Splash.setup_texobj("../images/DigiPen_BLACK_1024px.png");

	Logo.setup_texobj("../images/LOGO.png");
}

void MainMenu::Load()
{}

void MainMenu::Update(double dt)
{
	timer -= dt;
	if (PlayKey.IsKeyReleased() == true && timer <=0)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
	}
	if (timer < 0)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
	}
}

void MainMenu::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//to alpha effect
	std::map<std::string, GLSLShader>::iterator shd_ref;
	shd_ref = Engine::GetGLShader().find("Mainmenu");
	shd_ref->second.Use();
	shd_ref = Engine::GetGLShader().find("Mainmenu");
	GLuint alpha = glGetUniformLocation(shd_ref->second.GetHandle(), "alpha");
	if (alpha < 0)
	{
		Engine::GetLogger().LogError("Uniform value doesn't exist! ");
	}
	glUniform1f(alpha, static_cast<float>(timer) / 3.0f);
	if (timer > 3)
	{
		Splash.Draw(glm::mat3{ 2 / 3.0,0,0,0,1 / 3.0,0,0,0,1 }, "Basic_model", "Mainmenu");
	}
	else
	{
		Logo.Draw(glm::mat3{ 1,0,0,0,1,0,0,0,1 }, "Basic_model", "Mainmenu");
	}
}
void MainMenu::Unload()
{
}
