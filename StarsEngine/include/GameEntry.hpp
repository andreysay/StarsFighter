#pragma once
#include <memory>


namespace SF
{

    class GameBaseApp;

}

extern std::unique_ptr<SF::GameBaseApp> GetGame();

