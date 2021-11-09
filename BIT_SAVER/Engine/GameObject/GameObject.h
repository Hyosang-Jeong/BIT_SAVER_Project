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
#include"..\GLShader\glslshader.h"
#include"..\Sprite\Sprite.h"
#include"../Physics/Collision.h"
#include"../ComponentManager.h"

enum class GameObjectType;

class Component;

class GameObject
{
	friend class Sprite;
public:
	GameObject(glm::vec2 position);
	GameObject(glm::vec2 position, glm::vec2 scale);
	virtual ~GameObject() 
	{
		ClearGOComponents();
	}
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
	void UpdatePosition(glm::vec2 adjustPosition);
	void SetScale(glm::vec2 newScale);
	void SetPosition(glm::vec2 newPosition);
	void set_destroy(bool value);
	bool Destroy();

	template<typename T>
	T* GetGOComponent() { return components.GetComponent<T>(); }

protected:

	void SetVelocity(glm::vec2 newPosition);
	void UpdateVelocity(glm::vec2 adjustPosition);
	void AddGOComponent(Component* component) { components.AddComponent(component); }
	void UpdateGOComponents(double dt) { components.UpdateAll(dt); }
	void ClearGOComponents() { components.Clear(); }
	template<typename T>
	void RemoveGOComponent() { components.RemoveComponent<T>(); }

private:
	glm::mat3 objectMatrix;
	glm::vec2 scale;
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 orientation;

	bool updateMatrix;
	bool is_destroy = false;

	ComponentManager components;
protected:
	Collision collision;
	std::map<std::string, GLSLShader>::iterator shd_ref;
	glm::mat3 mdl_xform;
	glm::mat3 mdl_to_ndc_xform;
	glm::vec2 texture_ndc;
	const float world_range = 10;
};


