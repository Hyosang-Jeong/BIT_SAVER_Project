#include "obstacle.h"
#include"../../Engine/Sprite/Texture.h"
Obstacle::Obstacle(glm::vec2 startPos, glm::vec2 velocity):
	GameObject(startPos, glm::vec2{ 2,2 })
{
	AddGOComponent(new Sprite("../images/obstacle.png", this));
	SetVelocity(velocity);
}

void Obstacle::Update(double dt)
{
	GameObject::Update(dt);
}


void Obstacle::Draw(glm::mat3 )
{
	//Sprite* spritePtr = GetGOComponent<Sprite>();

	//if (spritePtr != nullptr)
	//{
	//	spritePtr->textureptr->Draw(mdl_to_ndc_xform * camera_matrix, { 0,0 }, { 1,1 });
	//}
}
