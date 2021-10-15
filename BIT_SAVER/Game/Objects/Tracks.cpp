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
#include"../Engine/Engine.h" //get window
#include"Notes.h"


Track::Track(std::map<int, std::vector<long double>> mid_info) : GameObject({ 0,0 }, 0, glm::vec2{ 0.1,0.1 })
{

	std::vector<long double> time;

	for (auto& track : mid_info)
	{
		for (auto& time_t : track.second)
		{
			time.push_back(time_t);
		}
	}
	std::sort(begin(time), end(time));

	long double t{ time[0] };
	time.erase(std::remove_if(begin(time) + 1, end(time), [&](auto time_t)
		{
			if (time_t - t < 0.35)
				return true;
			else {
				t = time_t;
				return false;
			}
		}), end(time));

	double target_time = 14.0 / -10;

	for (auto& time_t : time)
	{
		int T = static_cast<int>(time_t * 10000);
		if (T % 2 == 0)
			track_info[T % 2].push_back(time_t+ target_time);
		if (T % 2 == 1)
			track_info[T % 2].push_back(time_t+ target_time);
	}

}


void Track::Update(double dt)
{
	GameObject::Update(dt);

	timer += dt;

	for (auto& i : track_info)
	{
		for (auto& j : i.second)
		{
			if (timer > j)
			{
				//0 ->-5    1-> 5
				Engine::GetGameStateManager().gameObjectManager.Add(new Note({ 10, (i.first-0.5) * 10 }, { -10,0 }));
				//std::cout << "Track num: "<<track_num << "      time: " << i << "       timer: " << timer << std::endl;
				i.second.erase(i.second.begin());
			}
		}
	}

}

void Track::Draw()
{
}


glm::vec2 Track::Getposition()
{
	return GameObject::GetPosition();
}
