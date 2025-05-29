/*
*  Explosion.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 29.05.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "VFX/Explosion.hpp"
#include "framework/MathUtility.hpp"
#include "VFX/Particle.hpp"
#include "framework/World.hpp"
#include <memory>

namespace SF
{
	const std::vector<std::string>  Explosion::ParticleTextures = { {"SpaceShooterRedux/PNG/Effects/star1.png"},
																	{"SpaceShooterRedux/PNG/Effects/star2.png"},
																	{"SpaceShooterRedux/PNG/Effects/star3.png"} };

	Explosion::Explosion(uint32_t PerticleAmount, float Duration)
		: PerticleAmount{ PerticleAmount }
		, Duration{ Duration }
	{
	}

	void Explosion::SpawnExplosion(World& InWorld, const sf::Vector2f& Location)
	{
		for (uint32_t i = 0; i < PerticleAmount; ++i)
		{
			std::string TexturePath = ParticleTextures[SF::Math::RandomNumber<uint32_t>(0, ParticleTextures.size())];
			std::weak_ptr<Particle> ParticlePtr = InWorld.SpawnActor<Particle>(TexturePath, "ExplosionParticle");
			if (auto Particle = ParticlePtr.lock())
			{
				// Set random properties for the particle
				Particle->RandomLifeTime(LifetimeMin, LifetimeMax);
				// Set the particle's position to the explosion center (could be passed as a parameter)
				Particle->SetActorLocation(Location);
				Particle->RandomSize(ParticleSizeMin, ParticleSizeMax);
				Particle->RandomVelocity(ParticleSpeedMin, ParticleSpeedMax);
				Particle->GetActorSprite().setColor(ParticleColor); // Set the particle color
			}
		}
	}

	void Explosion::SpawnExplosion(World& InWorld, const sf::Vector2f& Location, float InLifetimeMin, float inLifetimeMax,
		float InParticleSpeedMin, float InParticleSpeedMax,
		float InParticleSizeMin, float InParticleSizeMax,
		const sf::Color& InParticleColor)
	{
		for (uint32_t i = 0; i < PerticleAmount; ++i)
		{
			std::string TexturePath = ParticleTextures[SF::Math::RandomNumber<uint32_t>( 0, (ParticleTextures.size() - 1) )];
			std::weak_ptr<Particle> ParticlePtr = InWorld.SpawnActor<Particle>(TexturePath, "ExplosionParticle");
			if (auto Particle = ParticlePtr.lock())
			{
				// Set random properties for the particle
				Particle->RandomLifeTime(InLifetimeMin, inLifetimeMax);
				// Set the particle's position to the explosion center (could be passed as a parameter)
				Particle->SetActorLocation(Location);
				Particle->RandomSize(InParticleSizeMin, InParticleSizeMax);
				Particle->RandomVelocity(InParticleSpeedMin, InParticleSpeedMax);
				Particle->GetActorSprite().setColor(InParticleColor); // Set the particle color
			}
		}
	}
}

