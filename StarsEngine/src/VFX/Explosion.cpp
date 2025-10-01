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

	Explosion::Explosion(uint32_t InPerticleAmount, float InLifetimeMin, float inLifetimeMax,
		float InParticleSpeedMin, float InParticleSpeedMax,
		float InParticleSizeMin, float InParticleSizeMax,
		const sf::Color& InParticleColor)
		: ParticleAmount{ InPerticleAmount }
		, LifetimeMin{ InLifetimeMin }
		, LifetimeMax{ inLifetimeMax }
		, ParticleSpeedMin{ InParticleSpeedMin }
		, ParticleSpeedMax{ InParticleSpeedMax }
		, ParticleSizeMin{ InParticleSizeMin }
		, ParticleSizeMax{ InParticleSizeMax }
		, ParticleColor{ InParticleColor }
	{
	}

	Explosion::~Explosion()
	{

	}

	//void Explosion::SpawnExplosion(World& InWorld, const sf::Vector2f& Location)
	//{
	//	for (uint32_t i = 0; i < ParticleAmount; ++i)
	//	{
	//		std::string TexturePath = ParticleTextures[SF::Math::RandomNumber<uint32_t>(0, ParticleTextures.size())];
	//		std::weak_ptr<Particle> ParticlePtr = InWorld.SpawnActor<Particle>(TexturePath, "ExplosionParticle");
	//		if (auto Particle = ParticlePtr.lock())
	//		{
	//			// Set random properties for the particle
	//			Particle->RandomLifeTime(LifetimeMin, LifetimeMax);
	//			// Set the particle's position to the explosion center (could be passed as a parameter)
	//			Particle->SetActorLocation(Location);
	//			Particle->RandomSize(ParticleSizeMin, ParticleSizeMax);
	//			Particle->RandomVelocity(ParticleSpeedMin, ParticleSpeedMax);
	//			Particle->GetActorSprite().setColor(ParticleColor); // Set the particle color
	//		}
	//	}
	//}

	void Explosion::SpawnExplosion(World* InWorld, const sf::Vector2f& Location, uint32_t InParticleAmount)
	{
		if (!InWorld) return;
		// Clone the explosion effect to use its properties
		std::unique_ptr<Explosion> ExplosionEffect = Clone(InParticleAmount);
		for (uint32_t i = 0; i < InParticleAmount; ++i)
		{
			std::string TexturePath = Explosion::ParticleTextures[SF::Math::RandomNumber<uint32_t>( 0, (Explosion::ParticleTextures.size() - 1) )];
			std::weak_ptr<Particle> ParticlePtr = InWorld->SpawnActor<Particle>(TexturePath, false);
			if (auto Particle = ParticlePtr.lock())
			{
				// Set random properties for the particle
				Particle->RandomLifeTime(ExplosionEffect->LifetimeMin, ExplosionEffect->LifetimeMax);
				// Set the particle's position to the explosion center (could be passed as a parameter)
				Particle->SetActorLocation(Location);
				Particle->RandomSize(ExplosionEffect->ParticleSizeMin, ExplosionEffect->ParticleSizeMax);
				Particle->RandomVelocity(ExplosionEffect->ParticleSpeedMin, ExplosionEffect->ParticleSpeedMax);
				Particle->GetActorSprite().setColor(ExplosionEffect->ParticleColor); // Set the particle color
			}
		}
	}
	std::unique_ptr<Explosion> Explosion::Clone(uint32_t InParticleAmount)
	{
		return std::unique_ptr<Explosion>(new Explosion{ InParticleAmount, 0.5f, 1.f, 100.f, 200.f, 1.f, 3.f, sf::Color(255, 128, 0, 255) });
	}
}

