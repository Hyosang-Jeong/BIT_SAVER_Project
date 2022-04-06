/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ParticleEmitter.h
Project: BIT_SAVER
Author:	Hyosang Jung
-----------------------------------------------------------------*/
#pragma once
#include <filesystem>
#include <vector>
#include "..\GameObject\GameObject.h"
#include "..\Engine\Component.h"



    class ParticleEmitter : public Component
    {
    protected:
        class Particle : public GameObject
        {
        public:
            Particle(const std::filesystem::path& spriteFile);
            void Revive(glm::vec2 Position, glm::vec2 Velocity, double Life);
            void Update(double dt) override;
            void Draw(glm::mat3 matrix) override;
            bool IsAlive() 
            { 
                return life > 0; 
            }
        private:
            double life;
        };
    public:
        ParticleEmitter(double lifetime);
        virtual ~ParticleEmitter();
        void AddParticle(Particle* particleData);
        void Emit(int number, glm::vec2 position, glm::vec2 emitterVelocity, glm::vec2 emitVector, double spread);
    private:
        std::vector<Particle*> particleMemoryPool;
        int particleIndexToUse;
        double lifetime;
    };
