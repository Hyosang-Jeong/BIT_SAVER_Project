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

//Background::Background(glm::vec2 startPos, glm::vec2 velocity) :
//	GameObject(startPos, glm::vec2{ 12,12 }), back_alive(true)
//{
//	AddGOComponent(new Sprite("../images/background.png", this));
//	SetVelocity(velocity);
//}
//
//void Background::Update(double dt)
//{
//	GameObject::Update(dt);
//	if (GetPosition().x < 0 && back_alive == true)
//	{
//		Background* new_back = new Background({ 20, 0 }, { -5,0 });
//		Engine::GetGSComponent<GameObjectManager>()->Add_front(new_back);
//		back_alive = false;
//	}
//	if (GetPosition().x < -20)
//	{
//		set_destroy(true);
//	}
//}
//
//void Background::Draw(glm::mat3 camera_matrix)
//{
//	GameObject::Draw(camera_matrix);
//}
//
//glm::vec2 Background::Getposition()
//{
//	return GameObject::GetPosition();
//}

void Background::Add(const std::filesystem::path& texturePath, int level) 
{
    backgrounds.push_back({ Texture{}, level });
    backgrounds.back().texture.setup_texobj(texturePath.string().c_str());
}

glm::vec2 Background::Size() {
    for (ParallaxInfo& levelInfo : backgrounds) {
        if (levelInfo.level == 1) {
            return levelInfo.texture.GetSize();
        }
    }
    return { 0,0 };
}

void Background::Update()
{
    
}

void Background::Unload() {
    backgrounds.clear();
}


//void Texture::Draw(double world_range, GLModel mdl, std::string shdr_name, glm::vec2 pos, glm::vec2 scale, glm::vec2 rotate)
//void Texture::Draw(glm::mat3  displayMatrix, GLModel mdl, std::string shdr_name)


void Background::Draw(const Camera& camera) {
    for (ParallaxInfo& levelInfo : backgrounds) {
        levelInfo.texture.Draw(math::TranslateMatrix(-math::vec2{ camera.GetPosition().x / levelInfo.level, camera.GetPosition().y }));
    }
}