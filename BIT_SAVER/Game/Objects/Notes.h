/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
//#include "..\Engine\Sprite.h" //sprite
#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance


class Note : public GameObject
{
public:
    Note(glm::vec2 startPos);
    void Update(double dt) override;
    glm::vec2 Getposition();
    void Draw() override;
private:
   //int track_num;
   //std::vector<double> time;
   //double timer = 0;
};