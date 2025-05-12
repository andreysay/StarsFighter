#include "GameFramework/StarsFighterGame.hpp"

namespace StarsFigher
{

std::unique_ptr<StarsFigher::GameBaseApp> GetGame()
{
    return std::make_unique<StarsFigher::GameBaseApp>();
}

}
