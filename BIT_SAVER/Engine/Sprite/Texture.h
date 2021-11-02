/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.h
Purpose: Wrapper class for doodle::Image
Project: BIT_SAVER
Author: 
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include<GL/glew.h>
#include<string>
#include<glm/glm.hpp>
#include<map>
#include"../GLModel/GLModel.h"
class Texture
{
public:
    Texture() = default;
    Texture(GLuint obj, glm::vec2 size) : tex_obj(obj), texture_size(size) {};
    void Draw(glm::mat3 displayMatrix, GLModel mdl, std::string shdr_name);
    void Draw(double world_range, GLModel mdl, std::string shdr_name, glm::vec2 pos, glm::vec2 scale = { 1,1 }, glm::vec2 rotate = { 0,0 });
    glm::vec2 GetSize();
private:
    GLuint tex_obj{ 0 };
    glm::vec2 texture_size{ 0,0 };
};
