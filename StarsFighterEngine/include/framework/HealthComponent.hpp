#pragma once

namespace SF
{
	class HealthComponent
	{
	public:
		HealthComponent(float InCurrentHealth, float InMaxHealth);
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

	protected:
		void SetCurrentHealth(float InCurrentHealth);
		void SetMaxHealth(float InMaxHealth) { MaxHealth = InMaxHealth; }
		void SetIsDead(bool bInIsDead) { bIsDead = bInIsDead; }

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