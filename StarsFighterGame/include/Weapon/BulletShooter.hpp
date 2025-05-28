/*
*  BulletShooter.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include "Shooter.hpp"
#include <SFML/System.hpp>
#include <vector>

namespace SF
{
	class Actor;
	class Bullet;
	//! BulletPoolSize defines the size of the bullet pool for the BulletShooter class.
	static const size_t BulletPoolSize = 100;
	//! BulletShooter class is a shooter that can shoot bullets from a pool of bullets.
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter() = default;
		BulletShooter(Actor* InOwner, float InCooldownTime = 0.1f);
		bool IsOnCooldown() const override;
	private:
		virtual void Shoot_Impl() override;
		
	private:
		std::vector<std::weak_ptr<Bullet>> Bullets;
		sf::Clock CooldownClock;
		float CooldownTime{ 0.1f }; // Example cooldown time in seconds
	};
}