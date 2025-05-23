#include "Weapon/Bullet.hpp"
#include "framework/Core.hpp"

namespace SF
{
	Bullet::Bullet(World* InWorld, Actor* InOwner, const std::filesystem::path& FilePath, float Speed, float Damage, const std::string& InName)
		: Actor{ InWorld, FilePath, InName }
		, Owner{ InOwner }
		, Speed{ Speed }
		, Damage{ Damage }
	{
		SetTexture(FilePath);
	}
	void Bullet::Tick(float DeltaTime)
	{
		Actor::Tick(DeltaTime);
		Move(DeltaTime);
		if (IsActorOutOfScreen())
		{
			SetActorVisible(false);
		}
	}
	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		//SetEnablePhysics(true);
	}
	void Bullet::SetSpeed(float InSpeed)
	{
		Speed = InSpeed;
	}
	void Bullet::SetDamage(float InDamage)
	{
		Damage = InDamage;
	}
	void Bullet::Move(float DeltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * Speed * DeltaTime);
		//std::string Message = "Bullet is moving at speed: " + std::to_string(Speed) + " direction: (" + std::to_string(GetActorForwardDirection().x) + ", " + std::to_string(GetActorForwardDirection().y) + ")";
		//WriteLog(GLog, GLoglevel, Message);
	}
}