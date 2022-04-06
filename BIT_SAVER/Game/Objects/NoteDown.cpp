#include"../../Engine/Engine.h"
#include "NoteDown.h"
#include"../../Engine/Sprite/GameParticles.h"
#include "EnergyBar.h"
#include "Score.h"
#include "Score Enum.h"
//#include"obstacle.h"


DownNote::DownNote(glm::vec2 startPos, glm::vec2 velocity) :
	isMiss(false),


    UpAttackKey(InputKey::Keyboard::None),
    DownAttackKey(InputKey::Keyboard::None),
    GameObject(startPos, glm::vec2{ 1.5,1.5 })
{
    if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
    {
        energy = (static_cast<EnergyBar*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Energy_bar)));
    }
    AddGOComponent(new Sprite("../spt/belcoz.spt", this));
    GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(DownNote_anim::flying));
    SetVelocity(velocity);

}

void DownNote::Update(double dt)
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
        if (energy->GetScale().x > 0)
        {
            if (GetGOComponent<Sprite>()->GetCurrentAnim() != static_cast<int>(DownNote_anim::explosion))
            {
                energy->SetScale(glm::vec2{ energy->GetScale().x - (dt / 10),energy->GetScale().y });
                energy->UpdatePosition(glm::vec2{ -(dt / 20),0 });
            }
        }
    }
}


void DownNote::Draw(glm::mat3 camera_matrix)
{

    GameObject::Draw(camera_matrix);
}

glm::vec2 DownNote::Getposition()
{
    return GameObject::GetPosition();
}

void DownNote::Hit_Check()
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
        if (GetGOComponent<Sprite>()->GetCurrentAnim() != static_cast<int>(DownNote_anim::explosion))
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

int DownNote::Score_check()
{
    float HeroPostion = 0;
    float NotePosition = GetPosition().x;

    if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
    {
        HeroPostion = -4.f;
    }
    if (NotePosition - HeroPostion <= 0.5f && NotePosition - HeroPostion >= -0.5f)
    {
        return static_cast<int>(SCORE::PERFECT);
    }
    else if (NotePosition - HeroPostion <= 1.f && NotePosition - HeroPostion >= -1.f)
    {
        return static_cast<int>(SCORE::GOOD);
    }
    else if (NotePosition - HeroPostion <= 1.5f && NotePosition - HeroPostion >= -1.5f)
    {
        return static_cast<int>(SCORE::BAD);
    }
    return static_cast<int>(SCORE::MISS);
}
