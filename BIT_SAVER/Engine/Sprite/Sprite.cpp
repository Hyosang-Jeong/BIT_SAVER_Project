/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project: BIT_SAVER
Author:  Hyun Kang , Hyosang Jung 
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
	animations.clear();
	frameTexel.clear();

	if (spriteInfoFile.extension() == ".png") 
	{
		textureptr  = Engine::GetTextureManager().Load(spriteInfoFile.string().c_str());
		frameTexel.push_back(glm::vec2{ 0,0 });
		ndc_frameSize = { 1,1 };
	}
	else if (spriteInfoFile.extension() == ".spt")
	{
		std::ifstream inFile(spriteInfoFile);

		if (inFile.is_open() == false) 
		{
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
			else if (text == "FrameSize") 
			{
				inFile >> frameSize.x;
				inFile >> frameSize.y;
			}
			else if (text == "NumFrames") 
			{
				int numFrames;
				inFile >> numFrames;
				float ndc_frame_size = 1.0f / static_cast<float>(numFrames);

				ndc_frameSize.x = ndc_frame_size;
				ndc_frameSize.y = 1.0f;

				for (int i = 0; i < numFrames; i++)
				{
					frameTexel.push_back({ ndc_frame_size * i, 0.f });
				}
			}
			else
			{
				Engine::GetLogger().LogError("Unknown spt command " + text);
				exit(EXIT_FAILURE);
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
	return ndc_frameSize;
}

glm::vec2 Sprite::GetFrameTexel(int frameNum) const
{
	if (frameNum > frameTexel.size() - 1 || frameNum < 0)
	{
		Engine::GetLogger().LogError("invalid index!");
	}
	return frameTexel[frameNum];
}


void Sprite::Draw(glm::mat3 displayMatrix)
{
	textureptr->Draw(displayMatrix, GetFrameTexel(animations[currAnim]->GetDisplayFrame()), ndc_frameSize);
}

bool Sprite::IsAnimationDone()
{
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
		//model.update(GetFrameTexel(animations[currAnim]->GetDisplayFrame()), ndc_frameSize);
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