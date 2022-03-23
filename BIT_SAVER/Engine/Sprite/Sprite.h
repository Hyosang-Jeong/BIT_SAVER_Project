/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.h
Project: BIT_SAVER
Author:  Hyun Kang , Hyosang Jung 

-----------------------------------------------------------------*/
#pragma once
#include <string>
#include <map>
#include<filesystem>
#include<GL/glew.h>
#include<glm/glm.hpp>
#include"../Component.h"


class Animation;
class GameObject;
class Texture;

class Sprite : public Component
{
public:
    Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object);
    ~Sprite();
    void Load(const std::filesystem::path& spriteInfoFile, GameObject* object);
    void Draw(glm::mat3 displayMatrix);
    void PlayAnimation(int anim);
    void Update(double dt) override;
    bool IsAnimationDone();
    int GetCurrentAnim();
    glm::vec2 GetFrameSize() const;
    Texture* textureptr;
private:
    glm::vec2 GetFrameTexel(int frameNum) const;
    bool is_playing = false;
    glm::vec2 frameSize;
    glm::vec2 ndc_frameSize;
    int currAnim = 0;
    std::vector<Animation*> animations;
    std::vector<glm::vec2> frameTexel;
};