/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Project: BIT_SAVER
Author:	Hyosang Jung
-----------------------------------------------------------------*/
#include "Camera.h"
#include<cmath>
#include<random>
#include<iostream>

float PI = 3.141592f;

Camera::Camera(glm::vec2 newPosition):position(newPosition),is_shaking(false)
{
    rotation = 0;
    scale = { 1,1 };
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

void Camera::Update(const glm::vec2& ,[[maybe_unused]]double dt)
{
    timer += dt;
    if (timer < 1.5)
    {
        generate_shake_value();
        target_time += dt;
    }
    else
    {
        position = { 0,0 };
        rotation = 0;
    }

    mdl_to_ndc_xform =
    {
        1,0,0,
        0,1,0,
       -position.x,-position.y,1
    };

    glm::mat3 scale_mat =
    {
        scale.x,0,0,
        0,scale.y,0,
        0,0,1
    };

    glm::mat3 rotate_mat =
    {
        cos(rotation),sin(rotation),0,
        -sin(rotation), cos(rotation),0,
       0,0,1
    };

    mdl_to_ndc_xform = mdl_to_ndc_xform * rotate_mat * scale_mat;
}

const glm::vec2& Camera::GetPosition() const
{
    return position;
}

glm::mat3 Camera::GetMatrix()
{
	return mdl_to_ndc_xform;
}

void Camera::shake()
{
    timer = 0;
    target_time = 0;
}

void Camera::generate_shake_value()
{
    if (timer > target_time)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> dis(-PI / 30.f, PI / 30.f);
        rotation = dis(gen);
      //  position = { dis(gen) * 10.f, dis(gen) *10.f};
    }
}
 