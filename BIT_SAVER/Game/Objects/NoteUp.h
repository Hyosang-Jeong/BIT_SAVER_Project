#pragma once
#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"

class EnergyBar;

class UpNote : public GameObject
{
public:
    UpNote(glm::vec2 startPos, glm::vec2 velocity);
    void Update(double dt) override;
    glm::vec2 Getposition();
    GameObjectType GetObjectType() override
    {
        return GameObjectType::UpNote;
    }
    void Draw(glm::mat3 camera_matrix) override;
    void Hit_Check();
    int Score_check();

    enum class UpNote_anim
    {
        flying,
        explosion
    };

private:
    InputKey UpAttackKey;
    InputKey DownAttackKey;
    bool isMiss;
    bool ishit;
    EnergyBar* energy;
};