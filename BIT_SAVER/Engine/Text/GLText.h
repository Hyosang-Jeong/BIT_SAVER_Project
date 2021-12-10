/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GLText.h
Purpose: For draw texture
Project: BIT_SAVER
Author: Sunwoo Lee

-----------------------------------------------------------------*/
#pragma once
#include "../GLShader/glslshader.h"


enum Font_Path
{
    PressStart,
    MochiyPopOne
    //Total
};

static const char* font_path[] = {
    "../font/PressStart2P-Regular.ttf",
    "../font/MochiyPopOne-Regular.ttf"
};

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::vec2   Size;      // Size of glyph
    glm::vec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class GLText
{
public:
    void Init();
    void Load(std::string font, unsigned int fontSize);
    void Draw(std::string text, float x, float y, float scale, glm::vec3 color = { 0.f,0.f,0.f });
    unsigned int VAO;
    unsigned int VBO;
    std::map<std::string, GLSLShader>::iterator shd_ref;

private:
    std::map<GLchar, Character> Characters;

};