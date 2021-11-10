/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Track.h
Project: BIT_SAVER
Author: 
Creation date: 
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"
#include <map>

class Track : public GameObject
{
public:
    Track(int music_num);
    Track(std::vector<long double>);
    void Update(double dt) override;
    glm::vec2 Getposition();
    void SetUpdate(bool update);
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Track;
    }
private:
    std::map<int, std::vector<long double>> track_info;
    bool Doupdate;
    glm::vec2 note_pos{ 0 };
    glm::vec2 note_vel{ 0 };
    double timer{ 0 };
};