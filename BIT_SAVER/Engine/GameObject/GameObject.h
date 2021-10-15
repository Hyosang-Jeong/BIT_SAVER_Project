/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Project: BIT_SAVER
Author:
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once

#include<iostream>
#include<map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include"..\GLModel\GLModel.h"
#include"..\GLShader\glslshader.h"
#include"..\Texture\Texture.h"
#include"../Physics/Collision.h"
enum class GameObjectType;

class GameObject
{
public:
	GameObject(glm::vec2 position);
	GameObject(glm::vec2 position, glm::vec2 scale);
	virtual ~GameObject() {}
	virtual GameObjectType GetObjectType() = 0;
	virtual void ResolveCollision(GameObject* object);
	virtual void Update(double dt);
	virtual void Draw(glm::mat3 camera_matrix);
	const glm::mat3& GetMatrix();
	const glm::vec2& GetPosition() const;
	const glm::vec2& GetVelocity() const;
	const glm::vec2& GetScale() const;
	const glm::vec2& GetTexturetoNDC() const;
	const AABB GetCollisionbox() const;
	void set_destroy(bool value);
	bool Destroy();

protected:

	void SetPosition(glm::vec2 newPosition);
	void UpdatePosition(glm::vec2 adjustPosition);
	void SetVelocity(glm::vec2 newPosition);
	void UpdateVelocity(glm::vec2 adjustPosition);
	void SetScale(glm::vec2 newScale);
private:
	glm::mat3 objectMatrix;
	glm::vec2 scale;
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 orientation;

	bool updateMatrix;
	bool is_destroy = false;
protected:
	Texture texture;
	Collision collision;
	std::map<std::string, GLModel>::iterator mdl_ref;
	std::map<std::string, GLSLShader>::iterator shd_ref;
	glm::mat3 mdl_xform;
	glm::mat3 mdl_to_ndc_xform;
	glm::vec2 texture_ndc;
	const float world_range = 10;
};


