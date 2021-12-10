/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.cpp
Project: BIT_SAVER
Author:  Hyosang Jung 

-----------------------------------------------------------------*/
#include"Animation.h"

Animation::Animation() : Animation("../anm/none.anm") { }

Animation::Animation(const std::filesystem::path& fileName) : animSequenceIndex(0)
{
    if (fileName.extension() != ".anm") {
        throw std::runtime_error("Bad Filetype.  " + fileName.generic_string() + " not a sprite info file (.anm)");
    }
    std::ifstream inFile(fileName);
    if (inFile.is_open() == false) {
        throw std::runtime_error("Failed to load " + fileName.generic_string());
    }

    std::string label;
    while (inFile.eof() == false)
    {
        inFile >> label;
        if (label == "PlayFrame")
        {
            int frame;
            float targetTime;
            inFile >> frame;
            inFile >> targetTime;

            animation.push_back(new PlayFrame(frame, targetTime));
        }
        else if (label == "Loop")
        {
            int loopToFrame;
            inFile >> loopToFrame;
            animation.push_back(new Loop(loopToFrame));
        }
        else if (label == "End")
        {
            animation.push_back(new End());
        }
        else
        {
            Engine::GetLogger().LogError("Unknown command " + label + " in anm file " + fileName.generic_string());
        }
    }
    ResetAnimation();
}

Animation::~Animation() {
    for (CommandData* command : animation) {
        delete command;
    }
    animation.clear();
}

void Animation::Update(double dt)
{
    currPlayFrameData->Update(dt);
    if (currPlayFrameData->IsFrameDone() == true)
    {
        currPlayFrameData->ResetTime();
        if (animation[animSequenceIndex]->GetType() == Command::PlayFrame)
        {
            currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
            ++animSequenceIndex;
        }
        else if (animation[animSequenceIndex]->GetType() == Command::Loop)
        {
            Loop* loopData = static_cast<Loop*>(animation[animSequenceIndex]);
            animSequenceIndex = loopData->GetLoopToIndex();
            if (animation[animSequenceIndex]->GetType() == Command::PlayFrame)
            {
                currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
            }
            else
            {
                Engine::GetLogger().LogError("Loop does not go to PlayFrame");
                ResetAnimation();
            }
            ++animSequenceIndex;
        }
        else if (animation[animSequenceIndex]->GetType() == Command::End)
        {
            isAnimationDone = true;
            return;
        }
    }
}


int Animation::GetDisplayFrame()
{
    return currPlayFrameData->GetFrameNum();
}

void Animation::ResetAnimation()
{
    animSequenceIndex = 0;
    currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
    isAnimationDone = false;
}
bool Animation::IsAnimationDone()
{
    return isAnimationDone;
}

Animation::PlayFrame::PlayFrame(int frame, double duration) :frame(frame), targetTime(duration), timer(0) {}

void Animation::PlayFrame::Update(double dt)
{
    timer += dt;
}

bool Animation::PlayFrame::IsFrameDone()
{
    if (timer > targetTime)
    {
        return true;
    }
    return false;
}

void Animation::PlayFrame::ResetTime()
{
    timer = 0;
}
int Animation::PlayFrame::GetFrameNum()
{
    return frame;
}

Animation::Loop::Loop(int loopToindex) :loopToIndex(loopToindex)
{}

int Animation::Loop::GetLoopToIndex()
{
    return loopToIndex;
}