/*
*  HealthComponent.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include "framework/Delegate.hpp"

namespace SF
{
	//! HealthComponent class is responsible for managing the health of an actor.
	class HealthComponent
	{
	public:
		HealthComponent() = default;
		//! Constructor for HealthComponent, initializes current and maximum health.
		HealthComponent(float InCurrentHealth, float InMaxHealth);
		HealthComponent(const HealthComponent&) = delete;
		HealthComponent& operator=(const HealthComponent&) = delete;
		HealthComponent(HealthComponent&&) = delete;
		HealthComponent& operator=(HealthComponent&&) = delete;
		~HealthComponent() = default;


		float GetMaxHealth() const { return MaxHealth; }
		float GetCurrentHealth() const { return CurrentHealth; }
		void ChangeCurrentHealth(float DeltaHealth);
		void SetDamageMultiplier(float InDamageMultiplier) { DamageMultiplier = InDamageMultiplier; }
		void SetHealingMultiplier(float InHealingMultiplier) { HealingMultiplier = InHealingMultiplier; }
		void SetDamageResistance(float InDamageResistance) { DamageResistance = InDamageResistance; }
		void SetHealingResistance(float InHealingResistance) { HealingResistance = InHealingResistance; }
		float GetDamageMultiplier() const { return DamageMultiplier; }
		float GetHealingMultiplier() const { return HealingMultiplier; }
		float GetDamageResistance() const { return DamageResistance; }
		bool IsDead() const { return bIsDead; }
		bool IsInvincible() const { return bIsInvincible; }
		bool IsHealing() const { return bIsHealing; }
		bool IsTakingDamage() const { return bIsTakingDamage; }
		bool IsInvincibleActive() const { return bIsInvincibleActive; }
		bool IsHealingActive() const { return bIsHealingActive; }
		void SetInvincibility(float InInvincibilityTime);
		void SetCurrentHealth(float InCurrentHealth);
		void SetMaxHealth(float InMaxHealth) { MaxHealth = InMaxHealth; }

		//! Delegate
		Delegate<> OnDead;
		Delegate<float> OnHealthChanged;
		Delegate<float> OnTakenDamage;

	protected:
		void SetIsDead(bool bInIsDead) { bIsDead = bInIsDead; }

		void TakenDamage(float DamageAmount);
		void Dead();
		void Heal(float HealAmount);

	private:
		float CurrentHealth{ 0.f };
		float MaxHealth{ 0.f };
		bool bIsDead{ false };
		bool bIsInvincible{ false };
		float InvincibilityTime{ 0.f };
		float InvincibilityTimer{ 0.f };
		float DamageMultiplier{ 1.f };
		float HealingMultiplier{ 1.f };
		float DamageResistance{ 0.f };
		float HealingResistance{ 0.f };
		bool bIsHealing{ false };
		bool bIsTakingDamage{ false };
		bool bIsInvincibleActive{ false };
		bool bIsHealingActive{ false };
	};
}