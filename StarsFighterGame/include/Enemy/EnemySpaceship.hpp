/*
*  EnemySpaceship.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 30.05.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once

#include "Spaceship/Spaceship.hpp"

namespace SF
{
	//! EnemySpaceship class represents an enemy spaceship actor in the game.
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* InWorld, const std::filesystem::path& FilePath, float InCollisionDamage = -200.f, bool IsAnimated = false, const std::string& InName = "EnemySpaceship");
		EnemySpaceship(const EnemySpaceship&) = delete;
		EnemySpaceship(EnemySpaceship&&) = delete;
		EnemySpaceship& operator=(const EnemySpaceship&) = delete;
		EnemySpaceship& operator=(EnemySpaceship&&) = delete;
		virtual ~EnemySpaceship() = default;

		virtual void Tick(float DeltaTime) override;
		virtual void OnActorBeginOverlap(Actor* OtherActor) override;

	private:
		float CollisionDamage{ -200.f }; //!< Damage dealt by the enemy spaceship on collision.
	};
} // namespace SF
