#include"Collision.h"

Collision::Collision(glm::vec2 scale) :texture_scale(scale) {}


const AABB& Collision::GetAABB() const
{
    return collision_box;
}

void Collision::UpdateCollision(glm::vec2 pos)
{
    collision_box.min = { pos.x - (texture_scale.x / 2.f), pos.y - (texture_scale.y / 2.f) };
    collision_box.max = { pos.x + (texture_scale.x / 2.f), pos.y + (texture_scale.y / 2.f) };
}
