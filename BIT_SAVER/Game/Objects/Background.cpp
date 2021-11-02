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

void Background::Add(const std::filesystem::path& texturePath, double level)
{
    GLModel model;
    model.init({ 1,1 });
    backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath.string().c_str()),
                            Engine::GetTextureManager().Load(texturePath.string().c_str()),
                            model, 0, 2, level });
}

//glm::vec2 Background::Size() 
//{
//    for (ParallaxInfo& levelInfo : backgrounds) {
//        {
//            return levelInfo.texture_front->GetSize();
//        }
//    }
//    return { 0,0 };
//}

void Background::Update(double dt)
{
    for (ParallaxInfo& levelInfo : backgrounds)
    {
        //double move = static_cast<double>(levelInfo.level) * dt;
        levelInfo.position_front = static_cast<float>(levelInfo.position_front - levelInfo.level * dt);
        levelInfo.position_back = static_cast<float>(levelInfo.position_back - levelInfo.level * dt);
        if (levelInfo.position_front <= -2)
        {
            levelInfo.position_front = 2;
        }
        if (levelInfo.position_back <= -2)
        {
            levelInfo.position_back = 2;
        }
    }

}

void Background::Unload() 
{
    backgrounds.clear();
}

void Background::Draw([[maybe_unused]]glm::mat3 camera)
{
    for (ParallaxInfo& levelInfo : backgrounds)
    {
        levelInfo.texture_front->Draw(1, levelInfo.model, "Hero", { levelInfo.position_front,0 });
        levelInfo.texture_back->Draw(1, levelInfo.model, "Hero", { levelInfo.position_back,0 });
    }
}