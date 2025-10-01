/*
*  Spaceship.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "Spaceship/Spaceship.hpp"
#include "framework/MathUtility.hpp"
#include "VFX/Explosion.hpp"

namespace SF
{
	Spaceship::Spaceship(World* InWorld, const std::filesystem::path& FilePath, bool IsAnimated, const std::string& InName)
		: Actor{ InWorld, FilePath, IsAnimated, InName }
		, HealthComponent{ 100.f, 100.f }
	{
	}
	void Spaceship::Tick(float DeltaTime)
	{
		Actor::Tick(DeltaTime);
		AddActorLocationOffset(GetVelocity() * DeltaTime);
		UpdateBlink(DeltaTime);
		//WriteLog(GLog, Helpers::LogLevel::Info, "Spaceship is ticking at framerate: " + std::to_string(1.f / DeltaTime));
	}
	void Spaceship::Shoot()
	{
	}
	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
		HealthComponent.OnHealthChanged.BindDelegate(GetWeakPtr(), &Spaceship::OnHeathChanged);
		HealthComponent.OnTakenDamage.BindDelegate(GetWeakPtr(), &Spaceship::OnTakenDamage);
		HealthComponent.OnDead.BindDelegate(GetWeakPtr(), &Spaceship::OnDead);
	}
	void Spaceship::ApplyDamage(float DamageAmount)
	{
		HealthComponent.ChangeCurrentHealth(DamageAmount);
		WriteLog(GLog, GLoglevel, "Current health: " + std::to_string(HealthComponent.GetCurrentHealth()));
	}
	void Spaceship::SetVelocity(const sf::Vector2f& InVelocity)
	{
		SpaceshipVelocity = InVelocity;
	}
	void Spaceship::OnHeathChanged(float DeltaHealth)
	{
		/* Default implementation does nothing */
		WriteLog(GLog, GLoglevel, "Spaceship health changed by: " + std::to_string(DeltaHealth));
	}
	void Spaceship::OnTakenDamage(float DamageAmount)
	{
		Blink();
		WriteLog(GLog, GLoglevel, "Spaceship took damage: " + std::to_string(DamageAmount));
	}
	void Spaceship::OnDead()
	{
		Explosion::SpawnExplosion(GetWorld(), GetActorLocation(), 20);
		auto Message = GetName() + " is dead! ( " + std::to_string(GetActorLocation().x) + " " + std::to_string(GetActorLocation().y) + " )";
		WriteLog(GLog, GLoglevel, Message);
		Destroy();
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	void Spaceship::SetHealth(float InCurrentHealth, float InMaxHealth)
	{
		HealthComponent.SetMaxHealth(InMaxHealth);
		HealthComponent.ChangeCurrentHealth(InCurrentHealth);
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	void Spaceship::Blink()
	{
		if (BlinkTime == 0.f)
		{
			BlinkTime = BlinkDuration;
		}
	}
	void Spaceship::UpdateBlink(float DeltaTime)
	{
		if (BlinkTime > 0.f)
		{
			BlinkTime -= DeltaTime;
			BlinkTime = BlinkTime > 0.f ? BlinkTime : 0.f;
			GetActorSprite().setColor(SF::Math::LerpColor(sf::Color::White, BlinkColorOffset, BlinkTime));
		}
	}
}


