#pragma once
#include "../GLShader/glslshader.h"

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

private:
    static std::map<GLchar, Character> Characters;
    static unsigned int VAO;
    static unsigned int VBO;
    static std::map<std::string, GLSLShader>::iterator shd_ref;

};