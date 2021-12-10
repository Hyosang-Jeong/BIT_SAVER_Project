/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.cpp
Project: BIT_SAVER
Author: Hyosang Jung
-----------------------------------------------------------------*/
#include"GameParticles.h"


HitEmitter::HitEmitter() : ParticleEmitter(0.4)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new HitParticle("../spt/hit.spt"));
	}
}

PerfectEmitter::PerfectEmitter() : ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new PerfectParticle("../images/perfect.png"));
	}
}

GoodEmitter::GoodEmitter() : ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new GoodParticle("../images/Good.png"));
	}
}

BadEmitter::BadEmitter() : ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new BadParticle("../images/Bad.png"));
	}
}

MissEmitter::MissEmitter() : ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new MissParticle("../images/Miss.png"));
	}
}
