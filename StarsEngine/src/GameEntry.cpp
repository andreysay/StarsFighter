/*
*  GameEntry.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "GameEntry.hpp"

#include "framework/GameBaseApp.hpp"
#include "framework/Core.hpp"

using namespace Helpers;

// Entry point for the game application
int main(int argc, char *argv[])
{
    GLog.SetLevel(GLoglevel);
    WriteLog(GLog, GLoglevel, "Game is starting up");
    std::unique_ptr<SF::GameBaseApp> Game = GetGame();
    Game->RunGame();
    WriteLog(GLog, GLoglevel, "Game finished");
}
