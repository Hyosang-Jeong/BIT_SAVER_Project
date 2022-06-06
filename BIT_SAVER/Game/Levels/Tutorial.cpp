/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tutorial.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang 
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManage
#include"Tutorial.h"
#include"../Objects/Hero.h"
#include"../Objects/Background.h"
#include"../Objects/Track.h"
#include"../Objects/Note_collisionBox.h"
#include"..\..\Engine\Physics\Camera.h"
#include"../../Engine/Sprite/GameParticles.h"
#include"../../Engine/Sprite/Texture.h"
#include"../Levels/State.h"
#include"../Objects/NoteHard.h"
Tutorial::Tutorial() :Escape(InputKey::Keyboard::Escape),
    font2( font_path[PressStart] )
{
     window_pos = Engine::GetWindow().GetSize();
    text_pos.x = window_pos.x * 0.5f;
    text_pos.y = window_pos.y * 0.6f;
}

void Tutorial::Load()
{
    tutorialState = &stateGreeting;
    tutorialState->Enter(this);
    stateMagu.magu_index = 0;

	heroPtr = new Hero({ -6,-5 });
	backPtr = new Background();
	trackPtr = new Track(SOUND_NUM::TUTORIAL);
	gameObjectManager = new GameObjectManager();
    camera = new Camera({ 0,0 });
    notebox = new Note_box({ -4,0 });

    backPtr->Add(texture_path[Background_1_10], 0);
    backPtr->Add(texture_path[Background_1_9], 0);
    backPtr->Add(texture_path[Background_1_8], 0.0005);
    backPtr->Add(texture_path[Background_1_7], 0.0015);
    backPtr->Add(texture_path[Background_1_6], 0.007);
    backPtr->Add(texture_path[Background_1_5], 0.022);
    backPtr->Add(texture_path[Background_1_4], 0.05);
    backPtr->Add(texture_path[Background_1_3], 0.1);
    backPtr->Add(texture_path[Background_1_2], 0.5);
    backPtr->Add(texture_path[Background_1_1], 0.8);

    AddGSComponent(gameObjectManager);
    AddGSComponent(backPtr);
    AddGSComponent(camera);

    gameObjectManager->Add(heroPtr);
    gameObjectManager->Add(trackPtr);
    gameObjectManager->Add(notebox);

    AddGSComponent(new HitEmitter());
    AddGSComponent(new PerfectEmitter());
    AddGSComponent(new GoodEmitter());
    AddGSComponent(new BadEmitter());
    AddGSComponent(new MissEmitter());
}

void Tutorial::Update(double dt)
{
    tutorialState->Update(this, dt);
    tutorialState->TestForExit(this);
}

void Tutorial::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1333f, 0.0666f, 0.5647f, 0.2156f);
    GetGSComponent<Background>()->Draw(camera->GetMatrix());
    gameObjectManager->DrawAll(camera->GetMatrix());
    tutorialState->Draw(this);
}


void Tutorial::Unload()
{
    heroPtr = nullptr;
    trackPtr = nullptr;
    notebox = nullptr;
    backPtr = nullptr;
    gameObjectManager->Unload();

    if (Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET) == true)
    {
        Engine::GetMusic().pitchDefault(SOUND_NUM::OFFSET);
        Engine::GetMusic().Stop(SOUND_NUM::OFFSET);
    }
    ClearGSComponent();

}

void Tutorial::State_Greeting::Enter(GameState* state)
{
    Tutorial* tutorial = static_cast<Tutorial*>(state);
    tutorial->helper = Engine::GetTextureManager().Load("../images/helper.png" );
    Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
    tutorial->index = 0;
}

void Tutorial::State_Greeting::Update(GameState* state, double dt)
{
    Tutorial* tutorial = reinterpret_cast<Tutorial*>(state);
    tutorial->heroPtr->Update(dt);
    if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None ){
        tutorial->index++;
        Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
    }
}

