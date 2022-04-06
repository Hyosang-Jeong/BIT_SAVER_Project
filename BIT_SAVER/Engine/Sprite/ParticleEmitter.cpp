/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ParticleEmitter.cpp
Project: BIT_SAVER
Author: Hyosang Jung
-----------------------------------------------------------------*/
#include"ParticleEmitter.h"
#include"../GameObject/GameObjectManager.h"  // add to the game object manager 
#include"../Engine.h" //GetGscomponent
ParticleEmitter::ParticleEmitter(double lifetime) :lifetime(lifetime), particleIndexToUse(0)
{}

ParticleEmitter::~ParticleEmitter()
{
	particleMemoryPool.clear();
}

void ParticleEmitter::AddParticle(Particle* particleData)
{
	particleMemoryPool.push_back(particleData);
	if (particleData->GetObjectType() == GameObjectType::Hit)
	{
		particleData->SetScale({ 2,2 });
	}
	if (particleData->GetObjectType() == GameObjectType::PerfectParticle)
	{
		particleData->SetScale({ 1.5,1 });
	}
	Engine::GetGSComponent<GameObjectManager>()->Add(particleData);

}

void ParticleEmitter::Emit(int number, glm::vec2 position, glm::vec2 emitterVelocity, glm::vec2 emitVector, double spread)
{

	if (particleMemoryPool[particleIndexToUse]->IsAlive() == true)
	{
		Engine::GetLogger().LogError("Overwrite a particle");
	}

	while (number != 0)
	{
		double angle = (((rand() % 1024) / 1024.0) * spread) - spread / 2.0;
		double magnitude = ((rand() % 1024) / 2048.0) + 0.5;


		glm::mat3 rotation_matrix
		{
			cos(angle * (float)3.14 / (float)180),sin(angle * (float)3.14 / (float)180),0,
		   -sin(angle * (float)3.14 / (float)180),cos(angle * (float)3.14 / (float)180),0,
			0,0,1
		};
		emitVector.x = (rotation_matrix[0].x * emitVector.x) + (rotation_matrix[1].x * emitVector.x);

		emitVector.y = (rotation_matrix[0].y * emitVector.y) + (rotation_matrix[1].y * emitVector.y);

		glm::vec2 Velocity = emitVector + emitterVelocity;

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

ParticleEmitter::Particle::Particle(const std::filesystem::path& spriteFile) :life(0), GameObject({ 0,0 })
{
	AddGOComponent(new Sprite(spriteFile, this));
}

void ParticleEmitter::Particle::Revive(glm::vec2 Position, glm::vec2 Velocity, double Life)
{
	this->life = Life;
	SetPosition(Position);
	SetVelocity(Velocity);
	GameObject::Update(0);
	if (this->GetObjectType() == GameObjectType::Hit)
	{
		GetGOComponent<Sprite>()->PlayAnimation(0);
	}

}

void ParticleEmitter::Particle::Update(double dt)
{
	if (IsAlive() == true)
	{
		life -= dt;
		GameObject::Update(dt);
	}
}

void ParticleEmitter::Particle::Draw(glm::mat3 matrix)
{
	if (IsAlive() == true)
	{
		GameObject::Draw(matrix);
	}
}
