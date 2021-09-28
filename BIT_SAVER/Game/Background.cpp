/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/25/2021
-----------------------------------------------------------------*/
#include"Background.h"
#include  "..\Engine\Camera.h" // Camera
#include"../Engine/Texture.h"
#include"../Engine/Engine.h"
void Background::Add(const std::filesystem::path& texturePath, int level)
{
	backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath),level });
}
Background::~Background()
{
	backgrounds.clear();
}

math::ivec2 Background::Size()
{

	for (ParallaxInfo& index : backgrounds)
	{
		if (index.level == 1)
		{
			return index.texturePtr->GetSize();
		}
	}
	return math::ivec2{ -1,-1 };   
}

void Background::Draw(const CS230::Camera& camera)
{
	for (ParallaxInfo& index : backgrounds)
	{
		index.texturePtr->Draw(math::TranslateMatrix(math::vec2{ -camera.GetPosition().x / index.level , -camera.GetPosition().y }));
	}
}