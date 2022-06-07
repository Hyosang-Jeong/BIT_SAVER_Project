#include"../../Engine/Engine.h"
#include "NoteUp.h"
#include"../../Engine/Sprite/GameParticles.h"
#include "EnergyBar.h"
#include "Score.h"
#include "Score Enum.h"
//#include"obstacle.h"
#include "../../Engine/Physics/Curve.h"

UpNote::UpNote(glm::vec2 startPos, glm::vec2 velocity, int movement) :
    isMiss(false), ishit(false), Movement(movement), 
    GameObject(startPos, glm::vec2{ -8,8 })
{
    if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
    {
        energy = (static_cast<EnergyBar*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Energy_bar)));
    }
    AddGOComponent(new Sprite("../spt/fly.spt", this));
    AddGOComponent(new Curve(this));
    GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(UpNote_anim::flying));
    SetVelocity(velocity);

}

void UpNote::Update(double dt)
{

    if (Movement == 99)
        GetGOComponent<Curve>()->TOPWave();
    else if (Movement == 101)
        GetGOComponent<Curve>()->BotToTop();

    GameObject::Update(dt);

    if (GetPosition().x < -10)
    {
        set_destroy(true);
    }

    Die_effect(dt);

    if (isMiss == true)
    {
        if (GetGOComponent<Sprite>()->GetCurrentAnim() != static_cast<int>(UpNote_anim::explosion))
        {
            if (energy != nullptr)
            {
                if (energy->GetScale().x > 0)
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


void UpNote::Draw(glm::mat3 camera_matrix)
{
    glm::mat3 trans_mat
    {
            1,0,0,
            0,1,0,
            -0.25,0,1
    };
    GameObject::Draw(camera_matrix * trans_mat);
}

glm::vec2 UpNote::Getposition()
{
    return GameObject::GetPosition();
}

void UpNote::Die_effect(double )
{
    if (ishit == false)
        return;

    SetRotation(glm::radians(30.f));

    if(score_ == 3)
         SetVelocity({ -5 ,  30 });
    else
        SetVelocity({ -15 ,  15 });

}
void UpNote::Score_Check(int score)
{
    switch (score)
    {

        case static_cast<int>(SCORE::PERFECT) :
        {
            Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
            Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
            GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(UpNote_anim::explosion));
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
            Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
            Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
            GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(UpNote_anim::explosion));
            isMiss = false;
            ishit = true;

            score_ = 2;
            if (Engine::GetGSComponent<Score>() != nullptr)
            {
                Engine::GetGSComponent<Score>()->AddScore(score);
            }               
            break;
        }
        case static_cast<int>(SCORE::BAD) :
        {
            Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
            Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
            GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(UpNote_anim::explosion));
            isMiss = false;
            ishit = true;
            if (Engine::GetGSComponent<Score>() != nullptr)
            {
                Engine::GetGSComponent<Score>()->AddScore(score);
            }                
            break;
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

