/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Project: BIT_SAVER
Author:  Hyosang Jung 

-----------------------------------------------------------------*/
#include"GameObject.h"
#include"../Engine.h"

GameObject::GameObject(glm::vec2 position) : GameObject(position,  { 1, 1 }) {}

GameObject::GameObject(glm::vec2 position, glm::vec2 scale)
    : velocity{ 0,0 }, position(position), updateMatrix(true),
    scale(scale), currState(&state_nothing), rotation( 0.0 )
{
}

void GameObject::ResolveCollision(GameObject* )
{
    return;
}

void GameObject::Update(double dt)
{
    UpdateGOComponents(dt);
    currState->Update(this, dt);
    if (velocity.x != 0 || velocity.y != 0)
    {
        UpdatePosition({ velocity.x * dt, velocity.y * dt });
    }
    glm::mat3 scale_matrix
    {
        scale.x,0,0,
        0,scale.y,0,
        0,0,1
    };

	glm::mat3 rotation_matrix
	{
		cos(rotation), sin(rotation), 0,
	   -sin(rotation), cos(rotation), 0,
		0, 0, 1
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
   currState->TestForExit(this);
   //collision.UpdateCollision(position);
   texture_ndc = scale / 2.f;
    mdl_to_ndc_xform = ndcscale_matrix* trans_matrix  *rotation_matrix* scale_matrix;

}

void GameObject::Draw(glm::mat3 camera_matrix)
{
    Sprite* spritePtr = GetGOComponent<Sprite>();

    if (spritePtr != nullptr)
    {
        spritePtr->Draw(mdl_to_ndc_xform * camera_matrix);
    }
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

const glm::vec2& GameObject::GetPosition() const 
{ 
    return position; 
}

const glm::vec2& GameObject::GetVelocity() const
{
    return velocity;
}

const glm::vec2& GameObject::GetScale() const
{
    return scale;
}

const double GameObject::GetRotation() const
{
    return rotation;
}

const glm::vec2& GameObject::GetTexturetoNDC() const
{
    return texture_ndc;
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

void GameObject::UpdateScale(glm::vec2 adjustScale)
{
    scale += adjustScale;

    updateMatrix = true;
}

void GameObject::SetRotation(double newRotationAmount)
{
    rotation = newRotationAmount;
}

void GameObject::UpdateRotation(double adjustRotation)
{
    rotation += adjustRotation;
    updateMatrix = true;
}

void GameObject::ChangeState(ObjectState* newState)
{
    currState = newState;

    currState->Enter(this);
}

void GameObject::set_destroy(bool value)
{
    is_destroy = value;
}

bool GameObject::Destroy()
{
    return is_destroy;
}

