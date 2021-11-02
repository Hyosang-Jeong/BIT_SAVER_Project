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

public:
    void Add(const std::filesystem::path& texturePath, int level);
    void Unload();
    void Update(double dt);
    void Draw(glm::mat3 camera);
    glm::vec2 Size();
private:
    struct ParallaxInfo {
        Texture* texture;
        GLModel model;
        glm::mat3 matrix;
        int level;
    };
    std::vector<ParallaxInfo> backgrounds;
};