void Tutorial::State_Greeting::Draw(GameState* state)
{
    Tutorial* tutorial = static_cast<Tutorial*>(state);
    tutorial->helper->Draw({ 6,-7 }, { -4,4 });
    switch (tutorial->index)
    {
    case 0:  Engine::GetText(tutorial->font2).Draw("Hello", tutorial->text_pos.x, tutorial->text_pos.y, 1.f, glm::vec3(1, 1, 1));
        break;
    case 1: Engine::GetText(tutorial->font2).Draw("Let's learn game play", tutorial->text_pos.x, tutorial->text_pos.y, 1.f, glm::vec3(1, 1, 1));
        break;
    case 2: Engine::GetText(tutorial->font2).Draw("Default Jump attack key is F", tutorial->text_pos.x, tutorial->text_pos.y, 1.f, glm::vec3(1, 1, 1));
        break;
    case 3: Engine::GetText(tutorial->font2).Draw("Default Down attack key is J", tutorial->text_pos.x, tutorial->text_pos.y, 1.f, glm::vec3(1, 1, 1));
        break;
    case 4: Engine::GetText(tutorial->font2).Draw("You can change these key", tutorial->text_pos.x, tutorial->text_pos.y, 1.f, glm::vec3(1, 1, 1));
        break;
    case 5: Engine::GetText(tutorial->font2).Draw("Play Tutorial !", tutorial->text_pos.x, tutorial->text_pos.y, 1.f, glm::vec3(1, 1, 1));
        break;
    }
       
}

void Tutorial::State_Greeting::TestForExit(GameState* state)
{
    Tutorial* tutorial = static_cast<Tutorial*>(state);
    if (tutorial->index == 6)
    {
        tutorial->tutorialState = &tutorial->stateAttack;
        tutorial->tutorialState->Enter(state);
    }
}

void Tutorial::State_Attacks::Enter(GameState* state)
{
    Tutorial* tutorial = static_cast<Tutorial*>(state);
    if(tutorial->stateMagu.magu_index==0)
        Engine::GetMusic().Play(SOUND_NUM::OFFSET);
}

void Tutorial::State_Attacks::Update(GameState* state, double dt)
{
    Tutorial* tutorial = static_cast<Tutorial*>(state);
    HardNote* magu = static_cast<HardNote*>(tutorial->gameObjectManager->Find(GameObjectType::HardNote));

    if (magu != nullptr)
    {
        if (tutorial->stateMagu.magu_index==0 && magu->Getposition().x <= 6)
        {
            tutorial->tutorialState = &tutorial->stateMagu;
            tutorial->tutorialState->Enter(state);
            return;
        }
    }
    tutorial->gameObjectManager->UpdateAll(dt);


    if (tutorial->Escape.IsKeyDown() == true)
    {
        Engine::GetGameStateManager().SetNextState(static_cast<int>(State::Option));
    }
    if (tutorial->index == 7 &&Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None) 
    {
        tutorial->index++;
        Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
    }
}

void Tutorial::State_Attacks::Draw(GameState* state)
{
    Tutorial* tutorial = static_cast<Tutorial*>(state);

    if (Engine::GetMusic().isPlaying(SOUND_NUM::OFFSET) == false)
    {
        Engine::GetText(tutorial->font2).Draw("Good..!", tutorial->text_pos.x, tutorial->text_pos.y, 1.f, glm::vec3(1, 1, 1));
        tutorial->index = 7;
        Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
    }
}

void Tutorial::State_Attacks::TestForExit(GameState* state)
{
    Tutorial* tutorial = static_cast<Tutorial*>(state);
    if (tutorial->index == 8)
    {
        Engine::GetGameStateManager().SetNextState(static_cast<int>(State::MainMenu));
    }
}

void Tutorial::State_Magu::Enter(GameState* )
{
    Engine::GetMusic().Pause(SOUND_NUM::OFFSET);
    Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
}

void Tutorial::State_Magu::Update(GameState* , double )
{
    if (Engine::GetInput().GetLastPressedButton() != InputKey::Keyboard::None)
    {
        this->magu_index++;
        Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::None);
    }
}

void Tutorial::State_Magu::Draw(GameState* state)
{
    Tutorial* tutorial = static_cast<Tutorial*>(state);
    tutorial->helper->Draw({ 6,-7 }, { -4,4 });
    switch (this->magu_index)
    {
    case 0:  Engine::GetText(tutorial->font2).Draw("This is Magu Magu note", tutorial->text_pos.x, tutorial->window_pos.y * 0.3f, 1.f, glm::vec3(1, 1, 1));
        break;
    case 1: Engine::GetText(tutorial->font2).Draw("Jump  and down  as much as you can", tutorial->text_pos.x, tutorial->window_pos.y * 0.3f, 1.f, glm::vec3(1, 1, 1));
        break;
    }
}

void Tutorial::State_Magu::TestForExit(GameState* state)
{
    Tutorial* tutorial = static_cast<Tutorial*>(state);
    if (this->magu_index == 2)
    {
        tutorial->tutorialState = &tutorial->stateAttack;
        tutorial->tutorialState->Enter(state);
        Engine::GetMusic().Resume(SOUND_NUM::OFFSET);
    }
}
