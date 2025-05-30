/*
*  Vanguard.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 30.05.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include "Enemy/EnemySpaceship.hpp"

namespace SF
{
	class BulletShooter;
	//! Vanguard class represents a specific type of enemy spaceship in the game.
	class Vanguard : public EnemySpaceship
	{
	public:
		Vanguard(World* InWorld, const std::filesystem::path& FilePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png", float InCollisionDamage = -200.f, const std::string& InName = "Vanguard");
		Vanguard(const Vanguard&) = delete;
		Vanguard(Vanguard&&) = delete;
		Vanguard& operator=(const Vanguard&) = delete;
		Vanguard& operator=(Vanguard&&) = delete;
		virtual ~Vanguard() = default;

		virtual void Tick(float DeltaTime) override;
		virtual void Shoot() override;

	private:
		std::unique_ptr<BulletShooter> BulletShooterPtr; //!< Pointer to the BooletShooter component for shooting bullets.
	};
} // namespace SF
