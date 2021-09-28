/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 4/27/2021
-----------------------------------------------------------------*/
#include"MainMenu.h"
#include "Fonts.h" //font
#include "Screens.h" // screen
#include "../Engine/Engine.h"  //getspritefont

MainMenu::OptionData MainMenu::optionsData[static_cast<int>(MainMenu::Options::Count)] = {
	{"Side Scroller", {0.5, 0.45}, {} },
	{"Space Shooter", {0.5, 0.35}, {} },
	{"Quit", {0.5, 0.25}, {} },
};

MainMenu::MainMenu() :
	upKey(CS230::InputKey::Keyboard::Up),
	downKey(CS230::InputKey::Keyboard::Down),
	selectKey(CS230::InputKey::Keyboard::Enter),
	selectedIndex(0)
{}

void MainMenu::Load() {
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("CS230 Project", 0xFFFFFFFF, true);
	for (OptionData& data : optionsData) 
	{
		RenderOption(data, false);
	}
	selectedIndex = static_cast<int>(Options::Level1);
	RenderOption(optionsData[selectedIndex], true);
}

void MainMenu::Update([[maybe_unused]] double dt)
{
	switch (selectedIndex)
	{
	case 0:
		if (downKey.IsKeyReleased() == true)
		{
			RenderOption(optionsData[selectedIndex], false);
			selectedIndex++;
			RenderOption(optionsData[selectedIndex], true);
		}
		else if (selectKey.IsKeyReleased() == true)
		{
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level1));
		}
		break;
	case 1:
		if (downKey.IsKeyReleased() == true)
		{
			RenderOption(optionsData[selectedIndex], false);
			selectedIndex++;
			RenderOption(optionsData[selectedIndex], true);
		}
		if (upKey.IsKeyReleased() == true)
		{
			RenderOption(optionsData[selectedIndex], false);
			selectedIndex--;
			RenderOption(optionsData[selectedIndex], true);
		}
		if (selectKey.IsKeyReleased() == true)
		{
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
		}
		break;
	case 2:	if (upKey.IsKeyReleased() == true)
	{
		RenderOption(optionsData[selectedIndex], false);
		selectedIndex--;
		RenderOption(optionsData[selectedIndex], true);
	}
		  if (selectKey.IsKeyReleased() == true)
		  {
			  Engine::GetGameStateManager().Shutdown();
		  }
		  break;
	}


}

void MainMenu::Unload()
{

}


void MainMenu::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);
	title.Draw(math::TranslateMatrix(math::ivec2{ Engine::GetWindow().GetSize().x / 2 - title.GetSize().x,Engine::GetWindow().GetSize().y / 2 + title.GetSize().y * 2 }) * math::ScaleMatrix({ 2.0,2.0 }));
	for (int i = 0; i < static_cast<int>(MainMenu::Options::Count); i++)
	{
		optionsData[i].texture.Draw(math::TranslateMatrix(math::vec2{ Engine::GetWindow().GetSize().x * optionsData[i].positionPercent.x - optionsData[i].texture.GetSize().x / 2,Engine::GetWindow().GetSize().y * optionsData[i].positionPercent.y }));
	}
}

void MainMenu::RenderOption(OptionData& data, bool isHighlighted) {

	data.texture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(
		data.text, (isHighlighted == true) ? MainMenu::onColor : MainMenu::offColor, true);
}