/*
*  Bullet.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "Weapon/Bullet.hpp"
#include "framework/Core.hpp"
#include "Spaceship/Spaceship.hpp"
#include "framework/World.hpp"
#include <random>

namespace SF
{
	static const float BulletOffScreenOffset{ 200.f }; // Offset to consider bullet off-screen
	//--------------------------------------------------------------------------------------------------------
	Bullet::Bullet(World* InWorld, Actor* InOwner, const std::filesystem::path& FilePath, float Speed, float Damage, const std::string& InName)
		: Actor{ InWorld, FilePath, InName }
		, Owner{ InOwner }
		, Speed{ Speed }
		, Damage{ Damage }
	{
		SetTexture(FilePath);
		//SetTeamId(InOwner->GetTeamId());
		SetTeamId(2);
	}
	//--------------------------------------------------------------------------------------------------------
	void Bullet::Tick(float DeltaTime)
	{
		Actor::Tick(DeltaTime);
		Move(DeltaTime);
		if (IsActorOutOfScreen())
		{
			SetActorVisible(false);
			SetSpeed(0.f); // Stop moving if bullet is out of screen
		}
	}
	//-----------------------------------------------------------------------------------
	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}
	//-----------------------------------------------------------------------------------
	void Bullet::OnActorBeginOverlap(Actor* OtherActor)
	{
		if (IsHostileTeam(OtherActor))
		{
			WriteLog(GLog, GLoglevel, "Bullet hit actor: " + OtherActor->GetName());
			// Apply damage to the other actor
			if (auto OtherSpaceship = dynamic_cast<Spaceship*>(OtherActor))
			{
				OtherSpaceship->ApplyDamage(GetDamage());
			}
			SetActorVisible(false); // Hide bullet after hit
			SetSpeed(0.f); // Stop moving after hit
			SetActorLocation(GetBulletRandomPosition()); // Reset bullet position to a random off-screen position
		}
	}
	//-----------------------------------------------------------------------------------
	void Bullet::OnActorEndOverlap(Actor* OtherActor)
	{
	}
	//-----------------------------------------------------------------------------------
	void Bullet::SetSpeed(float InSpeed)
	{
		Speed = InSpeed;
	}
	//-----------------------------------------------------------------------------------
	void Bullet::SetDamage(float InDamage)
	{
		Damage = InDamage;
	}
	//-----------------------------------------------------------------------------------
	void Bullet::Move(float DeltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * Speed * DeltaTime);
		//std::string Message = "Bullet is moving at speed: " + std::to_string(Speed) + " direction: (" + std::to_string(GetActorForwardDirection().x) + ", " + std::to_string(GetActorForwardDirection().y) + ")";
		//WriteLog(GLog, GLoglevel, Message);
	}
	//-----------------------------------------------------------------------------------
	sf::Vector2f Bullet::GetBulletRandomPosition() const
	{
		if (Owner)
		{
			static std::random_device Rd;  // Will be used to obtain a seed for the random number engine
			static std::mt19937 gen(Rd()); // Standard mersenne_twister_engine seeded with rd()
			auto WindowSize = Owner->GetWorld()->GetWindowSize();
			std::uniform_real_distribution<> Dis(WindowSize.x, WindowSize.x + BulletOffScreenOffset);
			return { static_cast<float>(Dis(gen)), Owner->GetActorLocation().y };
		}
	}
}