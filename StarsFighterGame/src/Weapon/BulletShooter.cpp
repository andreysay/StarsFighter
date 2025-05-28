#include "Weapon/BulletShooter.hpp"
#include "framework/Core.hpp"
#include "Weapon/Bullet.hpp"
#include "framework/World.hpp"
#include <random>

namespace SF
{

	BulletShooter::BulletShooter(Actor* InOwner, float InCooldownTime)
		: Shooter{ InOwner }
		, CooldownClock{}
		, CooldownTime{ InCooldownTime }
	{
		std::random_device Rd;  // Will be used to obtain a seed for the random number engine
		std::mt19937 gen(Rd()); // Standard mersenne_twister_engine seeded with rd()
		auto WindowSize = InOwner->GetWorld()->GetWindowSize();
		std::uniform_real_distribution<> Dis(WindowSize.x, WindowSize.x+200.f);
		Bullets.reserve(BulletPoolSize);
		// Spawn bullets in a pool
		if (InOwner)
		{
			for (size_t i = 0; i < BulletPoolSize; ++i)
			{
				std::weak_ptr<Bullet> BulletPtr = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
				if (auto Bullet = BulletPtr.lock())
				{
					sf::Vector2f BulletLocation{ static_cast<float>(Dis(gen)), InOwner->GetActorLocation().y };
					Bullet->SetActorLocation(BulletLocation);
					Bullet->SetActorRotation(InOwner->GetActorRotation());
					Bullet->SetActorVisible(false);
					//WriteLog(GLog, GLoglevel, "Bullet spawned at: " + std::to_string(Bullet->GetActorLocation().x) + ", " + std::to_string(Bullet->GetActorLocation().y));
					//WriteLog(GLog, GLoglevel, "Bullet rotation: " + std::to_string(Bullet->GetActorRotation()));
					Bullets.push_back(BulletPtr);
				}
				else
				{
					WriteLog(GLog, GLoglevel, "Failed to spawn bullet!");
				}
			}
		}
	}

	bool BulletShooter::IsOnCooldown() const
	{
		return CooldownClock.getElapsedTime().asSeconds() < CooldownTime;
	}

	void BulletShooter::Shoot_Impl()
	{
		// Implement the shooting logic here
		// For example, create a bullet and set its direction and speed
		CooldownClock.restart();
		//std::weak_ptr<Bullet> BulletPtr = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		//if (auto Bullet = BulletPtr.lock())
		//{
		//	Bullet->SetActorLocation(GetOwner()->GetActorLocation());
		//	Bullet->SetActorRotation(GetOwner()->GetActorRotation());
		//	WriteLog(GLog, GLoglevel, "Bullet spawned at: " + std::to_string(Bullet->GetActorLocation().x) + ", " + std::to_string(Bullet->GetActorLocation().y));
		//	WriteLog(GLog, GLoglevel, "Bullet rotation: " + std::to_string(Bullet->GetActorRotation()));
		//	Bullets.push_back(BulletPtr);
		//}
		//else
		//{
		//	WriteLog(GLog, GLoglevel, "Failed to spawn bullet!");
		//}
		std::vector<std::weak_ptr<Bullet>>::iterator IterBullet = Bullets.begin();
		for (; ; IterBullet++)
		{
			if (IterBullet != Bullets.end())
			{
				if (auto BulletPtr = IterBullet->lock())
				{
					if (!BulletPtr->IsActorVisible())
					{
						BulletPtr->SetActorLocation(GetOwner()->GetActorLocation());
						BulletPtr->SetActorRotation(GetOwner()->GetActorRotation());
						BulletPtr->SetActorVisible(true);
						break;
					}
				}
				IterBullet++;
			}
			if (IterBullet == Bullets.end())
			{
				std::weak_ptr<Bullet> BulletPtr = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
				if (auto Bullet = BulletPtr.lock())
				{
					Bullet->SetActorLocation(GetOwner()->GetActorLocation());
					Bullet->SetActorRotation(GetOwner()->GetActorRotation());
					//WriteLog(GLog, GLoglevel, "Bullet spawned at: " + std::to_string(Bullet->GetActorLocation().x) + ", " + std::to_string(Bullet->GetActorLocation().y));
					//WriteLog(GLog, GLoglevel, "Bullet rotation: " + std::to_string(Bullet->GetActorRotation()));
					Bullets.push_back(BulletPtr);
				}
				break;
			}
		}
		WriteLog(GLog, GLoglevel, "Shooting!");
	}
}