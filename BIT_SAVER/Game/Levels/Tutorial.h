/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tutorial.h
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang 
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include "..\Engine\GameObject\GameObjectManager.h" // gameobjectmanager
#include"..\Engine\Input\Input.h"  //input key
#include"../../Engine/Sprite/Texture.h"
#include "../../Engine/Music/Sound_Num.h"

class TutorialState
{
public:
    virtual void Enter(GameState* object) =0;
    virtual void Update(GameState* object, double dt)=0 ;
    virtual void Draw(GameState* object) = 0;
    virtual void TestForExit(GameState* object) =0;
};

class Hero;
class Track;
class Background;
class GLText;
class Camera;
class Note_box;
class Texture;

class Tutorial : public GameState
{
public:
	Tutorial();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() { return "Tutorial"; }
    SOUND_NUM GetcurrentMusic() override
    {
        return SOUND_NUM::OFFSET;
    }
	void Draw() override;
    Hero* heroPtr;
    Background* backPtr;
    Track* trackPtr;
    GameObjectManager* gameObjectManager;
    Camera* camera;
    Note_box* notebox;
    TutorialState* tutorialState;
    InputKey Escape;
    Texture* helper;
    glm::vec2 window_pos;
    glm::vec2 text_pos;
    const std::string font2;
    int index;
public:
    class State_Greeting : public TutorialState
    {
    public:
        virtual void Enter(GameState* state) override;
        virtual void Update(GameState* state, double dt) override;
        virtual void Draw(GameState* state)override;
        virtual void TestForExit(GameState* state) override;
    };

    class State_Attacks : public TutorialState 
    {
    public:
        virtual void Enter(GameState* state) override;
        virtual void Update(GameState* state, double dt) override;
        virtual void Draw(GameState* state)override;
        virtual void TestForExit(GameState* state) override;
    };
    class State_Magu : public TutorialState
    {
    public:
        virtual void Enter(GameState* state) override;
        virtual void Update(GameState* state, double dt) override;
        virtual void Draw(GameState* state)override;
        virtual void TestForExit(GameState* state) override;
        int magu_index{ 0 };
    };

    State_Greeting stateGreeting;
    State_Attacks stateAttack;
    State_Magu stateMagu;
};
