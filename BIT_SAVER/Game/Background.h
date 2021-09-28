/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include<filesystem>  // filesystem
#include "../Engine/Component.h"
#include"../Engine/Vec2.h"  
#include"../Engine/Texture.h" 
namespace CS230 {
    class Texture;
    class Camera;
}

class Background : public CS230::Component {
public:
    ~Background();
    void Add(const std::filesystem::path& texturePath, int level);
    void Draw(const CS230::Camera& camera);
    math::ivec2 Size();
private:
    struct ParallaxInfo 
    {
        CS230::Texture* texturePtr;
        int level;
    };
    std::vector<ParallaxInfo> backgrounds;
};

