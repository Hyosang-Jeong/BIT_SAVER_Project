/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project:
Author:
Creation date:
-----------------------------------------------------------------*/
#include"Sprite.h"
#include"../Engine.h" // get logger
#include"Texture.h"  //texture
#include"Animation.h" //new animation
#include"../Engine/GameObject/GameObject.h" //GameObject*

//#include"Collision.h"
Sprite::Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object) 
{
	Load(spriteInfoFile, object);
}

Sprite::~Sprite() {
	for (Animation* anim : animations) {
		delete anim;
	}
	animations.clear();
}

void Sprite::Load(const std::filesystem::path& spriteInfoFile,[[maybe_unused]] GameObject* object)
{

	frameTexel.clear();

	if (spriteInfoFile.extension() == ".png") 
	{
		textureptr  = Engine::GetTextureManager().Load(spriteInfoFile.string().c_str());
		model.init({ 1,1 });
	}
	else if (spriteInfoFile.extension() == ".spt")
	{
		std::ifstream inFile(spriteInfoFile);

		if (inFile.is_open() == false) {
			throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
		}

		std::string text;
		inFile >> text;
		textureptr = Engine::GetTextureManager().Load(text.c_str());
		inFile >> text;
		while (inFile.eof() == false)
		{
			if (text == "Anim")
			{
				inFile >> text;
				animations.push_back(new Animation(text));
			}
			else if (text == "FrameSize") {
				inFile >> frameSize.x;
				inFile >> frameSize.y;
				model.init(frameSize);
			}
			else if (text == "NumFrames") {
				int numFrames;
				inFile >> numFrames;
				for (int i = 0; i < numFrames; i++)
				{
					frameTexel.push_back({ frameSize.x * i, 0 });
				}
			}

			else
			{
				Engine::GetLogger().LogError("Unknown spt command " + text);
			}
			inFile >> text;
		}
	}

	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}
	if (animations.empty() == true)
	{
		animations.push_back(new Animation());
	}

}

glm::vec2 Sprite::GetFrameSize() const
{
	return frameSize;
}

glm::vec2 Sprite::GetFrameTexel(int frameNum) const
{
	if (frameNum > frameTexel.size() - 1 || frameNum < 0)
	{
		Engine::GetLogger().LogError("invalid index!");
	}
	return frameTexel[frameNum];
}


void Sprite::Draw(glm::mat3 displayMatrix, std::string shdr_name)
{
	textureptr->Draw(displayMatrix,  model, shdr_name);
}

bool Sprite::IsAnimationDone()
{
	is_playing = false;
	return animations[currAnim]->IsAnimationDone();
}

int Sprite::GetCurrentAnim()
{
	return currAnim;
}

void Sprite::Update(double dt)
{
	if (is_playing == true)
	{
		model.update(GetFrameTexel(animations[currAnim]->GetDisplayFrame()), frameSize);
	}
	animations[currAnim]->Update(dt);
}
void Sprite::PlayAnimation(int anim)
{
	if (anim > animations.size() - 1 || anim < 0)
	{
		Engine::GetLogger().LogError("invalid index");
		currAnim = 0;
	}
	animations[anim]->ResetAnimation();
	currAnim = anim;
	is_playing = true;
}



