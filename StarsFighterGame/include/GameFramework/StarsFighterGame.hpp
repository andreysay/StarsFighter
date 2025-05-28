/*
*  StarsFighterGame.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once

#include <framework/GameBaseApp.hpp>

namespace SF
{
	// StarsFighterGame class is main game application class that starts the game loop and manages the game window.
    class StarsFigherGame : public GameBaseApp
    {
    public:
		// Constructor initializes the game application with specific window size and title
		// spawns the player spaceship and other game entities.
        StarsFigherGame();
		StarsFigherGame(const StarsFigherGame&) = delete;
		StarsFigherGame(StarsFigherGame&&) = delete;
		StarsFigherGame& operator=(const StarsFigherGame&) = delete;
		StarsFigherGame& operator=(StarsFigherGame&&) = delete;
		// Destructor
		~StarsFigherGame() override = default;
    };
}
