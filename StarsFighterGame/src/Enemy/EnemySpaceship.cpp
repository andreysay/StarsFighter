/*
*  EnemySpaceship.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 30.05.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "Enemy/EnemySpaceship.hpp"
//----------------------------------------------------------------------------------------------------------------------------------------------
SF::EnemySpaceship::EnemySpaceship(World* InWorld, const std::filesystem::path& FilePath, float InCollisionDamage, const std::string& InName)
	: Spaceship{ InWorld, FilePath, InName }
	, CollisionDamage{ InCollisionDamage }
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------
void SF::EnemySpaceship::Tick(float DeltaTime)
{
	Spaceship::Tick(DeltaTime);
	if (IsActorOutOfScreen(GetActorGlobalBounds().size.x))
	{
		// If the enemy spaceship is out of screen, hide it
		SetActorVisible(false);
		SetSpaceshipVelocity(sf::Vector2f{ 0.f, 0.f }); // Stop moving if out of screen
	}
	// Additional logic for enemy spaceship can be added here
	//WriteLog(GLog, GLoglevel, "EnemySpaceship is ticking at framerate: " + std::to_string(1.f / DeltaTime));
}
//----------------------------------------------------------------------------------------------------------------------------------------------
void SF::EnemySpaceship::OnActorBeginOverlap(Actor* OtherActor)
{
	Spaceship::OnActorBeginOverlap(OtherActor);
	if (IsHostileTeam(OtherActor))
	{
		if (auto OtherSpaceship = dynamic_cast<Spaceship*>(OtherActor))
		{
			// Apply collision damage to the other spaceship
			OtherSpaceship->ApplyDamage(CollisionDamage);
			WriteLog(GLog, GLoglevel, "EnemySpaceship collided with: " + OtherActor->GetName() + ", applying damage: " + std::to_string(CollisionDamage));
		}
	}
}
