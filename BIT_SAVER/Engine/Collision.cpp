/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/01/2021
-----------------------------------------------------------------*/
#include"Collision.h"
#include"doodle/drawing.hpp" //doodle drawing
#include"TransformMatrix.h"
#include"GameObject.h" //objectPtr
void CS230::RectCollision::Draw(math::TransformMatrix cameraMatrix)
{
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    math::rect2 displayRect = GetWorldCoorRect();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_rectangle(displayRect.Left(), displayRect.Bottom(), displayRect.Size().x, displayRect.Size().y);
    doodle::pop_settings();
}

void CS230::CircleCollision::Draw(math::TransformMatrix cameraMatrix) 
{
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_ellipse(objectPtr->GetPosition().x, objectPtr->GetPosition().y, GetRadius() * 2);
    doodle::pop_settings();
}
math::rect2 CS230::RectCollision::GetWorldCoorRect()
{
    math::rect2 RectCollision; 
   
    RectCollision.point1 = math::TransformMatrix(objectPtr->GetMatrix()) * static_cast<math::vec2>(rect.point1);
    RectCollision.point2 = math::TransformMatrix(objectPtr->GetMatrix()) * static_cast<math::vec2>(rect.point2);
    
    return RectCollision;
}


double CS230::CircleCollision::GetRadius()
{
    return radius*objectPtr->GetScale().x;
}

bool CS230::RectCollision::DoesCollideWith(GameObject* testAgainstObject)
{
    if (testAgainstObject->GetGOComponent<CS230::Collision>() != nullptr && testAgainstObject->GetGOComponent<CS230::Collision>()->GetCollideType() == Collision::CollideType::Rect_Collide)
    {
        math::rect2 MyRectCollision = this->GetWorldCoorRect();
        math::rect2 TestRectCollision = testAgainstObject->GetGOComponent<RectCollision>()->GetWorldCoorRect();

        if (MyRectCollision.Left() < TestRectCollision.Right() && MyRectCollision.Right() > TestRectCollision.Left() && MyRectCollision.Bottom() < TestRectCollision.Top() && MyRectCollision.Top() > TestRectCollision.Bottom())
        {
            return true;
        }
    }
    return false;
}

bool CS230::CircleCollision::DoesCollideWith(GameObject* testAgainstObject)
{
    if (testAgainstObject->GetGOComponent<CS230::Collision>() != nullptr && testAgainstObject->GetGOComponent<CS230::Collision>()->GetCollideType() == Collision::CollideType::Circle_Collide)
    {
        if ((this->objectPtr->GetPosition().x - testAgainstObject->GetPosition().x) * (this->objectPtr->GetPosition().x - testAgainstObject->GetPosition().x) + (this->objectPtr->GetPosition().y - testAgainstObject->GetPosition().y) * (this->objectPtr->GetPosition().y - testAgainstObject->GetPosition().y) < (this->GetRadius() + testAgainstObject->GetGOComponent<CircleCollision>()->GetRadius()) * (this->GetRadius() + testAgainstObject->GetGOComponent<CircleCollision>()->GetRadius()))
        {
            return true;
        }
    }
    return false;
}


bool CS230::RectCollision::DoesCollideWith(math::vec2 point)
{
    math::rect2 MyRectCollision = this->GetWorldCoorRect();
   
    if (MyRectCollision.Left() <= point.x && MyRectCollision.Right() >= point.x && MyRectCollision.Bottom() <= point.y && MyRectCollision.Top() >= point.y)
    {
        return true;
    }
    return false;


}

bool CS230::CircleCollision::DoesCollideWith(math::vec2 point)
{
    if ((this->objectPtr->GetPosition().x - point.x) * (this->objectPtr->GetPosition().x - point.x) + (this->objectPtr->GetPosition().y - point.y) * (this->objectPtr->GetPosition().y - point.y) < (this->GetRadius()) * (this->GetRadius()))
    {
        return true;
    }
    return false;
}
