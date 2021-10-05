/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.cpp
Purpose: Wrapper class for doodle::Image
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/

#include "Texture.h"
#include <fstream>
//#define STB_IMAGE_IMPLEMENTATION
//#include "..\Image\stb_image.h"
#include "..\Engine.h"

using Image = unsigned char*;


//Texture::Texture(doodle::Image&& doodleImage) {
//    image = std::move(doodleImage);
//}

void Texture::Draw(glm::mat3  displayMatrix, std::string mdl_name, std::string shdr_name)
{
	std::map<std::string, GLModel>::iterator mdl_ref;
	std::map<std::string, GLSLShader>::iterator shd_ref;
	mdl_ref = Engine::GetGLModel().find(mdl_name);
	shd_ref = Engine::GetGLShader().find(shdr_name);

	shd_ref->second.Use();
	glBindVertexArray(mdl_ref->second.vaoid);

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
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE,&displayMatrix[0].x);
	}
	else
	{
		Engine::GetLogger().LogError("Uniform variable doesn't exist!!!");
	}

	glDrawElements(mdl_ref->second.primitive_type, mdl_ref->second.draw_cnt, GL_UNSIGNED_SHORT, NULL);

	shd_ref->second.UnUse();

	glBindVertexArray(0);
}


void Texture::setup_texobj(const char* pathname)
{
	tex_obj = Engine::GetTextureManager().Load(pathname);
}

//void CS230::Texture::Draw(math::TransformMatrix displayMatrix, math::ivec2 texelPos, math::ivec2 frameSize) {
//    doodle::push_settings();
//    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
//    doodle::draw_image(image, 0, 0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
//    doodle::pop_settings();
//}
//
//math::ivec2 CS230::Texture::GetSize() { return { image.GetWidth(), image.GetHeight() }; }
//
//unsigned int CS230::Texture::GetPixel(math::ivec2 texel) {
//    int index = texel.y * GetSize().x + texel.x;
//    return (static_cast<int>(image[index].red)) << 24 |
//        (static_cast<int>(image[index].green)) << 16 |
//        (static_cast<int>(image[index].blue)) << 8 |
//        (static_cast<int>(image[index].alpha));
//}
