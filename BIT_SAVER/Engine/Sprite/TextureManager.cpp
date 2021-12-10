/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.cpp
Project: BIT_SAVER
Author: Hyosang Jung
-----------------------------------------------------------------*/
#include"TextureManager.h"
#include"Texture.h"  //Texture
#define STB_IMAGE_IMPLEMENTATION
#include "..\Image\stb_image.h"

#include "..\Engine.h"

using Image = unsigned char*;

Texture* TextureManager::Load(const char* filePath)
{
	texture_info image;
	stbi_set_flip_vertically_on_load(true);

	if (images.find(filePath) == images.end())
	{
			image.img = stbi_load(filePath, &image.width, &image.height, &image.col_chanel, 4);
			if (!image.img)
			{
				Engine::GetLogger().LogError("Failed to load image");
				std::exit(EXIT_FAILURE);
			}
			glCreateTextures(GL_TEXTURE_2D, 1, &image.tex_objhdl);

			glTextureStorage2D(image.tex_objhdl, 1, GL_RGBA8, image.width, image.height);
			glTextureSubImage2D(image.tex_objhdl, 0, 0, 0, image.width, image.height, GL_RGBA, GL_UNSIGNED_BYTE, image.img);

			images[filePath] = new Texture{ image.tex_objhdl,{ image.width, image.height} };
			stbi_image_free(image.img);
			Engine::GetLogger().LogDebug("Image loaded" + std::string(filePath));
	}
	return images[filePath];
}

void TextureManager::Unload()
{
	for (const std::pair<std::string, Texture*>& i : images)
	{
		glDeleteTextures(1, &i.second->tex_obj);
		delete i.second;
	}
	images.clear();
	Engine::GetLogger().LogEvent("Clear Textures");
}


