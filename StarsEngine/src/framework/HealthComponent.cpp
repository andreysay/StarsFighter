/*
*  HealthComponent.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "framework/HealthComponent.hpp"
#include "framework/Core.hpp"

namespace SF
{
	//--------------------------------------------------------------------------------------------------------
	HealthComponent::HealthComponent(float InCurrentHealth, float InMaxHealth)
		: CurrentHealth{ InCurrentHealth }
		, MaxHealth{ InMaxHealth }
	{
	}
	//--------------------------------------------------------------------------------------------------------
	void HealthComponent::ChangeCurrentHealth(float DeltaHealth)
	{
		if (bIsDead)
		{
			return;
		}
		if (DeltaHealth < 0.f)
		{
			TakenDamage(DeltaHealth * DamageMultiplier);
			if (CurrentHealth <= 0.f)
			{
				Dead();
			}
		}
		else
		{
			Heal(DeltaHealth);
		}
		OnHealthChanged.Broadcast(DeltaHealth);
	}
	//--------------------------------------------------------------------------------------------------------
	void HealthComponent::SetInvincibility(float InInvincibilityTime)
	{
		bIsInvincible = true;
		InvincibilityTime = InInvincibilityTime;
		InvincibilityTimer = 0.f;
	}
	//--------------------------------------------------------------------------------------------------------
	void HealthComponent::SetCurrentHealth(float InCurrentHealth)
	{
		WriteLog(GLog, GLoglevel, "Current health: " + std::to_string(InCurrentHealth));
		CurrentHealth = InCurrentHealth;
	}
	//--------------------------------------------------------------------------------------------------------
	void HealthComponent::TakenDamage(float DamageAmount)
	{
		WriteLog(GLog, GLoglevel, "Taking damage: " + std::to_string(DamageAmount));
		bIsTakingDamage = true;
		bIsHealing = false;
		SetCurrentHealth(CurrentHealth + DamageAmount);
		OnTakenDamage.Broadcast(DamageAmount);
	}
	//--------------------------------------------------------------------------------------------------------
	void HealthComponent::Dead()
	{
		SetCurrentHealth(0.f);
		SetIsDead(true);
		OnDead.Broadcast();
		WriteLog(GLog, GLoglevel, "HealthComponent is dead!");
	}
	//--------------------------------------------------------------------------------------------------------
	void HealthComponent::Heal(float HealAmount)
	{
		WriteLog(GLog, GLoglevel, "Healing: " + std::to_string(HealAmount));
		bIsTakingDamage = false;
		bIsHealing = true;
		SetCurrentHealth(CurrentHealth + HealAmount * HealingMultiplier);
		if (CurrentHealth > MaxHealth)
		{
			SetCurrentHealth(MaxHealth);
		}
	}
} // namespace SF
