/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/22/2021
-----------------------------------------------------------------*/
#include"Camera.h" 
#include"TransformMatrix.h" //get matrix
CS230::Camera::Camera(math::rect2 movableRange) : movableRange{ movableRange }, extent{ math::irect2{math::ivec2{0,0},math::ivec2{0,0}} }, position{ math::vec2{0,0} }{}

void CS230::Camera::SetPosition(math::vec2 newPosition)
{
	position = newPosition;
}
void CS230::Camera::SetExtent(math::irect2 newExtent)
{
	extent = newExtent;
}
const math::vec2& CS230::Camera::GetPosition()const
{
	return position;
}

void CS230::Camera::Update(const math::vec2& followObjPos)
{
    if (followObjPos.x - position.x > movableRange.Right())
    {
        position.x = followObjPos.x - movableRange.Right();
    }
    if (followObjPos.x - position.x < movableRange.Left())
    {
        position.x = followObjPos.x - movableRange.Left();
    }
    if (position.x < extent.Left())
    {
        position.x = extent.Left();
    }
    if (position.x > extent.Right())
    {
        position.x = extent.Right();
    }

    if (followObjPos.y - position.y > movableRange.Top())
    {
        position.y = followObjPos.y - movableRange.Top();
    }
    if (followObjPos.y - position.y < movableRange.Bottom())
    {
        position.y = followObjPos.y - movableRange.Bottom();
    }
    if (position.y < extent.Bottom())
    {
        position.y = extent.Bottom();
    }
    if (position.y > extent.Top())
    {
        position.y = extent.Top();
    }
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
	return math::TranslateMatrix(-position);
}
