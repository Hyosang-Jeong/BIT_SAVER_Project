/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CheckBox.cpp
Project: BIT_SAVER
Author:
Creation date: 11/02/2021
-----------------------------------------------------------------*/
#include"CheckBox.h"
#include"../../Engine/Engine.h"


CheckBox::CheckBox(glm::vec2 startPos, int color) :
    tilt(InputKey::Keyboard::T),
    GameObject(startPos, glm::vec2{ 0.1,20 })
{
    isTiltKeyDown = false;
    if(color==0)
        AddGOComponent(new Sprite("../images/checkBoxP.png", this));
    else if (color == 1)
        AddGOComponent(new Sprite("../images/checkBoxG.png", this));
    else if (color == 2)
        AddGOComponent(new Sprite("../images/checkBoxR.png", this));
}

void CheckBox::Draw(glm::mat3 camera_matrix)
{
    if (isTiltKeyDown == false && tilt.IsKeyDown() && tilt.IsKeyReapeated()==false)
    {
        isTiltKeyDown = true;
    }
    else if (isTiltKeyDown == true && tilt.IsKeyDown() && tilt.IsKeyReapeated() == false)
    {
        isTiltKeyDown = false;
    }

    if (isTiltKeyDown == true)
    {
        GameObject::Draw(camera_matrix);
    }


}


