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

#define DISCO_OFFSET 0
#define REWIND_OFFSET 26
#define DIOMA_OFFSET 0
#define ENERGY_OFFSET 12


Mainmenu::Mainmenu() :
	Next(InputKey::Keyboard::Down),
	Previous(InputKey::Keyboard::Up),
	Select(InputKey::Keyboard::Enter),
	T(InputKey::Keyboard::T),
	Right(InputKey::Keyboard::Right),
	Left(InputKey::Keyboard::Left),
	currstate(static_cast<int>(state::START)),
	previous_state(currstate),
	escape(InputKey::Keyboard::Escape),
	updown_pos(10,-10),escape_game(false)
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
	LP = Engine::GetTextureManager().Load("../images/LP.png");
	LP_2 = Engine::GetTextureManager().Load("../images/LP.png");
	Quit_screen = Engine::GetTextureManager().Load("../images/Quit.png");
	Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
	is_selected  = false;
}

void Mainmenu::Update( double dt)
{
	lp_rotate += 30 * dt;
	//text alpha
	if (currstate == static_cast<int>(state::START))
	{
		timer += dt;
		if (Engine::GetMusic().isPlaying(SOUND_NUM::INTRO1) == false)
		{
			Engine::GetMusic().Play(SOUND_NUM::INTRO1);
		}
		if (Engine::GetMusic().isPlaying(SOUND_NUM::INTRO2) == false)
		{
		    Engine::GetMusic().Play(SOUND_NUM::INTRO2);
		}
		if (Engine::GetMusic().isPlaying(SOUND_NUM::INTRO3) == false)
		{
		    Engine::GetMusic().Play(SOUND_NUM::INTRO3);
		}
	}
	if (timer < 0.5)
	{
		text_alpha = 0.5;
	}
	else 
	{
		text_alpha = 1;
		if(timer > 1)
			timer = 0;
	}
	if (T.IsKeyReleased() == true)
	{
		stop_music(currstate);
		Engine::GetGameStateManager().SetNextState(3);
	}


	if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && escape.IsKeyReleased() == true)
	{
		if (currstate != static_cast<int>(state::ESCAPE))
		{
			previous_state = currstate;
			stop_music(currstate);
			escape_game = false;
			currstate = static_cast<int>(state::ESCAPE);
		}
		else
		{
			currstate = previous_state;
			play_music(currstate);
		}
	}

	if (currstate == static_cast<int>(state::ESCAPE))
	{
		if (Right.IsKeyReleased() || Left.IsKeyReleased())
		{
			Engine::GetMusic().Play(SOUND_NUM::MENU_MOVE);
			escape_game = !escape_game;
		}
	}

	if (currstate > static_cast<int>(state::START))
	{
		if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && Next.IsKeyReleased() == true)
		{
			if (is_selected == false)
			{
				Engine::GetMusic().Play(SOUND_NUM::MENU_MOVE);
				if (currstate != static_cast<int>(state::ESCAPE))
				{
					stop_music(currstate);
					currstate++;
					if (currstate == static_cast<int>(state::OPTION) + 1)
					{
						currstate = static_cast<int>(state::TUTORIAL);
					}
					play_music(currstate);
				}
			}
		}
		else if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && Previous.IsKeyReleased() == true)
		{
			if (is_selected == false)
			{
				Engine::GetMusic().Play(SOUND_NUM::MENU_MOVE);
				if (currstate != static_cast<int>(state::ESCAPE))
				{
					stop_music(currstate);
					currstate--;
					if (currstate == static_cast<int>(state::TUTORIAL) - 1)
					{
						currstate = static_cast<int>(state::OPTION);
					}
					play_music(currstate);
				}
			}
		}
		else if (is_selected == false && Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && Select.IsKeyReleased() == true)
		{
			Engine::GetMusic().Play(SOUND_NUM::MENU_SELECT);
			switch (currstate)
			{
			case 3:
			{
				stop_music(currstate);
				Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
				is_selected = true;
				/*difficulty_select();
				Engine::GetGameStateManager().SetNextState(4);*/
				break;
			}
			case 4:
			{
				stop_music(currstate);
				Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
				is_selected = true;
				//difficulty_select();
				//Engine::GetGameStateManager().SetNextState(5);
				break;
			}
			case 5:
			{
				stop_music(currstate);
				Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
				is_selected = true;
				//difficulty_select();
				//Engine::GetGameStateManager().SetNextState(6);
				break;
			}
			case 6:
			{
				stop_music(currstate);
				Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
				is_selected = true;
				//difficulty_select();
				//Engine::GetGameStateManager().SetNextState(7);
				break;
			}
			case 7:
			{
				stop_music(currstate);
				Engine::GetGameStateManager().SetNextState(2);
				break;
			}
			case 8:
			{
				if (escape_game == true)
					Engine::GetGameStateManager().Shutdown();
				else
				{
					currstate = previous_state;
					play_music(currstate);
					break;
				}
			}
			default:
				break;
			}
		}
	}
	
	 if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && currstate == (static_cast<int>(state::START)))
	 {
		 Engine::GetMusic().Stop(SOUND_NUM::INTRO1);
		 Engine::GetMusic().Stop(SOUND_NUM::INTRO2);
		 Engine::GetMusic().Stop(SOUND_NUM::INTRO3);
		 currstate++;
		 play_music(currstate);
		 Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
	 }
	alpha += static_cast<float>(dt)/3.0f;

	if (currstate > (static_cast<int>(state::START)))
	{
		updown_pos.x -= static_cast<float>(dt)*25.f;
		updown_pos.y += static_cast<float>(dt)*25.f;
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
	glm::vec2 winsize = Engine::GetWindow().GetSize();
	const std::string font1{ font_path[PressStart] };
	glm::mat3 camera =
	{
		1,0,0,
		0,1,0,
		0,0,1
	};
	mainmenu->Draw(alpha, camera, { 0,0 }, { 10,10 });
	

	if (currstate ==  static_cast<int>(state::START))
	{
		gamelogo->model.shdr_pgm.Use();
		gamelogo->model.shdr_pgm.SetUniform("Logo", 1);
		gamelogo->model.shdr_pgm.SetUniform("time", static_cast<float>(glfwGetTime()));
		gamelogo->Draw({ 0,0 }, { 10,10 });

		Engine::GetText(font1).Draw("Press any key to start", winsize.x * 0.38f, winsize.y * 0.9f, 1.f, glm::vec3(text_alpha, text_alpha, text_alpha));
	}
	
	if (currstate > static_cast<int>(state::START))
	{
		levels->Draw({ 0,updown_pos.x }, { 10,10 });
		option->Draw({ 0,updown_pos.y }, { 10,10 });
	}
	if (updown_pos.y == 0)
	{
		LP->Draw({ 1.25,5.28 }, { 0.5,0.73 }, { lp_rotate,0 });
		LP_2->Draw({ 2.5,2.0 }, { 0.45,0.7 }, { lp_rotate,0 });
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
		case static_cast<int>(state::ESCAPE):
		{
			if (is_selected == false)
			{
				Quit_screen->Draw({ 0,0 }, { 10,5 });
				Engine::GetText(font1).Draw("Do you want to Quit?", winsize.x * 0.32f, winsize.y * 0.41f, 1.5f, glm::vec3(1.f, 1.f, 1.f));

				Engine::GetText(font1).Draw("YES", winsize.x * 0.35f, winsize.y * 0.55f, 1.5f, glm::vec3(0.5f, 0.5f, 0.5f));
				Engine::GetText(font1).Draw("NO", winsize.x * 0.6f, winsize.y * 0.55f, 1.5f, glm::vec3(0.5f, 0.5f, 0.5f));
				if (escape_game == true)
					Engine::GetText(font1).Draw("YES", winsize.x * 0.35f, winsize.y * 0.55f, 1.5f, glm::vec3(1.f, 1.f, 1.f));
				else
					Engine::GetText(font1).Draw("NO", winsize.x * 0.6f, winsize.y * 0.55f, 1.5f, glm::vec3(1.f, 1.f, 1.f));
			}
			else
			{
				currstate = previous_state;
			}
			break;
		}
		default:
			break;
	}

	difficulty_select();
}
void Mainmenu::play_music(int num)
{
	if (num >= 3 || num <= 7)
	{
			switch (num)
			{
			case 3:
				Engine::GetMusic().Play(num - 2);
				Engine::GetMusic().Setposition(num - 2, DISCO_OFFSET);
				break;
			case 4:
				Engine::GetMusic().Play(num - 2);
				Engine::GetMusic().Setposition(num - 2, REWIND_OFFSET);
				break;
			case 5:
				Engine::GetMusic().Play(num - 2);
				Engine::GetMusic().Setposition(num - 2, DISCO_OFFSET);
				break;
			case 6:
				Engine::GetMusic().Play(num - 2);
				Engine::GetMusic().Setposition(num - 2, ENERGY_OFFSET);
				break;
			case 7:
				Engine::GetMusic().Play(0);
				break;
			default:
				break;
			}		
			
	}
}
void Mainmenu::stop_music(int num)
{
	if (num >= 3 || num <= 7)
	{
		if (num != 7)
		{
			if (Engine::GetMusic().isPlaying(num - 2) == true)
			{
				Engine::GetMusic().Setposition(num - 2, 0);
				Engine::GetMusic().Stop(num - 2);
			}
		}
		else if (num == 7)
		{
			if (Engine::GetMusic().isPlaying(0) == true)
			{
				Engine::GetMusic().Stop(0);
			}
		}
	}
}

