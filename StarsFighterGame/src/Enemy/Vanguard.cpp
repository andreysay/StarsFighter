/*
*  Vanguard.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 30.05.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "Enemy/Vanguard.hpp"
#include "Weapon/BulletShooter.hpp"

SF::Vanguard::Vanguard(World* InWorld, const std::filesystem::path& FilePath, float InCollisionDamage, const std::string& InName)
	: EnemySpaceship{ InWorld, FilePath, InCollisionDamage, false, InName }
{
	// Set the team id for the Vanguard enemy spaceship
	SetTeamId(EnemySpaceshipDefaultTeamId);
	BulletShooterPtr = std::make_unique<BulletShooter>(this, 1.f); // Initialize the BooletShooter with a cooldown time
	//SetActorRotation(180.f); // Set the initial rotation of the enemy spaceship to face down
	// Set the initial velocity of the enemy spaceship
	SetSpaceshipVelocity(sf::Vector2f{ 0.f, 100.f }); // Set the initial velocity to move downwards
	std::string LogMessage = "EnemySpaceship created with ID: " + std::to_string(GetTeamId());
	WriteLog(GLog, GLoglevel, LogMessage);
}

void SF::Vanguard::Tick(float DeltaTime)
{
	EnemySpaceship::Tick(DeltaTime);
	if (IsActorOutOfScreen(GetActorGlobalBounds().size.x))
	{
		return;
	}

	Shoot(); // Call the Shoot method to handle shooting logic
}

void SF::Vanguard::Shoot()
{
	if (BulletShooterPtr && BulletShooterPtr->IsOnCooldown() == false)
	{
		BulletShooterPtr->Shoot();
	}
}
