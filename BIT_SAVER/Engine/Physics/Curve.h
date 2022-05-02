/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Project: BIT_SAVER
Author:	Hyosang Jung
-----------------------------------------------------------------*/
#pragma once
#include <glm/glm.hpp>
#include "..\Component.h"
#include <vector>


class GameObject;

class Curve : public Component
{
public:
    Curve(GameObject* _object);
    void BotWave();
    void TOPWave();
    void TopToBot();
    void BotToTop();

private:
    glm::vec2 default_vector{ 1,0 };
    GameObject* _object;
};

