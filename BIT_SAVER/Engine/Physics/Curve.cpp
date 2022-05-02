#include "Curve.h"
#include "../Engine/GameObject/GameObject.h"


Curve::Curve(GameObject* m_object) : _object(m_object)
{}

//vec2 result = (start_val * start_point[num].pos) + (start_derive_val * (start_point[num].tangent - start_point[num].pos))
//              + (end_val * end_point[num].pos) + (end_derive_val * (end_point[num].tangent - end_point[num].pos));
void Curve::BotWave()
{

    float t = -(_object->GetPosition().x - 10.f) / 14.f;

    float start_val = (2 * t * t * t) - (3 * t * t) + 1;
    float start_derive_val = (t * t * t) - (2 * t * t) + t;
    float end_val = (-2 * t * t * t) + (3 * t * t);
    float end_derive_val = (t * t * t) - (t * t);

    glm::vec2 result = (start_val * glm::vec2(10,-7)) + (start_derive_val * (glm::vec2(-10, -10) - glm::vec2(10, -7)))
                         + (end_val * glm::vec2(-4, -7)) + (end_derive_val * (glm::vec2(4, -10) - glm::vec2(-4, -7)));
    result.y += 7;
    result.y *= 4;
    result.y -= 7;


    _object->SetPosition({ _object->GetPosition().x, result.y });
}

void Curve::TOPWave()
{

    float t = -(_object->GetPosition().x - 10.f) / 14.f;

    float start_val = (2 * t * t * t) - (3 * t * t) + 1;
    float start_derive_val = (t * t * t) - (2 * t * t) + t;
    float end_val = (-2 * t * t * t) + (3 * t * t);
    float end_derive_val = (t * t * t) - (t * t);

    glm::vec2 result = (start_val * glm::vec2(10, 3)) + (start_derive_val * (glm::vec2(-10, 10) - glm::vec2(10, 3)))
        + (end_val * glm::vec2(-4, 3)) + (end_derive_val * (glm::vec2(4, 10) - glm::vec2(-4, 3)));
    result.y -= 3;
    result.y *= 4;
    result.y += 3;


    _object->SetPosition({ _object->GetPosition().x, result.y });
}


void Curve::TopToBot()
{

    glm::vec2 pos = _object->GetPosition();
    float t = -(pos.x - 10.f) / 14.f;

    float start_val = (2 * t * t * t) - (3 * t * t) + 1;
    float start_derive_val = (t * t * t) - (2 * t * t) + t;
    float end_val = (-2 * t * t * t) + (3 * t * t);
    float end_derive_val = (t * t * t) - (t * t);

    glm::vec2 result = (start_val * glm::vec2(-10, 3)) + (start_derive_val * (glm::vec2(-10, -5) - glm::vec2(-10, 3)))
        + (end_val * glm::vec2(-4, -7)) + (end_derive_val * (glm::vec2(4, -5) - glm::vec2(-4, -7)));
    result.y += 7;
    result.y *= 2;
    result.y -= 7;

    _object->SetPosition({ _object->GetPosition().x, result.y });
}

void Curve::BotToTop()
{


    float t = -(_object->GetPosition().x - 10.f) / 14.f;

    float start_val = (2 * t * t * t) - (3 * t * t) + 1;
    float start_derive_val = (t * t * t) - (2 * t * t) + t;
    float end_val = (-2 * t * t * t) + (3 * t * t);
    float end_derive_val = (t * t * t) - (t * t);

    glm::vec2 result = (start_val * glm::vec2(-10, -7)) + (start_derive_val * (glm::vec2(-10, 5) - glm::vec2(-10, -7)))
        + (end_val * glm::vec2(-4, 3)) + (end_derive_val * (glm::vec2(4, 5) - glm::vec2(-4, 3)));
    result.y -= 3;
    result.y *= 2;
    result.y += 3;


    _object->SetPosition({ _object->GetPosition().x, result.y });
}

