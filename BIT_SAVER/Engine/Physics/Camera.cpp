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

void Camera::Update(const glm::vec2&  ,double dt)
{
    if (timer_ < target_time)
    {
        timer_ += dt;
        generate_shake_xvalue(dt);
        generate_shake_yvalue(dt);
    }
    else if(timer_ > target_time)
    {
        position = { 0,0 };
        rotation = 0;
        timer_ = 0;
        target_time = 0;
        interval_tmp = 0;
    }

    update_scale(dt);

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

void Camera::shake(float intensity, float interval, float total)
{
    timer_ = 0;
    target_time = total;
    interval_ = interval;
    intensity_ = intensity;

    std::random_device rd;
    std::mt19937 gen(rd());
   // std::normal_distribution<float> dis(-intensity_, intensity_);

    std::random_device rd_2;
    std::mt19937 gen_2(rd_2());
   // std::normal_distribution<float> dis_2(-intensity_, intensity_);

    for (int i = 0; i < static_cast<int>(total / interval); i++)
    {
        std::normal_distribution<float> dis(-intensity_, intensity_);
        std::normal_distribution<float> dis_2(-intensity_, intensity_);
        shake_value_x.push_back(dis(gen));
        shake_value_y.push_back(dis_2(gen_2));
        intensity_ *= 0.5;
    }
}

void Camera::generate_shake_xvalue(double dt)
{
    if (shake_value_x.size() == 0)
    {
        position.x = 0;
        return;
    }

    float tmp = *shake_value_x.begin();
    if (position.x < tmp)
    {
        position.x += static_cast<float>(dt);
        if (position.x >= tmp)
        {
            shake_value_x.pop_front();
        }
    }
    else if (position.x >= tmp)
    {
        position.x -= static_cast<float>(dt);
        if (position.x <= tmp)
        {
            shake_value_x.pop_front();
        }
    }
}
void Camera::generate_shake_yvalue(double dt)
{
    if (shake_value_y.size() == 0)
    {
        position.y = 0;
        return;
    }

    float tmp = *shake_value_y.begin();
    if (position.y < tmp)
    {
        position.y += static_cast<float>(dt);
        if (position.y >= tmp)
        {
            shake_value_y.pop_front();
        }
    }
    else if (position.y >= tmp)
    {
        position.y -= static_cast<float>(dt);
        if (position.y <= tmp)
        {
            shake_value_y.pop_front();
        }
    }
}


void Camera::zoom_effect(glm::vec2 start)
{
    scale = start;
    zoom_ = true;
}

void Camera::update_scale(double dt)
{
    if (zoom_ == true)
    {
        if (scale.x >= 1)
        {
            scale.x -= static_cast<float>(dt) / 2.f;
            if (scale.x <= 1)
            {
                scale.x = 1;
                zoom_ = false;
            }
        }
        if (scale.y >= 1)
        {
            scale.y -= static_cast<float>(dt) / 2.f;
            if (scale.y <= 1)
            {
                scale.y = 1;
                zoom_ = false;
            }
        }

        if (scale.x < 1)
        {
            scale.x += static_cast<float>(dt) / 2.f;
            if (scale.x >= 1)
            {
                scale.x = 1;
                zoom_ = false;
            }
        }
        if (scale.y < 1)
        {
            scale.y += static_cast<float>(dt) / 2.f;
            if (scale.y >= 1)
            {
                scale.y = 1;
                zoom_ = false;
            }
        }
    }
}