void Mainmenu::difficulty_select()
{

	const std::string font{ font_path[MochiyPopOne] };

	glm::vec2 winsize = Engine::GetWindow().GetSize();

	if (is_selected)
	{
		Quit_screen->Draw({ 0,0 }, { 10,5 });
		if (Right.IsKeyReleased() || Left.IsKeyReleased())
		{
			Engine::Instance().SetDifficulty(!Engine::Instance().GetDifficulty());
		}

		if (escape.IsKeyReleased())
		{
			is_selected = false;
			Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
		}
		Engine::GetText(font).Draw("Easy", winsize.x * 0.32f, winsize.y * 0.50f, 1.5f, glm::vec3(0.5f, 0.5f, 0.5f));
		Engine::GetText(font).Draw("Hard", winsize.x * 0.55f, winsize.y * 0.50f, 1.5f, glm::vec3(0.5f, 0.5f, 0.5f));
		if (Engine::Instance().GetDifficulty() == true)
			Engine::GetText(font).Draw("Easy", winsize.x * 0.32f, winsize.y * 0.50f, 1.5f, glm::vec3(1.f, 1.f, 1.f));
		else
			Engine::GetText(font).Draw("Hard", winsize.x * 0.55f, winsize.y * 0.50f, 1.5f, glm::vec3(1.f, 1.f, 1.f));

		if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None && Select.IsKeyReleased() == true)
		{
			switch (currstate)
			{
			case 3:
			{
				Engine::GetGameStateManager().SetNextState(4);
				is_selected = false;
				break;
			}
			case 4:
			{
				Engine::GetGameStateManager().SetNextState(5);
				is_selected = false;
				break;
			}
			case 5:
			{
				Engine::GetGameStateManager().SetNextState(6);
				is_selected = false;
				break;
			}
			case 6:
			{
				Engine::GetGameStateManager().SetNextState(7);
				is_selected = false;
				break;
			}
			}
		}

	}

}
//todo
void Mainmenu::Unload()
{
}
