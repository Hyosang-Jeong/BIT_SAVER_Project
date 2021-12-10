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



struct Track_Time
{
    int track{ 0 };
    long double time{ 0.0 };
    Track_Time(int a, long double b) :track(a), time(b) {}
};

class Track : public GameObject
{
public:
    Track(int music_num);
    Track(std::map<int,std::vector<long double>>, int);
    void Update(double dt) override;
    glm::vec2 Getposition();
    void SetUpdate(bool update);
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Track;
    }
    void SetOffsetTime(long double offset_time_);
    std::vector<Track_Time> track_time; // for else
    glm::vec2 note_pos{ 0 };
    glm::vec2 note_vel{ 0 };

    std::map<int, std::vector<long double>> track_info; // for REWIND
private:
    int Music_Num{ 0 };
    bool Doupdate;
    double timer{ 0 };
    long double offset_time{ 0 };
};