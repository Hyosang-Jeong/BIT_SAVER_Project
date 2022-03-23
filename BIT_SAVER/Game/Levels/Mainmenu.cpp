/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mainmenu.cpp
Project: BIT_SAVER
Author:	Hyun Kang
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Mainmenu.h"
#include"State.h"
#include"../../Engine/Sprite/Texture.h"
Mainmenu::Mainmenu() :
	Next(InputKey::Keyboard::Down),
	Previous(InputKey::Keyboard::Up),
	Select(InputKey::Keyboard::Enter),
	currstate(static_cast<int>(state::START)),
	escape(InputKey::Keyboard::Escape),
	updown_pos(10,-10)
{
}

void Mainmenu::Load()
{
	mainmenu = Engine::GetTextureManager().Load("../images/mainmenu.png");
	gamelogo = Engine::GetTextureManager().Load("../images/gamelogo.png");
	levels = Engine::GetTextureManager().Load("../images/mainmenu_level.png");
	option = Engine::GetTextureManager().Load("../images/mainmenu_option.png");
	option_button = Engine::GetTextureManager().Load("../images/mainmenu_optionindex.png");
	level_1 = Engine::GetTextureManager().Load("../images/mainmenu_level1.png");
	level_2 = Engine::GetTextureManager().Load("../images/mainmenu_level2.png");
	level_3 = Engine::GetTextureManager().Load("../images/mainmenu_level3.png");
	level_4 = Engine::GetTextureManager().Load("../images/mainmenu_level4.png");
}

void Mainmenu::Update([[maybe_unused]] double dt)
{
	if (escape.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}

	if (currstate > static_cast<int>(state::START))
	{
		if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && Next.IsKeyReleased() == true)
		{
			currstate++;
			if (currstate == static_cast<int>(state::OPTION) + 1)
			{
				currstate = static_cast<int>(state::TUTORIAL);
			}
		}
		else if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && Previous.IsKeyReleased() == true)
		{
			currstate--;
			if (currstate == static_cast<int>(state::TUTORIAL) - 1)
			{
				currstate = static_cast<int>(state::OPTION);
			}
		}
		else if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && Select.IsKeyReleased() == true)
		{
			switch (currstate)
			{
			case 3:
			{
				Engine::GetGameStateManager().SetNextState(4);
				break;
			}
			case 4:
			{
				Engine::GetGameStateManager().SetNextState(5);
				break;
			}
			case 5:
			{
				Engine::GetGameStateManager().SetNextState(6);
				break;
			}
			case 6:
			{
				Engine::GetGameStateManager().SetNextState(7);
				break;
			}
			case 7:
			{
				Engine::GetGameStateManager().SetNextState(2);
				break;
			}
			default:
				break;
			}
		}
	}
	
	 if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && currstate == (static_cast<int>(state::START)))
	 {
		 currstate++;
		 Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
	 }
	alpha += static_cast<float>(dt)/2.0f;
	if (currstate > (static_cast<int>(state::START)))
	{
		updown_pos.x -= static_cast<float>(dt)*10.f;
		updown_pos.y += static_cast<float>(dt)*10.f;
		if (updown_pos.x < 0)
		{
			updown_pos.x = 0;
			updown_pos.y = 0;
		}
	}
}

void Mainmenu::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat3 camera = {
		1,0,0,
		0,1,0,
		0,0,1
	};
	mainmenu->Draw(alpha, camera, { 0,0 }, { 10,10 });
	gamelogo->Draw({ 0,0 }, { 10,10 });
	const std::string font1{ font_path[PressStart] };
	glm::vec2 winsize = Engine::GetWindow().GetSize();
	
	if (currstate > static_cast<int>(state::START))
	{
		levels->Draw({ 0,updown_pos.x }, { 10,10 });
		option->Draw({ 0,updown_pos.y }, { 10,10 });
	}
	switch (currstate)
	{
		case static_cast<int>(state::TUTORIAL):
		{
			if(updown_pos.x == 0)
				level_1->Draw({ 0,0 }, { 10,10 });
			break;
		}
		case static_cast<int>(state::LEVEL1):
		{
			level_2->Draw({ 0,0 }, { 10,10 });
			break;
		}
		case static_cast<int>(state::LEVEL2):
		{
			level_3->Draw({ 0,0 }, { 10,10 });
			break;
		}
		case static_cast<int>(state::LEVEL3):
		{
			level_4->Draw({ 0,0 }, { 10,10 });
			break;
		}
		case static_cast<int>(state::OPTION):
		{
			option_button->Draw({ 0,0 }, { 10,10 });
			break;
		}
		default:
			break;
	}
	
}
void Mainmenu::Unload()
{
}
