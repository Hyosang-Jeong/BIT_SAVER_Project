#include "Camera.h"
#include<cmath>
Camera::Camera(glm::vec2 newPosition):position(newPosition)
{
    mdl_to_ndc_xform =
    {
        1,0,0,
        0,1,0,
       -position.x,-position.y,1
    };
}

void Camera::SetPosition(glm::vec2 newPosition)
{
    position = newPosition;
}

void Camera::Update(const glm::vec2& followObjPos,double dt)
{
    static double timer = 0;
    if (dynamic_move == true)
    {
        timer = 1;
    }
    timer -= dt;
    if (timer >=0)
    {
        static glm::vec2 pos{ 0,0.5 };
        position += pos;
        pos *= -1;
        dynamic_move = false;
    }
    if (timer < 0)
    {
        SetPosition({ 0,0 });
    }
    mdl_to_ndc_xform =
    {
        1,0,0,
        0,1,0,
       -position.x,-position.y,1
    };
    glm::mat3 view_xform =
    {
        1,0,0,
        0,1,0,
       -followObjPos.x,-followObjPos.y,1
    };

    mdl_to_ndc_xform *= view_xform;
}

const glm::vec2& Camera::GetPosition() const
{
    return position;
}

glm::mat3 Camera::GetMatrix()
{
	return mdl_to_ndc_xform;
}

void Camera::Dynamic_movement(bool start)
{
    dynamic_move = start;
}
