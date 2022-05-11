/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GLText.cpp
Purpose: For draw texture
Project: BIT_SAVER
Author:  Sunwoo Lee

-----------------------------------------------------------------*/
#include "GLText.h"
#include"../Engine.h" // get logger
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

void GLText::Load(std::string font, unsigned int fontSize)
{
	const std::string font1{ "../font/MochiyPopOne-Regular.ttf" };
	const std::string font2{ "../font/PressStart2P-Regular.ttf" };

	this->Characters.clear();

	FT_Library ft_lib;
	
	if (FT_Init_FreeType(&ft_lib)) {
		Engine::GetLogger().LogError("Can't init Font");
	}

	FT_Face ft_face;
	
	if (FT_New_Face(ft_lib, font.c_str(), 0, &ft_face)) {
		Engine::GetLogger().LogError("Can't Load Font");
	}
	

	FT_Set_Pixel_Sizes(ft_face, 0, fontSize);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(ft_face, c, FT_LOAD_RENDER))
		{
			Engine::GetLogger().LogError("Can't Load GLyph");
			continue;
		}

		//GLuint texobj_hdl;
		//glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);
		//glTextureStorage2D(texobj_hdl, 1, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		//glTextureSubImage2D(texobj_hdl, 0, 0, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows,
		//	GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		GLuint texobj_hdl;
		glGenTextures(1, &texobj_hdl);
		glBindTexture(GL_TEXTURE_2D, texobj_hdl);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			ft_face->glyph->bitmap.width,
			ft_face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			ft_face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		Character character = {
			texobj_hdl,
			glm::ivec2(ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows),
			glm::ivec2(ft_face->glyph->bitmap_left, ft_face->glyph->bitmap_top),
			static_cast<unsigned int>(ft_face->glyph->advance.x)
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(ft_face);
	FT_Done_FreeType(ft_lib);
}

void GLText::Draw(std::string text, float x, float y, float scale, glm::vec3 color)
{
	shd_ref->second.Use();

	//GLuint texColor_location = glGetUniformLocation(shd_ref->second.GetHandle(), "textColor");
	//glm::vec3 col = glm::vec3(color);
	//glUniform3fv(texColor_location, 1, &color.x);
	//this->shd_ref->second.SetUniform("textColor", color);

	GLint uniform_var_loc1 =
		glGetUniformLocation(shd_ref->second.GetHandle(), "textColor");
	if (uniform_var_loc1 >= 0) {
		glUniform3fv(uniform_var_loc1, 1, &color.x);
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character character = Characters[*c];

		float xpos = x + character.Bearing.x * scale;
		float ypos = y + (this->Characters['H'].Bearing.y - character.Bearing.y) * scale;

		float w = character.Size.x * scale;
		float h = character.Size.y * scale;

		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 0.0f },

			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f }
		};

		glBindTexture(GL_TEXTURE_2D, character.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (character.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	shd_ref->second.UnUse();
}

