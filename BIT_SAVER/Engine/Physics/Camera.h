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
#include<list>
class Camera : public Component 
{
public:
	Camera(glm::vec2 newPosition);
	void SetPosition(glm::vec2 newPosition);
	void Update(const glm::vec2& followObjPos,double dt);
	const glm::vec2& GetPosition() const;
	glm::mat3 GetMatrix();
	void shake(float intensity, float interval, float total);
	void generate_shake_xvalue(double dt);
	void generate_shake_yvalue(double dt);
	void zoom_effect(glm::vec2 start);
	void update_scale(double dt);

	void set_scale(glm::vec2 scale_)
	{
		scale = scale_;
	}

	glm::vec2 get_scale()
	{
		return scale;
	}
private:
	glm::mat3 mdl_to_ndc_xform;
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

	bool is_shaking;
	bool zoom_;
	double target_time = 0;
	float interval_ = 0;
	float interval_tmp = 0;
	double timer_ = 0;
	float intensity_ = 0;
	std::list<float> shake_value_x;
	std::list<float> shake_value_y;
};
