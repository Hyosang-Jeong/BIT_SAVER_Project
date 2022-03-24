/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.h
Project: BIT_SAVER
Author:	Hyun Kang
-----------------------------------------------------------------*/
#pragma once
#include "../../Engine/Component.h"
#include<glm/glm.hpp>
#include <filesystem>
#include"../../Engine/Sprite/Texture.h"
class Camera;
class Sprite;

class Background : public Component
{

public:
    void Add(const std::filesystem::path& texturePath, double level);
    void Unload();
    void Update(double dt);
    void Draw(glm::mat3 camera);
    void set_fever_mode(bool is_fever_mode_);

private:
    struct ParallaxInfo 
    {
        Texture* texture_front;
        Texture* texture_back;
        float position_front;
        float position_back;
        double level;
    };
    float alpha_value=1;
    bool is_fever_mode=false;
    std::vector<ParallaxInfo> backgrounds;
};