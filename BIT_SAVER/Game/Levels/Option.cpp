/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Option.cpp
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#include "Option.h"
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Mainmenu.h"
#include"State.h"

Option::Option() :
    escape(InputKey::Keyboard::Escape),
    OptionUpKey(InputKey::Keyboard::Up),
    OptionDownKey(InputKey::Keyboard::Down),
    OptionSoundUpKey(InputKey::Keyboard::Right),
    OptionSoundDownKey(InputKey::Keyboard::Left),
    OptionSelectKey(InputKey::Keyboard::Enter),
    isOption(false),
    selectedIndex(glm::vec2{ 0,1 })
{
    gameObjectManager = nullptr;
    curr_state = 0;
	select = SOUND;
}

void Option::Load()
{

    //isOption = false;
    //selectedIndex = glm::vec2{ 0,1 };


    textureAll = Engine::GetTextureManager().Load("../images/Pause_screen.png");
    sound1 = Engine::GetTextureManager().Load("../images/pause_volume1.png");
    sound2 = Engine::GetTextureManager().Load("../images/pause_volume2.png");
    sound3 = Engine::GetTextureManager().Load("../images/pause_volume3.png");
    sound4 = Engine::GetTextureManager().Load("../images/pause_volume4.png");
    Restart = Engine::GetTextureManager().Load("../images/Pause_Restart.png");
    Quit = Engine::GetTextureManager().Load("../images/Pause_Quit.png");

    model.init({ 1,1 });


}

void Option::Update([[maybe_unused]] double dt)
{
    GetIndex();

}

void Option::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	textureAll->Draw(10, model, "Option", { 0,0 }, { 5,5 });

	if (selectedIndex == glm::vec2{ 0,0 })
	{
	    sound1->Draw(10, model, "Option", { 0,0 }, { 5,5 });
	    Engine::GetMusic().SetVolume(Engine::GetMusic().REWIND, 0.25);
	}
	if (selectedIndex == glm::vec2{ 0,1 })
	{
	    sound2->Draw(10, model, "Option", { 0,0 }, { 5,5 });
	    Engine::GetMusic().SetVolume(Engine::GetMusic().REWIND, 0.5);
	}
	if (selectedIndex == glm::vec2{ 0,2 })
	{
	    sound3->Draw(10, model, "Option", { 0,0 }, { 5,5 });
	    Engine::GetMusic().SetVolume(Engine::GetMusic().REWIND, 0.75);

	}
	if (selectedIndex == glm::vec2{ 0,3 })
	{
	    sound4->Draw(10, model, "Option", { 0,0 }, { 5,5 });
	    Engine::GetMusic().SetVolume(Engine::GetMusic().REWIND, 1);
	}
	if (selectedIndex.x == 1)
	{
	    Restart->Draw(10, model, "Option", { 0,0 }, { 5,5 });
	    if (OptionSelectKey.IsKeyDown() == true)
	    {
			select = RESUME;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
	    }
	}
	if (selectedIndex.x == 2)
	{
	    Quit->Draw(10, model, "Option", { 0,0 }, { 5,5 });
	    if (OptionSelectKey.IsKeyDown() == true)
	    {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
	    }
	}
}
void Option::Unload()
{
}

void Option::GetIndex()
{
    if (OptionUpKey.IsKeyReleased() == true)
    {
	if (selectedIndex.x == 0 || selectedIndex.x == 1)
	{
	    selectedIndex.x = 0;
	}
	else if (selectedIndex.x == 2)
	{
	    selectedIndex.x = 1;
	}
    }
    if (OptionDownKey.IsKeyReleased() == true)
    {
	if (selectedIndex.x == 0)
	{
	    selectedIndex.x = 1;
	}
	else if (selectedIndex.x == 1 || selectedIndex.x == 2)
	{
	    selectedIndex.x = 2;
	}
    }
    if (selectedIndex.x == 0)
    {
	if (OptionSoundUpKey.IsKeyReleased() == true)
	{
	    if (selectedIndex.y == 0)
	    {
		selectedIndex.y = 1;
	    }
	    else if (selectedIndex.y == 1)
	    {
		selectedIndex.y = 2;
	    }
	    else if (selectedIndex.y == 2 || selectedIndex.y == 3)
	    {
		selectedIndex.y = 3;
	    }
	}
	if (OptionSoundDownKey.IsKeyReleased() == true)
	{
	    if (selectedIndex.y == 0 || selectedIndex.y == 1)
	    {
		selectedIndex.y = 0;
	    }
	    else if (selectedIndex.y == 2)
	    {
		selectedIndex.y = 1;
	    }
	    else if (selectedIndex.y == 3)
	    {
		selectedIndex.y = 2;
	    }
	}
    }
}

Select Option::GetSelect()
{
	return select;
}
