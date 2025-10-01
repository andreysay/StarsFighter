/*
*  Explosion.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 29.05.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SF
{
	class World;
	//! Explosion class represents an explosion effect in the game.
	class Explosion
	{
	public:
		virtual ~Explosion();

		//void SpawnExplosion(World& InWorld, const sf::Vector2f& Location);
		static void SpawnExplosion(World* InWorld, const sf::Vector2f& Location, uint32_t InParticleAmount); 

		static std::unique_ptr<Explosion> Clone(uint32_t InPerticleAmount);

		uint32_t ParticleAmount{ 100 }; //!< Number of particles in the explosion.
		float LifetimeMin{ 0.5f };          //!< Lifetime of the explosion effect in seconds.
		float LifetimeMax{ 1.f };          //!< Maximum lifetime of the explosion effect in seconds.
		float ParticleSpeedMin{ 200.f };     //!< Minimum speed of the explosion particles.
		float ParticleSpeedMax{ 400.f };     //!< Maximum speed of the explosion particles.
		float ParticleSizeMin{ 1.f };      //!< Minimum size of the explosion particles.
		float ParticleSizeMax{ 2.f };      //!< Maximum size of the explosion particles.
		sf::Color ParticleColor{ 255, 128, 0, 255 }; //!< Color of the explosion particles.

	protected:
		Explosion() = default; //!< Default constructor.
		Explosion(uint32_t InPerticleAmount, float InLifetimeMin = 0.5f, float inLifetimeMax = 1.f,
			float InParticleSpeedMin = 200.f, float InParticleSpeedMax = 400.f,
			float InParticleSizeMin = 1.f, float InParticleSizeMax = 3.f,
			const sf::Color& InParticleColor = sf::Color(255, 128, 0, 255));
		Explosion(const Explosion&) = delete;
		Explosion(Explosion&&) = delete;
		Explosion& operator=(const Explosion&) = delete;
		Explosion& operator=(Explosion&&) = delete;

		// Additional members for explosion properties can be added here.
		static const std::vector<std::string> ParticleTextures; //!< Textures for the explosion particles.
	};
} // namespace SF