#pragma once
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.h
Project:
Author:
Creation date:
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include "../../Engine/Component.h"
#include"GameObjectType.h"
#include"../../../lib/include/glm/glm.hpp"
#include <filesystem>

class Camera;
class Sprite;

class Background : public Component
{
//public:
//    Background(glm::vec2 startPos, glm::vec2 velocity);
//    void Update(double dt) override;
//    glm::vec2 Getposition();
//    //GameObjectType GetObjectType() override
//    //{
//    //    return GameObjectType::Background;
//    //}
//    void Draw(glm::mat3 camera_matrix) override;
//private:
//    bool back_alive;

public:
    void Add(const std::filesystem::path& texturePath, int level);
    void Unload();
    void Update();
    void Draw(glm::mat3 camera);
    glm::vec2 Size();
private:
    struct ParallaxInfo {
        Sprite texture;
        int level;
    };
    std::vector<ParallaxInfo> backgrounds;
};