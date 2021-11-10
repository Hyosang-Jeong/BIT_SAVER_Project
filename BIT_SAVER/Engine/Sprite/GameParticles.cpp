/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/24/2021
-----------------------------------------------------------------*/
#include"GameParticles.h"


HitEmitter::HitEmitter() : ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new HitParticle("../spt/hit.spt"));
	}
}
