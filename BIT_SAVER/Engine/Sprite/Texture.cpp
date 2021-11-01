/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.cpp
Purpose: For draw texture
Project: BIT_SAVER
Author:
Creation date: 2/11/2021
-----------------------------------------------------------------*/

#include "Texture.h"
#include <fstream>
#include "..\Engine.h"

using Image = unsigned char*;

void Texture::Draw(glm::mat3  displayMatrix, GLModel mdl, std::string shdr_name)
{
	std::map<std::string, GLSLShader>::iterator shd_ref;

	shd_ref = Engine::GetGLShader().find(shdr_name);
	if (shd_ref == Engine::GetGLShader().end())
	{
		Engine::GetLogger().LogError("Shader not found!");
		std::exit(EXIT_FAILURE);
	}

	shd_ref->second.Use();
	glBindVertexArray(mdl.vaoid);

	glTextureParameteri(tex_obj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // size
	glTextureParameteri(tex_obj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, tex_obj);
	glBindTextureUnit(0, tex_obj);

	GLuint tex_loc = glGetUniformLocation(shd_ref->second.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 0);

	GLint uniform_var_loc1 = glGetUniformLocation(shd_ref->second.GetHandle(), "uModelToNDC");
	if (uniform_var_loc1 >= 0)
	{
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, &displayMatrix[0].x);
	}
	else
	{
		Engine::GetLogger().LogError("Uniform variable doesn't exist!!!");
		std::exit(EXIT_FAILURE);
	}

	glDrawElements(mdl.primitive_type, mdl.draw_cnt, GL_UNSIGNED_SHORT, NULL);

	shd_ref->second.UnUse();

	glBindVertexArray(0);
}

void Texture::Draw(double world_range, GLModel mdl, std::string shdr_name, glm::vec2 pos, glm::vec2 scale, glm::vec2 rotate)
{
	glm::mat3 scale_matrix
	{
		scale.x,0,0,
		0,scale.y,0,
		0,0,1
	};
	double PI = 3.14159265359;

	glm::mat3 rotation_matrix
	{
		cos(rotate.x * (float)PI / (float)180),sin(rotate.x * (float)PI / (float)180),0,
	   -sin(rotate.x * (float)PI / (float)180),cos(rotate.x * (float)PI / (float)180),0,
		0,0,1
	};

	glm::mat3 trans_matrix
	{
		1,0,0,
		 0,1,0,
		pos.x,pos.y,1
	};
	glm::mat3 ndcscale_matrix
	{
	   1.0 / world_range  ,0  ,0,
		0,  1 / world_range ,0,
		0,0,1
	};
	glm::mat3 mdl_to_ndc_xform = ndcscale_matrix * trans_matrix * rotation_matrix * scale_matrix;
	Draw(mdl_to_ndc_xform, mdl, shdr_name);
}


glm::vec2 Texture::GetSize()
{
	return texture_size;
}

void Texture::setup_texobj(const char* pathname)
{
	tex_obj = Engine::GetTextureManager().Load(pathname, texture_size);
}
