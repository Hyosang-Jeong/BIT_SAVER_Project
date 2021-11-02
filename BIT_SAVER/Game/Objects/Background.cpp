/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project:
Author:
Creation date: 3/14/2021
-----------------------------------------------------------------*/

#include "Background.h"
#include "../Engine/Engine.h"	//GetGameStateManage
#include "../../Engine/Sprite/Sprite.h"
#include "../../Engine/Physics/Camera.h"

void Background::Add(const std::filesystem::path& texturePath, int level)
{
    GLModel model;
    model.init({ 1,1 });
    glm::mat3 matrix =
    {
        1,0,0,
        0,1,0,
        0,0,1
    };
    backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath.string().c_str()), model,matrix,level });
}

glm::vec2 Background::Size() {
    for (ParallaxInfo& levelInfo : backgrounds) {
        if (levelInfo.level == 1) {
            return levelInfo.texture->GetSize();
        }
    }
    return { 0,0 };
}

void Background::Update(double dt)
{
    for (ParallaxInfo& levelInfo : backgrounds)
    {
        glm::mat3 trans_matrix
        {
            1,0,0,
             0,1,0,
            -(levelInfo.level*dt),0,1
        };
        levelInfo.matrix *= trans_matrix;
    }
}

void Background::Unload() 
{
    backgrounds.clear();
}

void Background::Draw(glm::mat3 camera)
{
    for (ParallaxInfo& levelInfo : backgrounds)
    {
        levelInfo.texture->Draw(levelInfo.matrix*camera,levelInfo.model, "Hero");
    }
}