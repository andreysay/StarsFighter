/*
*  StarsFighterGame.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "GameFramework/StarsFighterGame.hpp"
#include "framework/AssetManager.hpp"
#include "Levels/Level_1.hpp"
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
	//--------------------------------------------------------------------------------------------------------
    StarsFigherGame::StarsFigherGame()
		: GameBaseApp{ WindowSize, std::string{GameTitle}, sf::Style::Titlebar | sf::Style::Close }
	{
		// Set the asset root directory
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		std::weak_ptr<Level_1> WeakNewWorld = LoadWorld<Level_1>();
	}

}// namespace SF
