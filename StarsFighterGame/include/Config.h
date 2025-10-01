/*
*  Config.h
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include <string>
#include "Spaceship/Spaceship.hpp"

// Default team id for the player spaceship, used for identification of a groups objects in the game
const uint32_t SF::Spaceship::PlayerSpaceshipDefaultTeamId = 2;
// Default team id for the player spaceship, used for identification of a groups objects in the game
const uint32_t SF::Spaceship::EnemySpaceshipDefaultTeamId = 3;

std::string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "assets/";
#else // debug build
	return "E:/sources/StarsFighter/StarsFighterGame/assets/";
#endif // NDEBUG // release build

}
