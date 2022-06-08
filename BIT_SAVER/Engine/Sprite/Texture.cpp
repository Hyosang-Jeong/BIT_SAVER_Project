/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.cpp
Purpose: For draw texture
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang , Hyosang Jung

-----------------------------------------------------------------*/

#include "Texture.h"
#include <fstream>
#include "..\Engine.h"

using Image = unsigned char*;

void Texture::Draw(glm::mat3  displayMatrix)
{
	Draw(displayMatrix, glm::vec2(0, 0), glm::vec2(1, 1));
}

void Texture::Draw(glm::mat3 displayMatrix, glm::vec2 texel_pos, glm::vec2 texel_size)
{
	model.shdr_pgm.Use();
	glBindVertexArray(model.vaoid);

	glTextureParameteri(tex_obj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // size
	glTextureParameteri(tex_obj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, tex_obj);
	glBindTextureUnit(0, tex_obj);

	GLuint tex_loc = glGetUniformLocation(model.shdr_pgm.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 0);

	glm::mat3 texture_matrix =
	{
		texel_size.x,0,0,
		0,1,0,
		texel_pos.x,0,1
	};

	GLuint texelPos = glGetUniformLocation(model.shdr_pgm.GetHandle(), "textureMatrix");
	glUniformMatrix3fv(texelPos, 1, GL_FALSE, &texture_matrix[0].x);
	if (texelPos >= 0)
	{
		glUniformMatrix3fv(texelPos, 1, GL_FALSE, &texture_matrix[0].x);
	}
	else
	{
		Engine::GetLogger().LogError("Uniform variable doesn't exist!!!");
		std::exit(EXIT_FAILURE);
	}

	GLint uniform_var_loc1 = glGetUniformLocation(model.shdr_pgm.GetHandle(), "uModelToNDC");
	if (uniform_var_loc1 >= 0)
	{
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, &displayMatrix[0].x);
	}
	else
	{
		Engine::GetLogger().LogError("Uniform variable doesn't exist!!!");
		std::exit(EXIT_FAILURE);
	}

	glDrawElements(model.primitive_type, model.draw_cnt, GL_UNSIGNED_SHORT, NULL);

	model.shdr_pgm.UnUse();

	glBindVertexArray(0);
}

void Texture::Draw(glm::vec2 pos, glm::vec2 scale, glm::vec2 rotate)
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
	   1.0 / 10.f  ,0  ,0,
		0,  1 / 10.f ,0,
		0,0,1
	};
	glm::mat3 mdl_to_ndc_xform = ndcscale_matrix * trans_matrix * scale_matrix * rotation_matrix;
	Draw(mdl_to_ndc_xform);
}

void Texture::Draw(float alpha_value, glm::mat3 camera, glm::vec2 pos, glm::vec2 scale, glm::vec2 rotate, glm::vec2 ,  glm::vec2 )
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
	   1.0 / 10.f  ,0  ,0,
		0,  1 / 10.f ,0,
		0,0,1
	};

	glm::mat3 mdl_to_ndc_xform = camera* ndcscale_matrix * trans_matrix * rotation_matrix * scale_matrix;

	model.shdr_pgm.Use();
	glBindVertexArray(model.vaoid);

	glTextureParameteri(tex_obj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // size
	glTextureParameteri(tex_obj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(tex_obj, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, tex_obj);
	glBindTextureUnit(0, tex_obj);

	GLuint tex_loc = glGetUniformLocation(model.shdr_pgm.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 0);

	GLuint alpha = glGetUniformLocation(model.shdr_pgm.GetHandle(), "alpha");
	if (alpha < 0)
	{
		Engine::GetLogger().LogError("Uniform value doesn't exist! ");
	}
	glUniform1f(alpha, alpha_value);
	glm::mat3 texture_matrix =
	{
		1,0,0,
		0,1,0,
		0,0,1
	};

	GLuint texelPos = glGetUniformLocation(model.shdr_pgm.GetHandle(), "textureMatrix");
	glUniformMatrix3fv(texelPos, 1, GL_FALSE, &texture_matrix[0].x);
	if (texelPos >= 0)
	{
		glUniformMatrix3fv(texelPos, 1, GL_FALSE, &texture_matrix[0].x);
	}
	else
	{
		Engine::GetLogger().LogError("Uniform variable doesn't exist!!!");
		std::exit(EXIT_FAILURE);
	}

	GLint uniform_var_loc1 = glGetUniformLocation(model.shdr_pgm.GetHandle(), "uModelToNDC");
	if (uniform_var_loc1 >= 0)
	{
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, &mdl_to_ndc_xform[0].x);
	}
	else
	{
		Engine::GetLogger().LogError("Uniform variable doesn't exist!!!");
		std::exit(EXIT_FAILURE);
	}

	glDrawElements(model.primitive_type, model.draw_cnt, GL_UNSIGNED_SHORT, NULL);

	model.shdr_pgm.UnUse();

	glBindVertexArray(0);
}


glm::vec2 Texture::GetSize()
{ 
	return texture_size;
}

