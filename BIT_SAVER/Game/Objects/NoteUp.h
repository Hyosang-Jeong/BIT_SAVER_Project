#pragma once
#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"


class EnergyBar;

class UpNote : public GameObject
{
public:
    UpNote(glm::vec2 startPos, glm::vec2 velocity, int movement);
    void Update(double dt) override;
    glm::vec2 Getposition();
    GameObjectType GetObjectType() override
    {
        return GameObjectType::UpNote;
    }
    void Draw(glm::mat3 camera_matrix) override;
    void Score_Check(int score);

    void Die_effect(double dt);
    enum class UpNote_anim
    {
        flying,
        explosion
    };

private:
    int score_;
    bool isMiss;
    bool ishit;
    int Movement;

    EnergyBar* energy;

};