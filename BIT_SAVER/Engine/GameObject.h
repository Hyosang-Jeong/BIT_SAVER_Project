/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once

#include "Vec2.h"
//#include "Sprite.h"
#include "TransformMatrix.h"
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<map>
#include"GLModel.h"
#include"glslshader.h"
#include"Texture.h"
	class GameObject 
	{
	public:
		GameObject(glm::vec2 position);
		GameObject(glm::vec2 position, double rotation, glm::vec2 scale);
		virtual ~GameObject() {}

		virtual void Update(double dt);
		virtual void Draw();

		const math::TransformMatrix& GetMatrix();
		const glm::vec2& GetPosition() const;
		const glm::vec2& GetVelocity() const;
		const glm::vec2& GetScale() const;
		double GetRotation() const;

	protected:

		class State 
		{
		public:
			virtual void Enter(GameObject* object) = 0;
			virtual void Update(GameObject* object, double dt) = 0;
			virtual void TestForExit(GameObject* object) = 0;
			virtual std::string GetName() = 0;
		};
		class State_Nothing : public State {
		public:
			void Enter(GameObject*) override {}
			void Update(GameObject*, double) override {}
			void TestForExit(GameObject*) override {}
			std::string GetName() { return ""; }
		};
		State_Nothing state_nothing;

		void ChangeState(State* newState);

		State* currState;


		void SetPosition(glm::vec2 newPosition);
		void UpdatePosition(glm::vec2 adjustPosition);
		void SetVelocity(glm::vec2 newPosition);
		void UpdateVelocity(glm::vec2 adjustPosition);
		void SetScale(glm::vec2 newScale);
		void SetRotation(double newRotationAmount);
		void UpdateRotation(double newRotationAmount);

		//Sprite sprite;

	private:
		math::TransformMatrix objectMatrix;
		bool updateMatrix;

		double rotation;

		glm::vec2 scale;
		glm::vec2 position;
		glm::vec2 velocity;



	protected:
		std::map<std::string, GLModel>::iterator mdl_ref;
		std::map<std::string, GLSLShader>::iterator shd_ref;
		glm::mat3 mdl_xform;
		glm::mat3 mdl_to_ndc_xform;
		Texture texture;
	};


