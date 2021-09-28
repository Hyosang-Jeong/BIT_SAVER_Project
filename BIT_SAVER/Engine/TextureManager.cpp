/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 4/16/2021
-----------------------------------------------------------------*/
#pragma once
#include"TextureManager.h"
#include"Texture.h"  //Texture
#include"Engine.h"  //get logger


CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& filePath)
{
	if (pathToTexture.find(filePath) == pathToTexture.end())
	{
		pathToTexture[filePath] = new Texture(filePath);
	}
	return pathToTexture[filePath];
}

void CS230::TextureManager::Unload()
{
	for (const std::pair<std::filesystem::path, Texture*> &i : pathToTexture)
	{
		delete i.second;
	}
	pathToTexture.clear();
	Engine::GetLogger().LogEvent("Clear Textures");
}