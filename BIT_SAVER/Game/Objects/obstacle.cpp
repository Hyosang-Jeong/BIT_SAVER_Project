#include "obstacle.h"
#include"../../Engine/Sprite/Texture.h"
Obstacle::Obstacle(glm::vec2 startPos, glm::vec2 velocity):
	GameObject(startPos, glm::vec2{ 1,6 })
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
	//spritePtr->textureptr->Draw(mdl_to_ndc_xform * camera_matrix, { 0,0 }, { 0.1,0.1 });
 //  //	spritePtr->textureptr->Draw(0.f, { 5,5 }, { 10,10 });
	//if (spritePtr != nullptr)
	//{
	//	//spritePtr->textureptr.
	//	//spritePtr->Draw(mdl_to_ndc_xform * camera_matrix);
	//	//textureptr->Draw(displayMatrix, GetFrameTexel(animations[currAnim]->GetDisplayFrame()), ndc_frameSize);
	//}
}
