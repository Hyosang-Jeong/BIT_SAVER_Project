/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tracks.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Sunwoo Lee

-----------------------------------------------------------------*/
#include"Track.h"

#include<algorithm>
#include"..\..\Engine/Engine.h"
#include "..\..\Engine\Music\Sound_Num.h"
#include "../Levels/Offset.h"
#include "../Levels/MainOption.h"
//#include"Notes.h"
#include "NoteUp.h"
#include "NoteHard.h"
#include"NoteDown.h"

Track::Track(int music_num) :
    Track(MidiEvent{}.MidiSetUp(music_num), music_num) {}

Track::Track(std::map<int, std::vector<info>> mid_info, int music_num) :
    GameObject({ 0,0 }, glm::vec2{ 0.1,0.1 }), Music_Num(music_num), UpAttackKey(InputKey::Keyboard::None),
    DownAttackKey(InputKey::Keyboard::None)
{
    if (Engine::Instance().GetDifficulty())
        target_time = 14.0 / -10.0;
    else
        target_time = 14.0 / -20.0;

    Doupdate = true;
    UpAttackKey = Engine::GetAttack_Key().UpAttackKey;
    DownAttackKey = Engine::GetAttack_Key().DownAttackKey;
    long double Dificulty{ 0.0 };
    if (Engine::Instance().GetDifficulty())
    {
    switch (Music_Num)
    {
        case static_cast<int>(SOUND_NUM::OFFSET) :
    		Dificulty = 0.0001;
    		break;
        case static_cast<int>(SOUND_NUM::DISCO) :
    		Dificulty = 0.5;
    		break;
        case static_cast<int>(SOUND_NUM::REWIND) :
    		Dificulty = 0.3;
    		break;
    	case static_cast<int>(SOUND_NUM::DIOMA) :
    		Dificulty = 0.4;
    		break;
    	case static_cast<int>(SOUND_NUM::ENERGY) :
    		Dificulty = 0.3;
    		break;
    	default:
    		break;
    }

    }

    std::vector<Track_Time> tmp;
    for (auto& tracks : mid_info)
    {
        for (auto& time_t : tracks.second)
        {
            if (time_t.dt_to_seconds < 0)		// if time is less than 0 for some reason ( -(time from pos10 to pos-4) or -(offset))
            {
                continue;
            }
            tmp.push_back(Track_Time(tracks.first, time_t.dt_to_seconds, time_t.movement));
        }
    }
    std::sort(begin(tmp), end(tmp), [](Track_Time left, Track_Time right)
        {
            return (left.time < right.time);
        }
    );

    long double t{ tmp[0].time };
    tmp.erase(std::remove_if(begin(tmp) + 1, end(tmp), [&](Track_Time time_t)
        {
            if (time_t.time - t < Dificulty)
            {
                return true;
            }
            else {
                t = time_t.time;
                return false;
            }
        }), end(tmp));


    for (auto& tt : tmp)
    {
        if (static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->GetOffsetTime() > -10)
            tt.time += target_time - static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->GetOffsetTime();
        else
            tt.time += target_time;
    }
    Engine::GetLogger().LogEvent("Your off set is " + std::to_string(static_cast<MainOption*>(Engine::GetGameStateManager().Find("MainOption"))->GetOffsetTime()));
    for (auto& i : tmp)
    {
        if (i.time > 0)
            track_time.push(i);
    }

    //if (Music_Num == static_cast<int>(SOUND_NUM::REWIND) || Music_Num == static_cast<int>(SOUND_NUM::ENERGY))
    //{
    //	for (auto& time_t : track_time)
    //	{
    //		int T = static_cast<int>(time_t.time * 10000);
    //		if (T % 2 == 0)
    //		{
    //			track_info[T % 2].push_back(time_t.time);
    //		}
    //		else if (T % 2 == 1)
    //		{
    //			track_info[T % 2].push_back(time_t.time);
    //		}
    //	}
    //}
    //if (Music_Num == static_cast<int>(SOUND_NUM::OFFSET))
    //{
    //	int T = 0;
    //	for (auto& time_t : track_time)
    //	{
    //		if (T % 2 == 0)
    //		{
    //			track_info[T % 2].push_back(info(time_t.time,time_t.movement));
    //		}
    //		else if (T % 2 == 1)
    //		{
    //			track_info[T % 2].push_back(info(time_t.time, time_t.movement));
    //		}
    //		T++;
    //	}
    //}
}


