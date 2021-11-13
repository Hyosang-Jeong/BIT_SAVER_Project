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
    mouseSwitch(false),
    selectedIndex(glm::vec2{ 0,1 }),
    SoundBallPosition(glm::vec2{ 0,5 }),
    SoundBallScale(glm::vec2{ 0.2,0.2 }),
    smallsoundballScale(glm::vec2{ 0.2,0.2 }),
    MouseKey(InputKey::Mouse::Left)
{
    curr_state = 0;
    select = -1;
}

void Option::Load()
{


    textureAll = Engine::GetTextureManager().Load("../images/Pause_screen.png");
    sound1 = Engine::GetTextureManager().Load("../images/pause_volume1.png");
    sound2 = Engine::GetTextureManager().Load("../images/pause_volume2.png");
    sound3 = Engine::GetTextureManager().Load("../images/pause_volume3.png");
    sound4 = Engine::GetTextureManager().Load("../images/pause_volume4.png");
    Restart = Engine::GetTextureManager().Load("../images/Pause_Restart.png");
    Quit = Engine::GetTextureManager().Load("../images/Pause_Quit.png");
    soundBar = Engine::GetTextureManager().Load("../images/sound_bar.png");
    bigSoundBall = Engine::GetTextureManager().Load("../images/sound_bigball.png");
    smallSoundBall = Engine::GetTextureManager().Load("../images/sound_smallball.png");

    model.init({ 1,1 });

     w = Engine::GetWindow().GetSize().x;
     h = Engine::GetWindow().GetSize().y;
    world_to_ndc=
    {
	20/w, 0,0,
	0,-20/h,0,
	-10,10,1
    };
}

void Option::Update([[maybe_unused]] double dt)
{
    mousePosition = Engine::GetInput().MouseGetPosition();
    mousePosition = world_to_ndc * glm::vec3(mousePosition,1);

    GetIndex();

    if (IsInBox(SoundBallPosition))
    {
	if (smallsoundballScale.x < 0.59f)
	{
	    smallsoundballScale.x += static_cast<float>(dt);
	}
	if (smallsoundballScale.y < 0.59f)
	{
	    smallsoundballScale.y += static_cast<float>(dt);
	}

	if (MouseKey.MouseIsKeyDown() == true)
	{
	    mouseSwitch = true;
	}
	else
	{
	    mouseSwitch = false;
	}
    }
    else if(IsInBox(SoundBallPosition)==false)
    {
	if (smallsoundballScale.x > 0.2f)
	{
	    smallsoundballScale.x -= static_cast<float>(dt);
	}
	if (smallsoundballScale.y > 0.2f)
	{
	    smallsoundballScale.y -= static_cast<float>(dt);
	}
    }
    if (mouseSwitch == true && MouseKey.MouseIsKeyDown()==true)
    {
	if (mousePosition.x >= -2.f && mousePosition.x <= 2.f)
	{
	    SoundBallPosition.x = mousePosition.x;
	}
	Engine::GetMusic().SetVolume(Engine::GetMusic().REWIND, ((SoundBallPosition.x) + 2.f)/4.f);
    }
}

void Option::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    
	textureAll->Draw(10, model, "Option", { 0,0 }, { 5,5 });
	soundBar->Draw(10, model, "Option", { 0,5 }, { 2,0.15 });
	bigSoundBall->Draw(10, model, "Option", SoundBallPosition, { 0.3,0.3 });
	smallSoundBall->Draw(10, model, "Option", SoundBallPosition, smallsoundballScale);
	
	if (select == Select::RESUME)
	{
	    Restart->Draw(10, model, "Option", { 0,0 }, { 5,5 });

	}
	if (select == Select::RESTART)
	{
	    Restart->Draw(10, model, "Option", { 0,0 }, { 5,5 });

	}
	if (selectedIndex.x == 2)
	{
	    Quit->Draw(10, model, "Option", { 0,0 }, { 5,5 });
	}
}


void Option::GetIndex()
{
    std::cout << select << std::endl;
    if (OptionUpKey.IsKeyReleased() == true)
    {
	if (select > Select::RESUME)
	{
	    select--;
	}
	else if (select == Select::RESUME)
	{
	    select = Select::QUIT;
	}
    }
    else if (OptionDownKey.IsKeyReleased() == true)
    {
	if (select < Select::QUIT)
	{
	    select++;
	}
	else if (select == Select::QUIT)
	{
	    select = Select::RESUME;
	}
    }
    else if (OptionSelectKey.IsKeyDown() == true)
    {
	switch (select)
	{
	case RESUME:
            Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
	    break;
	case RESTART:
	    Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Level1));
	    break;
	case MAINMENU:
	    Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
	    break;
	case QUIT:
	    Engine::GetGameStateManager().Shutdown();
	    break;
	default:
	    break;
	}
    }
}

int Option::GetSelect()
{
	return select;
}

bool Option::IsInBox(glm::vec2 pos)
{
    if (pos.x + 1 > mousePosition.x &&
	pos.x - 1 < mousePosition.x &&
	pos.y + 1 > mousePosition.y &&
	pos.y - 1 < mousePosition.y)
    {
	return true;
    }
    return false;
}

void Option::Unload()
{

}
