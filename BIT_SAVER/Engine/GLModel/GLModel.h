/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GLModel.h
Project: BIT_SAVER
Author:	Jaewoo Choi
-----------------------------------------------------------------*/
#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include"../GLShader/glslshader.h"
#include<string>
#include<vector>
#include<array>
class GLModel
{
public:
	GLModel();
	void update(glm::vec2 min, glm::vec2 frame_size);
	void init(glm::vec2 size);
	struct Vertex
	{
		glm::vec2 position;
		glm::vec2 tex_coord;
	};
	GLenum primitive_type;
	GLuint primitive_cnt;
	GLuint vaoid;
	GLuint draw_cnt;

	std::array<glm::vec2, 4> pos_vtx;
	std::array<GLushort, 4> idx_vtx;
	std::array<glm::vec2, 4>text_cord;
	std::vector<Vertex> vertices;
	std::vector<GLshort> indices;

	GLSLShader shdr_pgm;

};