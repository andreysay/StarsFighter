/*
*  Spaceship.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include "framework/Actor.hpp"
#include "framework/Core.hpp"
#include "framework/HealthComponent.hpp"

namespace SF
{
	//! Spaceship class represents a spaceship actor in the game.
	class Spaceship : public Actor
	{
	public:
		//! Constructor for Spaceship, initializes the actor with a texture and name.
		Spaceship(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName = "Spaceship");
		Spaceship(const Spaceship&) = delete;
		Spaceship(Spaceship&&) = delete;
		Spaceship& operator=(const Spaceship&) = delete;
		Spaceship& operator=(Spaceship&&) = delete;
		~Spaceship() = default;
		
		virtual void Tick(float DeltaTime) override;
		virtual void Shoot();
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float DamageAmount) override;


		void SetVelocity(const sf::Vector2f& InVelocity);
		virtual void OnHeathChanged(float DeltaHealth);
		virtual void OnTakenDamage(float DamageAmount);
		virtual void OnDead();
		inline sf::Vector2f GetVelocity() const { return SpaceshipVelocity; }

	private:
		//! Blinks the spaceship when it takes damage
		void Blink();
		//! Updates the blinking effect based on the time delta
		void UpdateBlink(float DeltaTime);

	private:
		sf::Vector2f SpaceshipVelocity;
		HealthComponent HealthComponent;
		float BlinkTime{ 0.f }; // Time for blinking effect when taking damage
		float BlinkDuration{ 0.2f }; // Duration of the blinking effect
		sf::Color BlinkColorOffset{ 255, 0, 0, 255 }; // Color for blinking effect when taking damage
	};
}