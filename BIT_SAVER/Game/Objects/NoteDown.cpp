#include"../../Engine/Engine.h"
#include "NoteDown.h"
#include"../../Engine/Sprite/GameParticles.h"
#include "EnergyBar.h"
#include "Score.h"
#include "Score Enum.h"
//#include"obstacle.h"
#include "../../Engine/Physics/Curve.h"
#include <random>

DownNote::DownNote(glm::vec2 startPos, glm::vec2 velocity, int movement) :
    isMiss(false), ishit(false), Movement(movement),
    GameObject(startPos, glm::vec2{ 1.5,1.5 })
{

    if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
    {
        energy = (static_cast<EnergyBar*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Energy_bar)));
    }
    AddGOComponent(new Sprite("../spt/belcoz.spt", this));
    AddGOComponent(new Curve(this));
    GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(DownNote_anim::flying));
    SetVelocity(velocity);

}

void DownNote::Update(double dt)
{
    if (Movement == 99)
        GetGOComponent<Curve>()->BotWave();
    else if (Movement == 101)
        GetGOComponent<Curve>()->TopToBot();


    GameObject::Update(dt);

   Die_effect(dt);
    if (GetPosition().x < -10)
    {
        set_destroy(true);
    }
    if (isMiss == true)
    {
        if (energy != nullptr)
        {
            if (energy->GetScale().x > 0)
            {
                if (GetGOComponent<Sprite>()->GetCurrentAnim() != static_cast<int>(DownNote_anim::explosion))
                {
                    energy->SetScale(glm::vec2{ energy->GetScale().x - ((dt * 2.f) * EIGHT_TIME_PER_LIFE),energy->GetScale().y });//one space
                    energy->UpdatePosition(glm::vec2{ -(dt) *EIGHT_TIME_PER_LIFE,0 });//one space
                    if (energy->GetScale().x < 0.1)
                        energy->SetScale({ -0.1,0 });
                }
            }
        }
    }
}

void DownNote::Die_effect(double)
{
    if (ishit == false)
        return;

    SetRotation(glm::radians(30.f));

    if (score_ == 3)
        SetVelocity({ -5 ,  30 });
    else
        SetVelocity({ -15 ,  15 });
}
void DownNote::Draw(glm::mat3 camera_matrix)
{

    GameObject::Draw(camera_matrix);
}

glm::vec2 DownNote::Getposition()
{
    return GameObject::GetPosition();
}

void DownNote::Score_Check(int score)
{
    switch (score)
    {
        case static_cast<int>(SCORE::PERFECT) :
        {
            Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
            Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
            GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(DownNote_anim::explosion));
            isMiss = false;
            ishit = true;
            score_ = 3;
            if (Engine::GetGSComponent<Score>() != nullptr)
            {
                Engine::GetGSComponent<Score>()->AddScore(score);
            }                
            break;
        }
        case static_cast<int>(SCORE::GOOD) :
        {
            Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
            Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
            GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(DownNote_anim::explosion));
            isMiss = false;
            ishit = true;
            score_ = 2;
            if (Engine::GetGSComponent<Score>() != nullptr)
            {
                Engine::GetGSComponent<Score>()->AddScore(score);
            }                break;
        }
        case static_cast<int>(SCORE::BAD) :
        {
            Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
            Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
            GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(DownNote_anim::explosion));
            isMiss = false;
            ishit = true;
            if (Engine::GetGSComponent<Score>() != nullptr)
            {
                Engine::GetGSComponent<Score>()->AddScore(score);
            }                break;
        }
        case static_cast<int>(SCORE::MISS) :
        {
            if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset" &&
                Engine::GetGameStateManager().GetCurrstate()->GetName() != "Tutorial")
            {
                isMiss = true;
                if (Engine::GetGSComponent<MissEmitter>() != nullptr)
                {
                    Engine::GetGSComponent<MissEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
                    if (Engine::GetGSComponent<Score>() != nullptr)
                    {
                        Engine::GetGSComponent<Score>()->AddScore(score);
                    }
                }
            }
        }
        default:
            break;
    }
}
