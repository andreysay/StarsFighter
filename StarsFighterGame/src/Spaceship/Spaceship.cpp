#include "Spaceship/Spaceship.hpp"

namespace SF
{
	Spaceship::Spaceship(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName)
		: Actor{ InWorld, FilePath, InName }
		, HealthComponent{ 100.f, 100.f }
	{
	}
	void Spaceship::Tick(float DeltaTime)
	{
		Actor::Tick(DeltaTime);
		AddActorLocationOffset(GetVelocity() * DeltaTime);
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
		/* Default implementation does nothing */
		WriteLog(GLog, GLoglevel, "Spaceship took damage: " + std::to_string(DamageAmount));
	}
	void Spaceship::OnDead()
	{
		WriteLog(GLog, GLoglevel, "Spaceship is dead!");
		Destroy();
	}
}


