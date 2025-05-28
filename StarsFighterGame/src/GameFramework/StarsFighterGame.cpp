/*
*  StarsFighterGame.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "GameFramework/StarsFighterGame.hpp"
#include "framework/World.hpp"
#include "framework/GameBaseApp.hpp"
#include "framework/Core.hpp"
#include "Spaceship/Spaceship.hpp"
#include "framework/AssetManager.hpp"
#include "Player/PlayerSpaceship.hpp"
#include "Config.h"



std::unique_ptr<SF::GameBaseApp> GetGame()
{
    return std::make_unique<SF::StarsFigherGame>();
}

namespace SF
{
	// Constants for the game window size and title
	const Vector2u WindowSize{ 750, 1334 };
	const std::string_view GameTitle{ "StarsFigher" };
	const float Velocity{ -200.f }; // Default spaceship velocity
	const Vector2f PlayerStartPosition = { WindowSize.x * 0.5f, WindowSize.y * 0.8f };
	const Vector2f ActorStartPosition = { WindowSize.x * 0.5f, WindowSize.y * 0.1f };
	//--------------------------------------------------------------------------------------------------------
    StarsFigherGame::StarsFigherGame()
		: GameBaseApp{ WindowSize, std::string{GameTitle}, sf::Style::Titlebar | sf::Style::Close }
	{
		// Set the asset root directory
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		std::weak_ptr<World> WeakNewWorld = LoadWorld<World>();
		if (auto NewWorld = WeakNewWorld.lock())
		{
			auto PlayerOwnSpaceShip = NewWorld->SpawnActor<PlayerSpaceship>(PlayerSpaceshipTexturePath);
			if (auto SpaceShipPtr = PlayerOwnSpaceShip.lock())
			{
				SpaceShipPtr->SetActorLocation(PlayerStartPosition);
				SpaceShipPtr->SetVelocity(sf::Vector2f(0.f, Velocity));
				SpaceShipPtr->SetTeamId(PlayerSpaceship::PlayerSpaceshipDefaultTeamId);
			}

			const std::filesystem::path FilePath = "SpaceShooterRedux/PNG/playerShip3_red.png";
			auto SpaceShip = NewWorld->SpawnActor<Spaceship>(FilePath.c_str());
			if (auto SpaceShipPtr = SpaceShip.lock())
			{
				SpaceShipPtr->SetActorLocation(ActorStartPosition);
				SpaceShipPtr->SetTeamId(3);
			}

		}
		else
		{
			WriteLog(GLog, GLoglevel, "Failed to load world");
		}
	}

}
