/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.h
Project: 
Author: 
Creation date: 2/26/2021
-----------------------------------------------------------------*/
#include "ParticleEmitter.h"
#include "../../Game/Objects/GameObjectType.h"

class HitEmitter : public ParticleEmitter
{
public:
    HitEmitter();
private:
    class HitParticle : public ParticleEmitter::Particle
    {
    public:
        HitParticle(std::string spriteFile) : ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Hit Particle"; }
    };
    static constexpr int NumParticles = 10;
};

