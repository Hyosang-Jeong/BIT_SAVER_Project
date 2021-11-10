/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.h
Project:
Author:
Creation date:
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include <map>
#include<filesystem>
#include<GL/glew.h>
#include<glm/glm.hpp>
#include"../Component.h"
#include"../GLModel/GLModel.h"
#include"Texture.h"
#include"..\Engine\GLShader\glslshader.h"
class Animation;
class GameObject;


class Sprite : public Component
{
public:
    Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object);
    ~Sprite();
    void Load(const std::filesystem::path& spriteInfoFile, GameObject* object);
    void Draw(glm::mat3 displayMatrix, std::string shdr_name);
    void PlayAnimation(int anim);
    void Update(double dt) override;
    bool IsAnimationDone();
    int GetCurrentAnim();
    glm::vec2 GetFrameSize() const;
private:
    bool is_playing = false;
    Texture* textureptr;
    GLModel model;
    glm::vec2 GetFrameTexel(int frameNum) const;
    glm::vec2 frameSize;
    glm::vec2 ndc_frameSize;
    int currAnim = 0;
    std::vector<Animation*> animations;
    std::vector<glm::vec2> frameTexel;
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
    GLText();
    void Load(std::string font, unsigned int fontSize);
    void Draw(std::string text, float x, float y, float scale, glm::vec3 color = { 0.f,0.f,0.f });
    void setup_shdrpgm();

private:
    static std::map<GLchar, Character> Characters;
    static unsigned int VAO;
    static unsigned int VBO;
    static std::map<std::string, GLSLShader>::iterator shd_ref;

};
