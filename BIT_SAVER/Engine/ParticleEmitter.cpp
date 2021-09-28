/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ParticleEmitter.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 5/24/2021
-----------------------------------------------------------------*/
#include"ParticleEmitter.h"
#include"GameObjectManager.h"  // add to the game object manager 
#include"Engine.h" //GetGscomponent
CS230::ParticleEmitter::ParticleEmitter(double lifetime):lifetime(lifetime),particleIndexToUse(0)
{}

CS230::ParticleEmitter::~ParticleEmitter()
{
	particleMemoryPool.clear();
}

void CS230::ParticleEmitter::AddParticle(Particle* particleData)
{
	particleMemoryPool.push_back(particleData);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(particleData);
	
}

void CS230::ParticleEmitter::Emit(int number, math::vec2 position, math::vec2 emitterVelocity, math::vec2 emitVector, double spread)
{
	if (particleMemoryPool[particleIndexToUse]->IsAlive() == true)
	{
		Engine::GetLogger().LogError("Overwrite a particle");
	}
	while (number != 0)
	{
		double angle = (((rand() % 1024) / 1024.0) * spread) - spread/2.0;
		double magnitude = ((rand() % 1024) / 2048.0) + 0.5;

		math::vec2 Velocity = (math::RotateMatrix(angle) * emitVector) + emitterVelocity;
		Velocity *= magnitude;

		particleMemoryPool[particleIndexToUse]->Revive(position, Velocity, lifetime);
		particleIndexToUse++;
		if (particleIndexToUse == static_cast<int>(particleMemoryPool.size()))
		{
			particleIndexToUse = 0;
		}
		number--;
	}
}

CS230::ParticleEmitter::Particle::Particle(const std::filesystem::path& spriteFile) :life(0)
{
	AddGOComponent(new CS230::Sprite(spriteFile, this));
}

void CS230::ParticleEmitter::Particle::Revive(math::vec2 Position, math::vec2 Velocity, double Life)
{
	this->life = Life;
	SetPosition(Position);
	SetVelocity(Velocity);
	GetGOComponent<CS230::Sprite>()->PlayAnimation(0);
}

void CS230::ParticleEmitter::Particle::Update(double dt)
{
	if (IsAlive() == true)
	{
		life -= dt;
		GameObject::Update(dt);
	}
}

void CS230::ParticleEmitter::Particle::Draw(math::TransformMatrix matrix)
{
	if (IsAlive() == true)
	{
		GameObject::Draw(matrix);
	}
}
