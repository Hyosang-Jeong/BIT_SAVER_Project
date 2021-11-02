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
    Texture texture;
    GLModel model;
    glm::vec2 GetFrameTexel(int frameNum) const;
    glm::vec2 frameSize;
    int currAnim = 0;
    std::vector<Animation*> animations;
    std::vector<glm::vec2> frameTexel;
};
