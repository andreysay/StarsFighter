/*
*  Level_1.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 02.06.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "Levels/Level_1.hpp"
#include "framework/World.hpp"
#include "framework/GameBaseApp.hpp"
#include "framework/Core.hpp"
#include "Spaceship/Spaceship.hpp"
#include "Player/PlayerSpaceship.hpp"
#include "Enemy/Vanguard.hpp"
#include "framework/TimersHandler.hpp"
#include "gameplay/GameStage.hpp"
#include "Enemy/VanguardStage.hpp"

namespace SF
{
	const float Velocity{ -200.f }; // Default spaceship velocity

	Level_1::Level_1(const GameBaseApp& OwningApp)
		: World{OwningApp}
	{
		//if (auto NewWorld = WeakNewWorld.lock())
		//{
		auto WindowSize = OwningApp.GetWindowSize();
		const Vector2f PlayerStartPosition = { WindowSize.x * 0.5f, WindowSize.y * 0.8f };
		const Vector2f ActorStartPosition = { WindowSize.x * 0.5f, WindowSize.y * 0.1f };
		auto PlayerOwnSpaceShip = SpawnActor<PlayerSpaceship>(PlayerSpaceshipTexturePath, true);
		if (auto SpaceShipPtr = PlayerOwnSpaceShip.lock())
		{
			SpaceShipPtr->SetActorLocation(PlayerStartPosition);
			SpaceShipPtr->SetVelocity(sf::Vector2f(0.f, Velocity));
			SpaceShipPtr->SetHealth(1000.f, 1000.f);
			SpaceShipPtr->SetShooterLocation();
		}

		//auto VanguardShip = SpawnActor<Vanguard>();
		//if (auto VanguardShipPtr = VanguardShip.lock())
		//{
		//	VanguardShipPtr->SetActorLocation(ActorStartPosition);
		//}
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	void Level_1::Tick(float deltaTime)
	{
		
	}
	void Level_1::BeginPlay()
	{

	}
	void Level_1::InitGameStages()
	{
		AddStage(std::shared_ptr<VanguardStage>{new VanguardStage{ this }});
	}
} // namespace SF