/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include<filesystem>
#include"Vec2.h"
#include"TransformMatrix.h" //display matrix
#include "Component.h"
#include"GameObject.h" //GameObject*
namespace CS230 {
    class Texture;
    class Animation;
    class GameObject;
}
namespace CS230 {
    class Sprite : public Component {
    public:
        Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object);
        ~Sprite();
        void Load(const std::filesystem::path& spriteInfoFile, GameObject* object);
        void Draw(math::TransformMatrix displayMatrix);
        void PlayAnimation(int anim);
        void Update(double dt) override;
        bool IsAnimationDone();
        int GetCurrentAnim();
        math::ivec2 GetHotSpot(int index);
        math::ivec2 GetFrameSize() const;
    private:
        Texture* texturePtr;
        math::ivec2 GetFrameTexel(int frameNum) const;
        math::ivec2 frameSize;
        int currAnim = 0;
        std::vector<Animation*> animations;
        std::vector<math::ivec2> frameTexel;
        std::vector<math::ivec2> hotSpotList;
    };
}