#pragma once

#include "framework/Actor.hpp"

namespace SF
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* InWorld, Actor* InOwner, const std::filesystem::path& FilePath, float Speed = -800.f, float Damage = 10.f, const std::string& InName = "Bullet");
		
		virtual void Tick(float DeltaTime) override;
		virtual void BeginPlay() override;


		void SetSpeed(float InSpeed);
		void SetDamage(float InDamage);
		float GetSpeed() const { return Speed; }

	private:
		void Move(float DeltaTime);

	private:
		Actor* Owner{ nullptr };
		float Speed{ 0.f };
		float Damage{ 0.f };
	};
}