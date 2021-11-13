/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Option.h
Project: BIT_SAVER
Author:
Creation date: 3/07/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState\GameState.h" // BIT_SAVER::GameState
#include "..\Engine\GameObject\GameObjectManager.h" // gameobjectmanager
#include"..\Engine\Input\Input.h"  //input key
#include"../../Engine/Sprite/Texture.h"
class GLText;

enum Select
{
    SOUND,
    RESUME,
    RESTART,
    MAINMENU,
    QUIT
};


class Option : public GameState
{
public:
    Option();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    std::string GetName() { return "Option"; }
    void Draw() override;
    void GetIndex();
    Select GetSelect();
private:

    Texture* textureAll;
    Texture* sound1;
    Texture* sound2;
    Texture* sound3;
    Texture* sound4;
    Texture* Restart;
    Texture* Quit;
    GLModel model;

    InputKey escape;
    InputKey OptionUpKey;
    InputKey OptionDownKey;
    InputKey OptionSoundUpKey;
    InputKey OptionSoundDownKey;
    InputKey OptionSelectKey;

    GameObjectManager* gameObjectManager;
    int curr_state;

    bool isOption;
    glm::vec2 selectedIndex;

    Select select;
};
