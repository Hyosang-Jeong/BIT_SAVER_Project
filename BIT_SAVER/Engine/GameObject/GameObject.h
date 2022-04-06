/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Project: BIT_SAVER
Author: Hyosang Jung 

-----------------------------------------------------------------*/
#pragma once


#include<map>
#include<Windows.h>
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
	const double GetRotation() const;
	const glm::vec2& GetTexturetoNDC() const;
	void SetScale(glm::vec2 newScale);
	void UpdateScale(glm::vec2 adjustScale);
	void SetPosition(glm::vec2 newPosition);
	void set_destroy(bool value);
	bool Destroy();

	void UpdatePosition(glm::vec2 addPosition);
	void SetVelocity(glm::vec2 newVelocity);
	void UpdateVelocity(glm::vec2 newVelocity);
	void SetRotation(double newRotationAmount);
	void UpdateRotation(double adjustRotation);

	template<typename T>
	T* GetGOComponent() { return components.GetComponent<T>(); }

protected:


	void AddGOComponent(Component* component) { components.AddComponent(component); }
	void UpdateGOComponents(double dt) { components.UpdateAll(dt); }
	void ClearGOComponents() { components.Clear(); }
	template<typename T>
	void RemoveGOComponent() { components.RemoveComponent<T>(); }


	class ObjectState {
	public:
		virtual void Enter(GameObject* object) = 0;
		virtual void Update(GameObject* object, double dt) = 0;
		virtual void TestForExit(GameObject* object) = 0;
		virtual std::string GetName() = 0;
	};
	class State_Nothing : public ObjectState {
	public:
		void Enter(GameObject*) override {}
		void Update(GameObject*, double) override {}
		void TestForExit(GameObject*) override {}
		std::string GetName() override { return ""; }
	};
	State_Nothing state_nothing;


	void ChangeState(ObjectState* newState);

	ObjectState* currState;

private:
	glm::mat3 objectMatrix;
	glm::vec2 scale;
	glm::vec2 position;
	glm::vec2 velocity;

	double rotation;

	bool updateMatrix;
	bool is_destroy = false;

	ComponentManager components;
protected:
	std::map<std::string, GLSLShader>::iterator shd_ref;
	glm::mat3 mdl_xform;
	glm::mat3 mdl_to_ndc_xform;
	glm::vec2 texture_ndc;
	const float world_range = 10;
};


