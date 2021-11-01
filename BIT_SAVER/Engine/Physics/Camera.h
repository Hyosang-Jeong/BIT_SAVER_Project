/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Project: BIT_SAVER
Author: 
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include <glm/glm.hpp>
#include "..\Component.h"
class Camera : public Component 
{
public:
	Camera(glm::vec2 newPosition);
	void SetPosition(glm::vec2 newPosition);
	void Update(const glm::vec2& followObjPos,double dt);
	const glm::vec2& GetPosition() const;
	glm::mat3 GetMatrix();
	void Dynamic_movement(bool start, double dt);
private:
	glm::mat3 mdl_to_ndc_xform;
	glm::vec2 position;
	bool dynamic_move{ false };
};
