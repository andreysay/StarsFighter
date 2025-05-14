#include "GameFramework/StarsFighterGame.hpp"
#include "framework/World.hpp"
#include "framework/GameBaseApp.hpp"
#include <memory>



std::unique_ptr<StarsFigher::GameBaseApp> GetGame()
{
    return std::make_unique<StarsFigher::StarsFigherGame>();
}

namespace StarsFigher
{
StarsFigherGame::StarsFigherGame()
{
    LoadWorld<World>();
}

}
