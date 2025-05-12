#pragma once
#include <memory>


namespace StarsFigher
{

    class GameBaseApp;

}

extern std::unique_ptr<StarsFigher::GameBaseApp> GetGame();

