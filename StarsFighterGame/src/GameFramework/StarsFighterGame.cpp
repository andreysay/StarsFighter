#include "GameFramework/StarsFighterGame.hpp"
#include "framework/World.hpp"
#include "framework/GameBaseApp.hpp"
#include "framework/Core.hpp"
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
    std::weak_ptr<World> WeakNewWorld = LoadWorld<World>();
    if (auto NewWorld = WeakNewWorld.lock())
    {
        //const std::filesystem::path FilePath = "E:/sources/StarsFighter/StarsFighterGame/assets/SpaceShooterRedux/PNG/playerShip1_blue.png";
        const std::filesystem::path FilePath = GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png";
		auto SpaceShip = NewWorld->SpawnActor<Actor>();
		if (auto SpaceShipPtr = SpaceShip.lock())
		{
			SpaceShipPtr->SetTexture(FilePath);
			SpaceShipPtr->SetName("SpaceShip");
		}
	}
	else
	{
		WriteLog(GLog, GLoglevel, "Failed to load world");
    }
}

}