void Track::Update(double dt)
{
    UpAttackKey = Engine::GetAttack_Key().UpAttackKey;
    DownAttackKey = Engine::GetAttack_Key().DownAttackKey;
    if (Doupdate == true)
    {
        GameObject::Update(dt);

        timer += dt * Engine::GetMusic().pitch;
        pitch_timer += dt;
        //if ( Music_Num == static_cast<int>(SOUND_NUM::OFFSET))
        //{
        //	for (auto& i : track_info)
        //	{
        //		for (auto& j : i.second)
        //		{
        //			if (timer > j.dt_to_seconds)
        //			{
        //				note_pos = { 10, (i.first - 0.7) * 10 };
        //				note_vel = { -20,0 };
        //				if (note_pos.y < 0)
        //				{
        //					Engine::GetGSComponent<GameObjectManager>()->Add(new DownNote(note_pos, note_vel, j.movement));
        //				}
        //				else
        //				{
        //					Engine::GetGSComponent<GameObjectManager>()->Add(new UpNote(note_pos, note_vel, j.movement));
        //				}
        //				i.second.erase(i.second.begin());
        //			}
        //		}
        //	}
        //}
        //else
        //{
        while (true)
        {

            if (track_time.empty() != true)
            {
                Track_Time tmp = track_time.front();
                if (timer >= tmp.time)
                {
                    note_pos = { 10, ((tmp.track - 1) - 0.7) * 10 };
                    if (Engine::Instance().GetDifficulty())
                        note_vel = { -10,0 };
                    else
                        note_vel = { -20,0 };

                    switch (tmp.track)
                    {
                    case 1:
                    {
                        GameObject* down_tmp = new DownNote(note_pos, note_vel, tmp.movement);
                        Engine::GetGSComponent<GameObjectManager>()->Add(down_tmp);
                        time.push(tmp.time);
                        notes.push(down_tmp);
                        break;
                    }
                    case 2:
                    {
                        GameObject* up_tmp = new UpNote(note_pos, note_vel, tmp.movement);
                        Engine::GetGSComponent<GameObjectManager>()->Add(up_tmp);
                        time.push(tmp.time);
                        notes.push(up_tmp);
                        break;
                    }
                    case 3:
                    {
                        note_pos = { 10, -2 };
                        GameObject* hard_tmp = new HardNote(note_pos, note_vel, 1);
                        Engine::GetGSComponent<GameObjectManager>()->Add(hard_tmp);
                        time.push(tmp.time);
                        notes.push(hard_tmp);
                        break;
                    }

                    default: break;
                    }
                    track_time.pop();
                }
                else
                    break;
            }

            else
                break;
        }
        hit_check();

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

void Track::hit_check()
{
    double miss_time;
    if (Engine::Instance().GetDifficulty())
        miss_time = 16.0 / -10;
    else
        miss_time = 16.0 / -20;
    while (true)
    {
        if (time.empty() == false) //for miss any note
        {
            long double  tmp = (time.front()) - (miss_time * Engine::GetMusic().pitch);
            if (timer >= (tmp))
            {
                GameObject* note_tmp = notes.front();
                notes.pop();
                time.pop();
                if (note_tmp->GetPosition().y > -2)
                {
                    static_cast<UpNote*>(note_tmp)->Score_Check(0);
                    break;
                }
                else
                {
                    static_cast<DownNote*>(note_tmp)->Score_Check(0);
                    break;
                }
            }
            else
                break;
        }
        else
            break;
    }

    if ((UpAttackKey.IsKeyDown() == true && UpAttackKey.IsKeyReapeated() == false))
    {
        while (true)
        {
            if (time.empty() == false)
            {
                long double  tmp = time.front() - (target_time * Engine::GetMusic().pitch);

                if (timer - (tmp) <= 0.05 && timer - (tmp) >= -0.05)
                {
                    GameObject* note_tmp = notes.front();
                    if (note_tmp->GetPosition().y > -2)
                    {
                        notes.pop();
                        time.pop();
                        static_cast<UpNote*>(note_tmp)->Score_Check(3);
                        break;
                    }
                    else if (note_tmp->GetPosition().y == -2)
                    {
                        notes.pop();
                        time.pop();
                        break;
                    }
                    else
                        break;
                }

                else if (timer - (tmp) <= 0.13 && timer - (tmp) >= -0.13)
                {
                    GameObject* note_tmp = notes.front();
                    if (note_tmp->GetPosition().y > -2)
                    {
                        notes.pop();
                        time.pop();
                        static_cast<UpNote*>(note_tmp)->Score_Check(2);
                        break;
                    }
                    else if (note_tmp->GetPosition().y == -2)
                    {
                        notes.pop();
                        time.pop();
                        break;
                    }
                    else
                        break;
                }


                else
                    break;
            }
            else
                break;
        }
    }


    if (DownAttackKey.IsKeyDown() == true && DownAttackKey.IsKeyReapeated() == false)
    {
        while (true)
        {
            if (time.empty() == false)
            {
                long double  tmp = time.front() - (target_time * Engine::GetMusic().pitch);

                if (timer - (tmp) <= 0.05 && timer - tmp >= -0.05)
                {
                    GameObject* note_tmp = notes.front();
                    if (note_tmp->GetPosition().y < -2)
                    {
                        notes.pop();
                        time.pop();
                        static_cast<DownNote*>(note_tmp)->Score_Check(3);
                        break;
                    }
                    else if (note_tmp->GetPosition().y == -2)
                    {
                        notes.pop();
                        time.pop();
                        break;
                    }
                    else
                        break;
                }
                if (timer - (tmp) <= 0.13 && timer - tmp >= -0.13)
                {
                    GameObject* note_tmp = notes.front();
                    if (note_tmp->GetPosition().y < -2)
                    {
                        notes.pop();
                        time.pop();
                        static_cast<DownNote*>(note_tmp)->Score_Check(2);
                        break;
                    }
                    else if (note_tmp->GetPosition().y == -2)
                    {
                        notes.pop();
                        time.pop();
                        break;
                    }
                    else
                        break;
                }
                else
                    break;
            }
            else
                break;
        }
    }
}

