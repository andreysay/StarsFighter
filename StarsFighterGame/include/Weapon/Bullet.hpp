#pragma once

#include "framework/Actor.hpp"

namespace SF
{
	class Bullet : public Actor
	{
		static const uint32_t BulletDefaultTeamId = 1; // Default team id for the bullet, used for identification of a groups objects in the game
	public:
		Bullet(World* InWorld, Actor* InOwner, const std::filesystem::path& FilePath, float Speed = -800.f, float Damage = -10.f, const std::string& InName = "Bullet");
		
		virtual void Tick(float DeltaTime) override;
		virtual void BeginPlay() override;
		virtual void OnActorBeginOverlap(Actor* OtherActor) override;
		virtual void OnActorEndOverlap(Actor* OtherActor) override;


		void SetSpeed(float InSpeed);
		float GetSpeed() const { return Speed; }
		void SetDamage(float InDamage);
		float GetDamage() const { return Damage; }

	private:
		void Move(float DeltaTime);

	private:
		Actor* Owner{ nullptr };
		float Speed{ 0.f };
		float Damage{ 0.f };
	};
}