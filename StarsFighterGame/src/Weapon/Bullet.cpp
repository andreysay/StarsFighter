#include "Weapon/Bullet.hpp"
#include "framework/Core.hpp"
#include "Spaceship/Spaceship.hpp"

namespace SF
{
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
	void Bullet::Tick(float DeltaTime)
	{
		Actor::Tick(DeltaTime);
		Move(DeltaTime);
		if (IsActorOutOfScreen())
		{
			SetActorVisible(false);
			//SetSpeed(0.f); // Stop moving if out of screen
		}
	}
	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}
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
		}
		//else
		//{
		//	WriteLog(GLog, GLoglevel, "Bullet overlap with non-hostile actor: " + OtherActor->GetName());
		//}
	}
	void Bullet::OnActorEndOverlap(Actor* OtherActor)
	{
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