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
    StarsFigherGame::StarsFigherGame()
		: GameBaseApp{ Vector2u{600, 980}, std::string{"Stars Fighter"}, sf::Style::Titlebar | sf::Style::Close }
	{
		// Set the asset root directory
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		std::weak_ptr<World> WeakNewWorld = LoadWorld<World>();
		if (auto NewWorld = WeakNewWorld.lock())
		{
			//const std::filesystem::path FilePath = "E:/sources/StarsFighter/StarsFighterGame/assets/SpaceShooterRedux/PNG/playerShip1_blue.png";
			//const std::filesystem::path FilePath = "SpaceShooterRedux/PNG/playerShip1_blue.png";
			auto PlayerOwnSpaceShip = NewWorld->SpawnActor<PlayerSpaceship>(PlayerSpaceshipTexturePath);
			if (auto SpaceShipPtr = PlayerOwnSpaceShip.lock())
			{
				//SpaceShipPtr->SetTexture(PlayerSpaceshipTexturePath);
				SpaceShipPtr->SetActorLocation({ 300.f, 480.f });
				SpaceShipPtr->SetVelocity(sf::Vector2f(0.f, -200.f));
			}

			const std::filesystem::path FilePath = "SpaceShooterRedux/PNG/playerShip3_red.png";
			auto SpaceShip = NewWorld->SpawnActor<Spaceship>(FilePath.c_str());
			if (auto SpaceShipPtr = SpaceShip.lock())
			{
				//SpaceShipPtr->SetTexture(FilePath);
				SpaceShipPtr->SetActorLocation({ 300.f, 50.f });
			}

		}
		else
		{
			WriteLog(GLog, GLoglevel, "Failed to load world");
		}
	}

}
