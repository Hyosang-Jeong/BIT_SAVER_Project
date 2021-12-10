/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tracks.cpp
Project: BIT_SAVER
Author: 
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"Track.h"
#include"..\..\Engine\Music\Midi.h"
#include<algorithm>
#include"..\..\Engine/Engine.h"
#include "..\..\Engine\Music\Sound_Num.h"
#include"Notes.h"
#include "../Levels/Offset.h"
#include "../Levels/MainOption.h"


Track::Track(int music_num) :
	Track(MidiEvent{}.MidiSetUp(music_num), music_num)
{
}

Track::Track(std::map<int,std::vector<long double>> mid_info , int music_num) : 
GameObject({ 0,0 },  glm::vec2{ 0.1,0.1 }), Music_Num(music_num)
{
	Doupdate = true;

    long double Dificulty{ 0.0 };

	switch (Music_Num)
	{
	    case static_cast<int>(SOUND_NUM::OFFSET) :
			Dificulty = 0.0001;
			break;
	    case static_cast<int>(SOUND_NUM::DISCO) :
			Dificulty = 0.000001;
			break;
	    case static_cast<int>(SOUND_NUM::REWIND) :
			Dificulty = 0.3;
			break;
		case static_cast<int>(SOUND_NUM::DIOMA):
			Dificulty = 0.1;
			break;
		case static_cast<int>(SOUND_NUM::ENERGY):
			Dificulty = 0.1;
			break;
		default:
			break;
	}

	for (auto& tracks : mid_info)
	{
		for (auto& time_t : tracks.second)
		{
			track_time.push_back(Track_Time(tracks.first, time_t));
		}
	}

	std::sort(begin(track_time), end(track_time), [](Track_Time left, Track_Time right)
		{
			return (left.time < right.time);
		}
	);


	long double t{ track_time[0].time };
	track_time.erase(std::remove_if(begin(track_time) + 1, end(track_time), [&](Track_Time time_t)
		{
			if (time_t.time - t < Dificulty)
			{
				return true;
			}
			else {
				t = time_t.time;
				return false;
			}
		}), end(track_time));

	
	double target_time = 10.0 / -20;
	for (auto& tt : track_time)
	{
	    if (static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->GetOffsetTime() > -10)
		tt.time += target_time - static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->GetOffsetTime();
	    else
		tt.time += target_time;
	}
	Engine::GetLogger().LogEvent("Your off set is " + std::to_string(static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->GetOffsetTime()));
	if (Music_Num == static_cast<int>(SOUND_NUM::REWIND) || Music_Num == static_cast<int>(SOUND_NUM::ENERGY))
	{
		for (auto& time_t : track_time)
		{
			int T = static_cast<int>(time_t.time * 10000);
			if (T % 2 == 0)
			{
				track_info[T % 2].push_back(time_t.time);
			}
			else if (T % 2 == 1)
			{
				track_info[T % 2].push_back(time_t.time);
			}
		}
	}
	else if (Music_Num == static_cast<int>(SOUND_NUM::OFFSET))
	{
		int T = 0;
		for (auto& time_t : track_time)
		{
			if (T % 2 == 0)
			{
				track_info[T % 2].push_back(time_t.time);
			}
			else if (T % 2 == 1)
			{
				track_info[T % 2].push_back(time_t.time);
			}
			T++;
		}
	}
}


void Track::Update(double dt)
{
	if (Doupdate == true)
	{
		GameObject::Update(dt);

		timer += dt * Engine::GetMusic().pitch;

		if (Music_Num == static_cast<int>(SOUND_NUM::REWIND) || Music_Num == static_cast<int>(SOUND_NUM::ENERGY) || Music_Num == static_cast<int>(SOUND_NUM::OFFSET))
		{
			for (auto& i : track_info)
			{
				for (auto& j : i.second)
				{
					if (timer > j)
					{
						note_pos = { 10, (i.first - 0.5) * 10 };
						note_vel = { -20,0 };
						Engine::GetGSComponent<GameObjectManager>()->Add(new Note(note_pos, note_vel));
						i.second.erase(i.second.begin());
					}
				}
			}
		}
		else
		{
			for (auto& i : track_time)
			{
				if (timer > i.time)
				{
					note_pos = { 10, ((i.track - 1) - 0.5) * 10 };
					note_vel = { -20,0 };
					Engine::GetGSComponent<GameObjectManager>()->Add(new Note(note_pos, note_vel));
					track_time.erase(track_time.begin());
				}
			}
		}
	}
}

glm::vec2 Track::Getposition()
{
	return GameObject::GetPosition();
}

void Track::SetUpdate(bool update)
{
	Doupdate = update;
}

