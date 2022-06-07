/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Track.h
Project: BIT_SAVER
Author:  Jaewoo.choi,  Sunwoo Lee
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"
#include <map>
#include<queue>
#include"..\..\Engine\Music\Midi.h"


struct Track_Time
{
    int track{ 0 };
    long double time{ 0.0 };
    int movement{ 0 };
    Track_Time(int a, long double b, int c) :track(a), time(b), movement(c) {}
};

class Track : public GameObject
{
public:
    Track(int music_num);
    Track(std::map<int,std::vector<info>>, int);
    void Update(double dt) override;
    glm::vec2 Getposition();
    void SetUpdate(bool update);
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Track;
    }

    void SetOffsetTime(long double offset_time_);
    std::queue<Track_Time> track_time; // for else
    std::queue<long double> time;
    std::queue<GameObject*> notes;
    glm::vec2 note_pos{ 0 };
    glm::vec2 note_vel{ 0 };

    std::map<int, std::vector<info>> track_info; // for REWIND
    InputKey UpAttackKey;
    InputKey DownAttackKey;
    void hit_check();
private:
    int Music_Num{ 0 };
    bool Doupdate;
    double timer{ 0 };
    double pitch_timer{ 0 };
    long double offset_time{ 0 };
    double target_time;
};