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
#include"GameObjectType.h"

class Note_box : public GameObject
{
public:
    Note_box(glm::vec2 startPos);
    void Update(double dt) override;
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Note_collisionBox;
    }
    glm::vec2 Getposition();
    void Draw() override;
private:

};