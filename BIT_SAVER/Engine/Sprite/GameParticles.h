/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.h
Project: BIT_SAVER
Author: Hyosang Jung
-----------------------------------------------------------------*/
#pragma once
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
        GameObjectType GetObjectType() { return GameObjectType::Hit; }
        std::string GetObjectTypeName() { return "Hit Particle"; }
    };
   static constexpr int NumParticles = 20;
};

class PerfectEmitter : public ParticleEmitter
{
public:
    PerfectEmitter();
private:
    class PerfectParticle : public ParticleEmitter::Particle
    {
    public:
        PerfectParticle(std::string spriteFile) : ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::PerfectParticle; }
        std::string GetObjectTypeName() { return "Perfect Particle"; }
    };
    static constexpr int NumParticles = 20;
};

class GoodEmitter : public ParticleEmitter
{
public:
    GoodEmitter();
private:
    class GoodParticle : public ParticleEmitter::Particle
    {
    public:
        GoodParticle(std::string spriteFile) : ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Hit GoodParticle"; }
    };
    static constexpr int NumParticles = 20;
};

class BadEmitter : public ParticleEmitter
{
public:
    BadEmitter();
private:
    class BadParticle : public ParticleEmitter::Particle
    {
    public:
        BadParticle(std::string spriteFile) : ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Hit BadParticle"; }
    };
    static constexpr int NumParticles = 20;
};

class MissEmitter : public ParticleEmitter
{
public:
    MissEmitter();
private:
    class MissParticle : public ParticleEmitter::Particle
    {
    public:
        MissParticle(std::string spriteFile) : ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Hit MissParticle"; }
    };
    static constexpr int NumParticles = 20;
};
