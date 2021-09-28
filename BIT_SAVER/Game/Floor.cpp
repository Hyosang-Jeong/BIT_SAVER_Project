/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Floor.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/16/2021
-----------------------------------------------------------------*/

#include "Floor.h"
#include"..\Engine\Rect.h"
#include"..\Engine\Collision.h"

Floor::Floor(math::irect2 rect): GameObject(rect.point1)
{
	this->AddGOComponent(new CS230::RectCollision(math::irect2{ {0,0},{rect.Size().x,rect.Size().y} }, this));
}
