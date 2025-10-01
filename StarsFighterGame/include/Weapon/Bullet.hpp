/*
*  Bullet.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once

#include "framework/Actor.hpp"

namespace SF
{
	//! Bullet class represents a projectile fired by the spaceship
	class Bullet : public Actor
	{
		//! Default team id for the bullet, used for identification of a groups objects in the game
		static const uint32_t BulletDefaultTeamId = 1; 
	public:
		Bullet(World* InWorld, Actor* InOwner, const std::filesystem::path& FilePath, float Speed = 0.f, float Damage = -10.f, bool IsAnimated = false, const std::string& InName = "Bullet");
		
		virtual void Tick(float DeltaTime) override;
		virtual void BeginPlay() override;
		virtual void OnActorBeginOverlap(Actor* OtherActor) override;
		virtual void OnActorEndOverlap(Actor* OtherActor) override;
		virtual bool IsNotBullet() const override { return false; }

		//! Set the speed of the bullet
		void SetSpeed(float InSpeed);
		//! Get the speed of the bullet
		float GetSpeed() const { return Speed; }
		//! Set the damage dealt by the bullet
		void SetDamage(float InDamage);
		//! Get the damage dealt by the bullet
		float GetDamage() const { return Damage; }
		//! Get a bullet's random position without the screen bounds
		sf::Vector2f GetBulletRandomPosition() const;

	private:
		//! Move the bullet based on its speed and delta time
		void Move(float DeltaTime);

	private:
		Actor* Owner{ nullptr };
		float Speed{ 0.f };
		float Damage{ 0.f };
	};
}