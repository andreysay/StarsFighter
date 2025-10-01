/*
*  Particle.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 29.05.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include "framework/Actor.hpp"

namespace SF
{
	//! Particle class represents a particle effect in the game.
	class Particle : public Actor
	{
	public:
		Particle() = delete;
		explicit Particle(World* InWorld, const std::filesystem::path& FilePath, bool IsAnimated = false, const std::string& InName = "Particle");
		Particle(const Particle&) = delete;
		Particle(Particle&&) = delete;
		Particle& operator=(const Particle&) = delete;
		Particle& operator=(Particle&&) = delete;
		virtual ~Particle() = default;


		virtual void Tick(float DeltaTime) override;

		void RandomVelocity(float MinSpeed, float MaxSpeed);
		void RandomSize(float MinSize, float MaxSize);
		void RandomLifeTime(float MinLifetime, float MaxLifetime);
	private:
		void Move(float DeltaTime);
		void FadeOut(float DeltaTime);

	private:
		sf::Vector2f Velocity; // Particle velocity
		float Lifetime; // Particle lifetime in seconds
		sf::Clock Timer; // Timer to track particle lifetime
	};
}