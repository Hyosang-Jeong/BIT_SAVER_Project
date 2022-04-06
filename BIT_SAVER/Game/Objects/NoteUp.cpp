#include"../../Engine/Engine.h"
#include "NoteUp.h"
#include"../../Engine/Sprite/GameParticles.h"
#include "EnergyBar.h"
#include "Score.h"
#include "Score Enum.h"
//#include"obstacle.h"

UpNote::UpNote(glm::vec2 startPos, glm::vec2 velocity) :
    isMiss(false),

    UpAttackKey(InputKey::Keyboard::None),
    DownAttackKey(InputKey::Keyboard::None),
    GameObject(startPos, glm::vec2{ -8,8 })
{
    if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
    {
        energy = (static_cast<EnergyBar*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Energy_bar)));
    }
    AddGOComponent(new Sprite("../spt/fly.spt", this));
    GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(UpNote_anim::flying));
    SetVelocity(velocity);

}

void UpNote::Update(double dt)
{
    GameObject::Update(dt);

    UpAttackKey = Engine::GetAttack_Key().UpAttackKey;
    DownAttackKey = Engine::GetAttack_Key().DownAttackKey;
    if (GetPosition().x < -10)
    {
        set_destroy(true);
    }
    Hit_Check();

    if (isMiss == true)
    {
        if (GetGOComponent<Sprite>()->GetCurrentAnim() != static_cast<int>(UpNote_anim::explosion))
        {
            if (energy->GetScale().x > 0)
            {
                energy->SetScale(glm::vec2{ energy->GetScale().x - (dt / 10),energy->GetScale().y });
                energy->UpdatePosition(glm::vec2{ -(dt / 10),0 });
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

void UpNote::Hit_Check()
{

    if ((UpAttackKey.IsKeyDown() == true && UpAttackKey.IsKeyReapeated() == false) && GetPosition().y > 0)
    {
        switch (Score_check())
        {
            case static_cast<int>(SCORE::PERFECT) :
            {
                Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
                isMiss = false;
                Engine::GetGSComponent<Score>()->AddScore(Score_check());
                break;
            }
            case static_cast<int>(SCORE::GOOD) :
            {
                Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
                isMiss = false;
                Engine::GetGSComponent<Score>()->AddScore(Score_check());
                break;
            }
            case static_cast<int>(SCORE::BAD) :
            {
                Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
                isMiss = false;
                Engine::GetGSComponent<Score>()->AddScore(Score_check());
                break;
            }
            default:
                break;
        }

    }

    if ((DownAttackKey.IsKeyDown() == true && DownAttackKey.IsKeyReapeated() == false && GetPosition().y < 0))
    {
        switch (Score_check())
        {
            case static_cast<int>(SCORE::PERFECT) :
            {
                Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
                isMiss = false;
                Engine::GetGSComponent<Score>()->AddScore(Score_check());
                break;
            }
            case static_cast<int>(SCORE::GOOD) :
            {
                Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
                isMiss = false;
                Engine::GetGSComponent<Score>()->AddScore(Score_check());
                break;
            }
            case static_cast<int>(SCORE::BAD) :
            {
                Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
                isMiss = false;
                Engine::GetGSComponent<Score>()->AddScore(Score_check());
                break;
            }
            default:
                break;
        }

    }
    if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
    {
        if (GetGOComponent<Sprite>()->GetCurrentAnim() != static_cast<int>(UpNote_anim::explosion))
        {
            if (Score_check() == static_cast<int>(SCORE::MISS) && isMiss == false && GetPosition().x < -4.f)
            {
                isMiss = true;
                if (Engine::GetGSComponent<MissEmitter>() != nullptr)
                {
                    Engine::GetGSComponent<MissEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
                    Engine::GetGSComponent<Score>()->AddScore(Score_check());
                }
            }
        }
    }

}

int UpNote::Score_check()
{
    float HeroPostion = 0;
    float NotePosition = GetPosition().x;

    if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
    {
        HeroPostion = -4.f;
    }

    if (NotePosition - HeroPostion <= 0.5f && NotePosition - HeroPostion >= -0.5f)//0.4
    {
        return static_cast<int>(SCORE::PERFECT);
    }
    else if (NotePosition - HeroPostion <= 1.f && NotePosition - HeroPostion >= -1.f)//0.4
    {
        return static_cast<int>(SCORE::GOOD);
    }
    else if (NotePosition - HeroPostion <= 1.5f && NotePosition - HeroPostion >= -1.5f)//0.4
    {
        return static_cast<int>(SCORE::BAD);
    }
    return static_cast<int>(SCORE::MISS);
}
