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

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<map>
#include"..\GLModel\GLModel.h"
#include"..\GLShader\glslshader.h"
#include"..\Texture\Texture.h"

	class GameObject 
	{
	public:
		GameObject(glm::vec2 position);
		GameObject(glm::vec2 position, double rotation, glm::vec2 scale);
		virtual ~GameObject() {}

		virtual void Update(double dt);
		virtual void Draw();

		const glm::mat3& GetMatrix();
		const glm::vec2& GetPosition() const;
		const glm::vec2& GetVelocity() const;
		const glm::vec2& GetScale() const;
		double GetRotation() const;
		bool Destroy();
	protected:

		void SetPosition(glm::vec2 newPosition);
		void UpdatePosition(glm::vec2 adjustPosition);
		void SetVelocity(glm::vec2 newPosition);
		void UpdateVelocity(glm::vec2 adjustPosition);
		void SetScale(glm::vec2 newScale);
		void SetRotation(double newRotationAmount);
		void UpdateRotation(double newRotationAmount);
		void set_destroy(bool value);

		//Sprite sprite;

	private:
		glm::mat3 objectMatrix;
		bool updateMatrix;

		double rotation;

		glm::vec2 scale;
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 orientation;

		bool is_destroy = false;
		const double world_range = 10;
	protected:
		std::map<std::string, GLModel>::iterator mdl_ref;
		std::map<std::string, GLSLShader>::iterator shd_ref;
		glm::mat3 mdl_xform;
		glm::mat3 mdl_to_ndc_xform;
		Texture texture;
	};


