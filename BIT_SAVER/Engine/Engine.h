/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.h
Purpose: This is the service provider for our games engine services
Project: BIT_SAVER
Author:  Hyosang Jung , Sunwoo Lee

-----------------------------------------------------------------*/
#pragma once
#include<iostream>
#include <chrono>   
#include<utility>
#include "..\Engine\Window\Window.h"
#include "..\Engine\GameState\GameStateManager.h"
#include "..\Engine\input\Input.h"
#include "..\Engine\Logger\Logger.h"
#include"..\Engine\GLModel\GLModel.h"
#include"..\Engine\GLShader\glslshader.h"
#include"..\Engine\Sprite\TextureManager.h"
#include"..\Engine\Music\music.h"
#include"..\Engine\Component.h"
#include "..\Engine\Text\GLText.h"
#include<map>

class Engine
{
public:
    static Engine& Instance()
    {
        static Engine instance; return instance;
    }
    static Music& GetMusic() { return Instance().music; };
    static Logger& GetLogger() { return Instance().logger; };
    static Input& GetInput() { return Instance().input; }
    static Window& GetWindow() { return Instance().window; }
    static GLText& GetText(std::string fontpath) { return Instance().texts[fontpath]; };
    static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
    static TextureManager& GetTextureManager() { return Instance().texturemanager; }
    static  std::map<std::string, GLSLShader>& GetGLShader() { return Instance().shdrpgms; }
    static AttackKey& GetAttack_Key() { return Instance().attackKey; };

    void Init(std::string windowName);
    void Shutdown();
    void Update();
    bool HasGameEnded();
    void init_shdrpgms();
    void init_fonts();
    bool GetDifficulty();
    void SetDifficulty(bool _easy);


    template<typename T>
    static T* GetGSComponent() { return GetGameStateManager().GetGSComponent<T>(); }
    
public:
    Engine();
    ~Engine();

    std::chrono::system_clock::time_point lastTick;
    std::chrono::system_clock::time_point fpsCalcTime;
    AttackKey attackKey;

    int frameCount;

    Music music;
    Logger logger;
    GameStateManager gameStateManager;
    TextureManager texturemanager;
    Input input;
    Window window;
    bool easy;

    std::map<std::string, GLSLShader> shdrpgms;
    std::map<std::string, GLText> texts;


    static constexpr double Target_FPS = 60.0;
    static constexpr int FPS_IntervalSec = 5;
    static constexpr int FPS_IntervalFrameCount = static_cast<int>(FPS_IntervalSec * Target_FPS);
};

