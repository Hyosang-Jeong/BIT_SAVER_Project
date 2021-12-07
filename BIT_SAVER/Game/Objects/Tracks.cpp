/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: BIT_SAVER
Author: 
Creation date: 3/14/2021
-----------------------------------------------------------------*/
#include"Track.h"
#include"..\..\Engine\Music\Midi.h"
#include<algorithm>
#include"../../Engine/Engine.h"
#include"Notes.h"



Track::Track(int music_num) :  
Track(MidiEvent{}.MidiSetUp(music_num))
{}

Track::Track(std::map<int,std::vector<long double>> mid_info) : 
GameObject({ 0,0 },  glm::vec2{ 0.1,0.1 })
{
	Doupdate = true;

	//std::vector<Track_Time> track_time;

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
			if (time_t.time - t < 0.0000001)
			{
				return true;
			}
			else {
				t = time_t.time;
				return false;
			}
		}), end(track_time));










	//std::vector<long double> time;

	//for (auto& tracks : mid_info)
	//{
	//	for (auto& time_t : tracks.second)
	//	{
	//		time.push_back(time_t);
	//	}
	//	
	//}
	//std::sort(begin(time), end(time));

	//long double t{ time[0] };
	//time.erase(std::remove_if(begin(time) + 1, end(time), [&](auto time_t)
	//	{
	//		if (time_t - t < 0.3)
	//		{
	//			return true;
	//		}
	//		else {
	//			t = time_t;
	//			return false;
	//		}
	//	}), end(time));

	double target_time = 14.0 / -20;
	for (auto& tt : track_time)
	{
		tt.time += target_time;
	}

	//std::copy(list_track_time.begin(), list_track_time.end(), std::back_inserter(track_time));
	//for (auto& a : track_time)
	//{
	//	list_track_time.push_back(a);
	//}


	//for (auto& time_t : time)
	//{
	//	int T = static_cast<int>(time_t * 10000);
	//	if (T % 2 == 0)
	//	{
	//		track_info[T % 2].push_back(time_t + target_time);
	//	}
	//	else if (T % 2 == 1)
	//	{
	//		track_info[T % 2].push_back(time_t + target_time);
	//	}
	//}

}


void Track::Update(double dt)
{
	if (Doupdate == true)
	{
		GameObject::Update(dt);

		timer += dt * Engine::GetMusic().pitch;

		/*for (auto& i : track_info)
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
		}*/
		/*for (auto& i : track_time)
		{
			for (auto& j : i.time)
			{
				if (timer > j)
				{
					note_pos = { 10, (i.track - 0.5) * 10 };
					note_vel = { -20,0 };
					Engine::GetGSComponent<GameObjectManager>()->Add(new Note(note_pos, note_vel));
					i.second.erase(i.second.begin());
				}
			}
		}*/
		for (auto& i : track_time)
		{
			if (timer > i.time)
			{
				note_pos = { 10, ((i.track-1) - 0.5) * 10 };
				note_vel = { -20,0 };
				Engine::GetGSComponent<GameObjectManager>()->Add(new Note(note_pos, note_vel));
				//i.second.erase(i.second.begin());
				//list_track_time.pop_front();
				track_time.erase(track_time.begin());
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
