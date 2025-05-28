/*
*  GameEntry.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include <memory>


namespace SF
{

    class GameBaseApp;

}
//--------------------------------------------------------------------------------------------------------
extern std::unique_ptr<SF::GameBaseApp> GetGame();

