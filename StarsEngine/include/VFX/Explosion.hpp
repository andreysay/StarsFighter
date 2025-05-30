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
		Explosion() = default; //!< Default constructor.
		Explosion(uint32_t InPerticleAmount, float InDuration);
		Explosion(const Explosion&) = delete;
		Explosion(Explosion&&) = delete;
		Explosion& operator=(const Explosion&) = delete;
		Explosion& operator=(Explosion&&) = delete;
		virtual ~Explosion() = default;

		void SpawnExplosion(World& InWorld, const sf::Vector2f& Location);
		static void SpawnExplosion(World& InWorld, const sf::Vector2f& Location, uint32_t InParticleAmount, float InLifetimeMin, float inLifetimeMax,
			float InParticleSpeedMin = 200.f, float InParticleSpeedMax = 400.f,
			float InParticleSizeMin = 1.f, float InParticleSizeMax = 3.f,
			const sf::Color& InParticleColor = sf::Color(255, 128, 0, 255)); 

	private:
		uint32_t PerticleAmount{100}; //!< Number of particles in the explosion.
		float Duration{1.f};           //!< Duration of the explosion effect.
		float LifetimeMin{0.5f};          //!< Lifetime of the explosion effect in seconds.
		float LifetimeMax{1.f};          //!< Maximum lifetime of the explosion effect in seconds.
		float ParticleSpeedMin{200.f};     //!< Minimum speed of the explosion particles.
		float ParticleSpeedMax{400.f};     //!< Maximum speed of the explosion particles.
		float ParticleSizeMin{1.f};      //!< Minimum size of the explosion particles.
		float ParticleSizeMax{2.f};      //!< Maximum size of the explosion particles.
		sf::Color ParticleColor{ 255, 128, 0, 255 }; //!< Color of the explosion particles.
		// Additional members for explosion properties can be added here.
		static const std::vector<std::string> ParticleTextures; //!< Textures for the explosion particles.

	};
} // namespace SF