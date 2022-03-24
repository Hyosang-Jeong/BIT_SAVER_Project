/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project: BIT_SAVER
Author:	Hyun Kang
-----------------------------------------------------------------*/

#include "Background.h"
#include "../Engine/Engine.h"	//GetGameStateManage
#include "../../Engine/Sprite/Sprite.h"

void Background::Add(const std::filesystem::path& texturePath, double level)
{
    backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath.string().c_str()),Engine::GetTextureManager().Load(texturePath.string().c_str()), 0, 20, level });
}


void Background::Update(double dt)
{
    for (ParallaxInfo& levelInfo : backgrounds)
    {
        levelInfo.position_front = static_cast<float>(levelInfo.position_front - levelInfo.level * 10.0 * dt);
        levelInfo.position_back = static_cast<float>(levelInfo.position_back - levelInfo.level * 10.0 * dt);
        if (levelInfo.position_front <= -20)
        {
            levelInfo.position_front = 20;
        }
        if (levelInfo.position_back <= -20)
        {
            levelInfo.position_back = 20;
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
    for (ParallaxInfo& levelInfo : backgrounds)
    {
        levelInfo.texture_front->Draw(alpha_value, camera,{ levelInfo.position_front,0 }, { 10,10 });
        levelInfo.texture_back->Draw(alpha_value, camera, { levelInfo.position_back,0 },  { 10,10 });
    }
}

void Background::set_fever_mode(bool is_fever_mode_)
{
    if (is_fever_mode_ == true)
    {
        Engine::GetMusic().Play(SOUND_NUM::FEVER);
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
