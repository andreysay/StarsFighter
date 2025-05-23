#pragma once
#include "Shooter.hpp"
#include <SFML/System.hpp>
#include <vector>

namespace SF
{
	class Actor;
	class Bullet;
	static const size_t BulletPoolSize = 100;

	class BulletShooter : public Shooter
	{
	public:
		BulletShooter() = default;
		BulletShooter(Actor* InOwner, float InCooldownTime = 0.1f);
		bool IsOnCooldown() const override;
	private:
		void Shoot_Impl() override;
		
	private:
		std::vector<std::weak_ptr<Bullet>> Bullets;
		sf::Clock CooldownClock;
		float CooldownTime{ 0.1f }; // Example cooldown time in seconds
	};
}