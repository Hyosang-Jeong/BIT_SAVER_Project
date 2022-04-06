/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CheckBox.cpp
Project: BIT_SAVER
Author: Jaewoo Choi
-----------------------------------------------------------------*/
#include"CheckBox.h"
#include"../../Engine/Engine.h"


CheckBox::CheckBox(glm::vec2 startPos, int color) :
    tilde(InputKey::Keyboard::Tilde),
    GameObject(startPos, glm::vec2{ 0.1,20 })
{
    isTildeKeyDown = true;

    if(color==0)
        AddGOComponent(new Sprite("../images/checkBoxP.png", this));
    else if (color == 1)
        AddGOComponent(new Sprite("../images/checkBoxG.png", this));
    else if (color == 2)
        AddGOComponent(new Sprite("../images/checkBoxR.png", this));
}

void CheckBox::Draw([[maybe_unused]]glm::mat3 camera_matrix)
{
#ifdef _DEBUG
    if (isTildeKeyDown == false && tilde.IsKeyDown() && tilde.IsKeyReapeated()==false)
    {
        isTildeKeyDown = true;
    }
    else if (isTildeKeyDown == true && tilde.IsKeyDown() && tilde.IsKeyReapeated() == false)
    {
        isTildeKeyDown = false;
    }

    if (isTildeKeyDown == true)
    {
        GameObject::Draw(camera_matrix);
    }
#endif

}


