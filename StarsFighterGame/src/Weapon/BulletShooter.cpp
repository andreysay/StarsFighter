/*
*  BulletShooter.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "Weapon/BulletShooter.hpp"
#include "framework/Core.hpp"
#include "Weapon/Bullet.hpp"
#include "framework/World.hpp"
#include "Player/PlayerSpaceship.hpp"

namespace SF
{
	const float BulletDefaultSpeed{ 800.f }; // Default bullet speed
	const float PlayerBulletSpeed{ -800.f }; // Default bullet speed
	//--------------------------------------------------------------------------------------------------------
	BulletShooter::BulletShooter(Actor* InOwner, float InCooldownTime)
		: Shooter{ InOwner }
		, CooldownClock{}
		, CooldownTime{ InCooldownTime }
	{
		Bullets.reserve(BulletPoolSize);
		// Spawn bullets in a pool
		if (InOwner)
		{
			for (size_t i = 0; i < BulletPoolSize; ++i)
			{
				std::weak_ptr<Bullet> BulletPtr = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
				if (auto Bullet = BulletPtr.lock())
				{
					Bullet->SetActorLocation(Bullet->GetBulletRandomPosition());
					Bullet->SetActorRotation(InOwner->GetActorRotation());
					Bullet->SetTeamId(GetOwner()->GetTeamId());
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
		CooldownClock.restart();
		std::vector<std::weak_ptr<Bullet>>::iterator IterBullet = Bullets.begin();
		for (; ; )
		{
			// Find a bullet in the pool that is not visible
			if (IterBullet != Bullets.end())
			{
				if (auto BulletPtr = IterBullet->lock())
				{
					if (!BulletPtr->IsActorVisible())
					{
						BulletPtr->SetActorLocation(GetOwner()->GetActorLocation());
						BulletPtr->SetActorRotation(GetOwner()->GetActorRotation());
						//TODO: Refactor this logic
						if (GetOwner()->GetTeamId() == PlayerSpaceship::PlayerSpaceshipDefaultTeamId)
						{
							BulletPtr->SetSpeed(PlayerBulletSpeed); // Set bullet speed
						}
						else
						{
							BulletPtr->SetSpeed(BulletDefaultSpeed);
						}
						
						BulletPtr->SetActorVisible(true);
						BulletPtr->SetEnablePhysics(true);
						break;
					}
				}
				IterBullet++;
			}
			// If we reach the pool end, spawn a new one
			if (IterBullet == Bullets.end())
			{
				std::weak_ptr<Bullet> BulletWeakPtr = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
				if (auto BulletPtr = BulletWeakPtr.lock())
				{
					BulletPtr->SetActorLocation(GetOwner()->GetActorLocation());
					BulletPtr->SetActorRotation(GetOwner()->GetActorRotation());
					//TODO: Refactor this logic 
					if (GetOwner()->GetTeamId() == PlayerSpaceship::PlayerSpaceshipDefaultTeamId)
					{
						BulletPtr->SetSpeed(PlayerBulletSpeed); // Set bullet speed
					}
					else
					{
						BulletPtr->SetSpeed(BulletDefaultSpeed);
						BulletPtr->SetEnablePhysics(true);
					}
					//WriteLog(GLog, GLoglevel, "Bullet spawned at: " + std::to_string(Bullet->GetActorLocation().x) + ", " + std::to_string(Bullet->GetActorLocation().y));
					//WriteLog(GLog, GLoglevel, "Bullet rotation: " + std::to_string(Bullet->GetActorRotation()));
					Bullets.push_back(BulletPtr);
				}
				break;
			}
		}
		WriteLog(GLog, GLoglevel, "Shooting!");
	}
}// End of namespace SF