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
#include "framework/TimerHandler.hpp"

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
		auto PlayerOwnSpaceShip = SpawnActor<PlayerSpaceship>(PlayerSpaceshipTexturePath);
		if (auto SpaceShipPtr = PlayerOwnSpaceShip.lock())
		{
			SpaceShipPtr->SetActorLocation(PlayerStartPosition);
			SpaceShipPtr->SetVelocity(sf::Vector2f(0.f, Velocity));
		}

		auto VanguardShip = SpawnActor<Vanguard>();
		if (auto VanguardShipPtr = VanguardShip.lock())
		{
			VanguardShipPtr->SetActorLocation(ActorStartPosition);
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	void Level_1::Tick(float deltaTime)
	{
		
	}
	void Level_1::BeginPlay()
	{
		Key = TimerHandler::Get().RegisterTimer(GetWeakPtr(), &Level_1::TimerCallbackTest, 3.f, true);
	}
	void Level_1::TimerCallbackTest()
	{
		//TimerHandler::Get().ExpireTimer(Key);
		WriteLog(GLog, GLoglevel, "TimerCallbackTest called after 3 seconds in Level_1");
	}
} // namespace SF