/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tutorial_Helper.cpp
Project: BIT_SAVER
Author: Hyosang Jung
Creation date: 5/01/2021
-----------------------------------------------------------------*/
#include "Tutorial_Helper.h"
#include "../Engine/Engine.h"
#include "Notes.h"
#include"../../Engine/Sprite/GameParticles.h"

std::string messages[] = {
	"Hello",
	"I will explain how to play",
	"This game is rhythm game",
	"Rainbow box is hit box",
	"Each color represents different accuracy",
	"This is up note",
	"Press F to hit note",
	"This is dow note",
	"Press J to hit note",
	"Good",
	"There are many fun things in the game",
	"You can change attack key in Option",
	"Let's play First Level"
};
Tutorial_Helper::Tutorial_Helper():
	nextKey(InputKey::Keyboard::Enter)
{
	sound_bar = Engine::GetTextureManager().Load("../images/sound_bar.png");
	helper = Engine::GetTextureManager().Load("../images/helper.png");
	currstate = 0;
	index = 0;
}

void Tutorial_Helper::AddScore(int )
{
	
}

void Tutorial_Helper::Draw( )
{
	RenderText();
}

void Tutorial_Helper::Set_state(int state)
{
	currstate = state;
}

void Tutorial_Helper::Setflag(bool value)
{
	flag = value;
}

bool Tutorial_Helper::Getflag()
{
	return flag;
}

void Tutorial_Helper::RenderText()
{
	winsize = Engine::GetWindow().GetSize();
	const std::string font2{ font_path[PressStart] };
	sound_bar_pos.x = 0;
	sound_bar_pos.y = -8;

	if (nextKey.IsKeyReleased() == true)
	{
		if (index != 6)
		{
			index++;
		}
	}

	switch (currstate)
	{
	case 0: //Greetings
	{
		helper->Draw({ -6,-8 }, { 2,2 });
		sound_bar->Draw(0.5,sound_bar_pos, { 10,2 });
		Engine::GetText(font2).Draw(messages[index], winsize.x * 0.4f, winsize.y * 0.9f, 1.f, glm::vec3(1.f, 1.f, 1.f));
		Engine::GetText(font2).Draw("Press Enter ", winsize.x * 0.7f, winsize.y * 0.95f, 1.f, glm::vec3(1.f, 1.f, 1.f));
		if (index > 2)
		{
			Setflag(true);
		}
		break;
	}
	case 2: //NOTE_HIT
	{
		helper->Draw({ -6,-8 }, { 2,2 });
		sound_bar->Draw(0.5, sound_bar_pos, { 10,2 });

		Engine::GetText(font2).Draw(messages[index], winsize.x * 0.4f, winsize.y * 0.9f, 1.f, glm::vec3(1.f, 1.f, 1.f));
		if (index != 6)
		{
			Engine::GetText(font2).Draw("Press Enter ", winsize.x * 0.7f, winsize.y * 0.95f, 1.f, glm::vec3(1.f, 1.f, 1.f));
		}
		if (index == 6)
		{
			if (InputKey(InputKey::Keyboard::F).IsKeyReleased() == true)
			{
				Engine::GetGSComponent<HitEmitter>()->Emit(1, { -4,5 }, { 0,0 }, { 0,0 }, 0);
				Engine::GetGSComponent<PerfectEmitter>()->Emit(1, { -4,5 }, { -4,2 }, { 0,0 }, 0);
				index++;
			}
		}
		if (index > 6)
		{
			Setflag(true);
		}
		break;
	}
	case 4: //NOTE_Down
	{
		helper->Draw({ -6,-8 }, { 2,2 });
		sound_bar->Draw(0.5, sound_bar_pos, { 10,2 });

		Engine::GetText(font2).Draw(messages[index], winsize.x * 0.4f, winsize.y * 0.9f, 1.f, glm::vec3(1.f, 1.f, 1.f));
		if (index != 8)
		{
			Engine::GetText(font2).Draw("Press Enter ", winsize.x * 0.7f, winsize.y * 0.95f, 1.f, glm::vec3(1.f, 1.f, 1.f));
		}
		if (index == 8)
		{
			if (InputKey(InputKey::Keyboard::J).IsKeyReleased() == true)
			{
				
				Engine::GetGSComponent<HitEmitter>()->Emit(1, { -4,-5 }, { 0,0 }, { 0,0 }, 0);
				Engine::GetGSComponent<PerfectEmitter>()->Emit(1, { -4,-5 }, { -4,2 }, { 0,0 }, 0);
				index++;
			}
		}
		if (index > 8)
		{
			Setflag(true);
		}
		break;
	}
	case 5: //End
	{
		helper->Draw({ -6,-8 }, { 2,2 });
		sound_bar->Draw(0.5, sound_bar_pos, { 10,2 });
		Engine::GetText(font2).Draw("Press Enter ", winsize.x * 0.7f, winsize.y * 0.95f, 1.f, glm::vec3(1.f, 1.f, 1.f));

		Engine::GetText(font2).Draw(messages[index], winsize.x * 0.4f, winsize.y * 0.9f, 1.f, glm::vec3(1.f, 1.f, 1.f));

		if (index > 12)
		{
			Setflag(true);
		}
		break;
	}
	default: 
		break;
	}
}