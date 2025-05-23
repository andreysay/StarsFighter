#include "framework/HealthComponent.hpp"
#include "framework/Core.hpp"

namespace SF
{
	HealthComponent::HealthComponent(float InCurrentHealth, float InMaxHealth)
		: CurrentHealth{ InCurrentHealth }
		, MaxHealth{ InMaxHealth }
	{
	}
	void HealthComponent::ChangeCurrentHealth(float DeltaHealth)
	{
		if (bIsDead)
		{
			return;
		}
		if (DeltaHealth < 0.f)
		{
			WriteLog(GLog, GLoglevel, "Taking damage: " + std::to_string(DeltaHealth));
			bIsTakingDamage = true;
			bIsHealing = false;
			SetCurrentHealth(CurrentHealth + DeltaHealth * DamageMultiplier);
			if (CurrentHealth <= 0.f)
			{
				SetCurrentHealth(0.f);
				SetIsDead(true);
			}
		}
		else
		{
			WriteLog(GLog, GLoglevel, "Healing: " + std::to_string(DeltaHealth));
			bIsTakingDamage = false;
			bIsHealing = true;
			SetCurrentHealth(CurrentHealth + DeltaHealth * HealingMultiplier);
			if (CurrentHealth > MaxHealth)
			{
				SetCurrentHealth(MaxHealth);
			}
		}
	}
	void HealthComponent::SetInvincibility(float InInvincibilityTime)
	{
		bIsInvincible = true;
		InvincibilityTime = InInvincibilityTime;
		InvincibilityTimer = 0.f;
	}
	void HealthComponent::SetCurrentHealth(float InCurrentHealth)
	{
		WriteLog(GLog, GLoglevel, "Current health: " + std::to_string(InCurrentHealth));
		CurrentHealth = InCurrentHealth;
	}
}
