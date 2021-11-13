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
    backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath.string().c_str()),Engine::GetTextureManager().Load(texturePath.string().c_str()),model, 0, 2, level });
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
    if (is_fever_mode == true)
    {
        alpha_value += static_cast<float>(dt) * 0.1f;
    }


}

void Background::Unload() 
{
    backgrounds.clear();
}

void Background::Draw([[maybe_unused]]glm::mat3 camera)
{
    std::map<std::string, GLSLShader>::iterator shd_ref;
    shd_ref = Engine::GetGLShader().find("Mainmenu");
    shd_ref->second.Use();

    GLuint alpha = glGetUniformLocation(shd_ref->second.GetHandle(), "alpha");
    if (alpha < 0)
    {
        Engine::GetLogger().LogError("Uniform value doesn't exist! ");
    }
    glUniform1f(alpha, alpha_value);
    for (ParallaxInfo& levelInfo : backgrounds)
    {
        levelInfo.texture_front->Draw(1, levelInfo.model, "Mainmenu", { levelInfo.position_front,0 });
        levelInfo.texture_back->Draw(1, levelInfo.model, "Mainmenu", { levelInfo.position_back,0 });
    }
    shd_ref->second.UnUse();
}

void Background::set_fever_mode(bool is_fever_mode_)
{
    if (is_fever_mode_ == true)
    {
        Engine::GetMusic().Play(Music::SOUND_NUM::FEVER);
        is_fever_mode = is_fever_mode_;
        backgrounds[0].texture_front = Engine::GetTextureManager().Load("../images/fever_background1.png");
        backgrounds[0].texture_back = Engine::GetTextureManager().Load("../images/fever_background1.png");
        alpha_value = 0;
    }
    else
    {
        is_fever_mode = is_fever_mode_;
        backgrounds[0].texture_front = Engine::GetTextureManager().Load("../images/background1.png");
        backgrounds[0].texture_back = Engine::GetTextureManager().Load("../images/background1.png");
        alpha_value = 1;
    }
        
}
