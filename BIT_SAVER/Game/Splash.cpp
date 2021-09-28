/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h" //Screens::Level1
#include "Splash.h"
#include"../Engine/Texture.h"
Splash::Splash():texturePtr(nullptr)
{}

void Splash::Load()
{
	texturePtr = Engine::GetTextureManager().Load("Assets/DigiPen_BLACK_1024px.png");
}
void Splash::Update(double dt) {
	timer += dt;
	if (timer >= displaytime)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
}
void Splash::Unload()
{

}

void Splash::Draw()
{
	Engine::GetWindow().Clear(0xffffffff);
	math::ivec2 windowsize = Engine::GetWindow().GetSize();
	windowsize /= 2;
	math::ivec2 texturesize = texturePtr->GetSize();
	texturesize /= 2;
	texturePtr->Draw(math::TranslateMatrix(windowsize - texturesize));
}
