/*
*  Particle.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 29.05.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "VFX/Particle.hpp"
#include "framework/MathUtility.hpp"

SF::Particle::Particle(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName)
	: Actor(InWorld, FilePath, InName)
{
}

void SF::Particle::Tick(float DeltaTime)
{
	Actor::Tick(DeltaTime);

	Move(DeltaTime);
	FadeOut(DeltaTime);

	if (Timer.getElapsedTime().asSeconds() >= Lifetime)
	{
		Destroy();
	}
}

void SF::Particle::RandomVelocity(float MinSpeed, float MaxSpeed)
{
	Velocity = SF::Math::RandomUnitVector() * SF::Math::RandomNumber<float>(MinSpeed, MaxSpeed);
}

void SF::Particle::RandomSize(float MinSize, float MaxSize)
{
	float RandomScale = SF::Math::RandomNumber<float>(MinSize, MaxSize);
	GetActorSprite().setScale({ RandomScale, RandomScale }); // Set random size for the particle
}

void SF::Particle::RandomLifeTime(float MinLifetime, float MaxLifetime)
{
	Lifetime = SF::Math::RandomNumber<float>(MinLifetime, MaxLifetime);
}

void SF::Particle::Move(float DeltaTime)
{
	AddActorLocationOffset(Velocity * DeltaTime);
}

void SF::Particle::FadeOut(float DeltaTime)
{
	float ElapsedTime = Timer.getElapsedTime().asSeconds();
	GetActorSprite().setColor(
			SF::Math::LerpColor(
			GetActorSprite().getColor(),
			sf::Color(255, 255, 255, 0), // Fade to transparent
			ElapsedTime / Lifetime
		)
	);

	GetActorSprite().setScale(
		SF::Math::LerpVector(
			GetActorSprite().getScale(),
			sf::Vector2f(0.f, 0.f), // Scale down to zero
			ElapsedTime / Lifetime
		)
	);
}
