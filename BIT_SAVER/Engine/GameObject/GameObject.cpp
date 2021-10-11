/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 4/16/2021
-----------------------------------------------------------------*/
#include"GameObject.h"
#include"../Engine.h"
GameObject::GameObject(glm::vec2 position) : GameObject(position, 0, { 1, 1 }) {}

GameObject::GameObject(glm::vec2 position, double rotation, glm::vec2 scale)
    : velocity{ 0,0 }, position(position), updateMatrix(true),
    scale(scale), rotation(rotation)
{

}

void GameObject::Update(double dt)
{
    //currState->Update(this, dt);
    ////sprite.Update(dt);
    if (velocity.x != 0 || velocity.y != 0)
    {
        UpdatePosition({ velocity.x * dt, velocity.y * dt });
    }
    //currState->TestForExit(this);

    glm::mat3 scale_matrix
    {
        scale.x,0,0,
        0,scale.y,0,
        0,0,1
    };
    double PI = 3.14159265359;
    orientation.x += orientation.y * (GLfloat)dt;


    glm::mat3 rotation_matrix
    {
        cos(orientation.x * (float)PI / (float)180),sin(orientation.x * (float)PI / (float)180),0,
       -sin(orientation.x * (float)PI / (float)180),cos(orientation.x * (float)PI / (float)180),0,
        0,0,1
    };

    glm::mat3 trans_matrix
    {
        1,0,0,
         0,1,0,
        position.x,position.y,1
    };
   glm::mat3 ndcscale_matrix
   {
      1.0 / world_range  ,0  ,0,
       0,  1 / world_range ,0,
       0,0,1
   };

   glm::vec2 texture_size = texture.GetSize();
   glm::vec2 winsize = Engine::GetWindow().GetSize();
  

  
   texture_size.x = ((world_range*2) * texture_size.x) / winsize.x;
   texture_size.y = ((world_range*2) * texture_size.y) / winsize.y;


   //collision_box.min = { position.x - (texture_size.x / 2), position.y - (texture_size.y / 2) };
   //collision_box.max = { position.x + (texture_size.x / 2), position.y + (texture_size.y / 2) };

    mdl_to_ndc_xform = ndcscale_matrix* trans_matrix  *rotation_matrix* scale_matrix;

}

void GameObject::Draw() 
{
    //sprite.Draw(cameraMatrix * GetMatrix());
}

const glm::mat3& GameObject::GetMatrix()
{
    return mdl_to_ndc_xform;
}

void GameObject::SetPosition(glm::vec2 newPosition) {
    position = newPosition;
    updateMatrix = true;
}

void GameObject::SetVelocity(glm::vec2 newVelocity) {
    velocity = newVelocity;
}

void GameObject::UpdatePosition(glm::vec2 adjustPosition) {
    position += adjustPosition;
    updateMatrix = true;
}

const glm::vec2& GameObject::GetPosition() const { return position; }

const glm::vec2& GameObject::GetVelocity() const
{
    return velocity;
}

const glm::vec2& GameObject::GetScale() const
{
    return scale;
}

const AABB& GameObject::GetAABB() const
{
    return collision_box;
}

double GameObject::GetRotation() const
{
    return rotation;
}

void GameObject::UpdateVelocity(glm::vec2 adjustPosition)
{
    velocity += adjustPosition;
}

void GameObject::SetScale(glm::vec2 newScale)
{
    scale = newScale;
    updateMatrix = true;
}

void GameObject::SetRotation(double newRotationAmount)
{
    rotation = newRotationAmount;
    updateMatrix = true;
}

void GameObject::UpdateRotation(double newRotationAmount)
{
    rotation += newRotationAmount;
    updateMatrix = true;
}

void GameObject::set_destroy(bool value)
{
    is_destroy = value;
}

bool GameObject::Destroy()
{
    return is_destroy;
}

