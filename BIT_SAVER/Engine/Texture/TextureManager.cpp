#pragma once
#include"TextureManager.h"
#include"Texture.h"  //Texture
#define STB_IMAGE_IMPLEMENTATION
#include "..\Image\stb_image.h"
#include<iostream>
#include "..\Engine.h"

using Image = unsigned char*;

GLuint TextureManager::Load(const char* filePath,glm::vec2& texture_size)
{
	texture_info image;
	stbi_set_flip_vertically_on_load(true);
	if (images.find(filePath) == images.end())
	{
		image.img = stbi_load(filePath, &image.width, &image.height, &image.col_chanel, 4);
		if (!image.img)
		{
		    Engine::GetLogger().LogDebug("Failed to load image");
		    std::exit(EXIT_FAILURE);
		}
		glCreateTextures(GL_TEXTURE_2D, 1, &image.tex_objhdl);
		// allocate GPU storage for texture image data loaded from file
		glTextureStorage2D(image.tex_objhdl, 1, GL_RGBA8, image.width, image.height);
		glTextureSubImage2D(image.tex_objhdl, 0, 0, 0, image.width, image.height, GL_RGBA, GL_UNSIGNED_BYTE, image.img);
		texture_size = { image.width ,image.height };
		images[filePath] = image.tex_objhdl;

	}
	else
	{
		return images.find(filePath)->second;
	}

	return images[filePath];
}

//void TextureManager::Unload()
//{
//	for (const std::pair<std::filesystem::path, Texture*>& i : pathToTexture)
//	{
//		delete i.second;
//	}
//	pathToTexture.clear();
//	Engine::GetLogger().LogEvent("Clear Textures");
//}