/*
*  Config.h
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "assets/";
#else // debug build
	return "E:/sources/StarsFighter/StarsFighterGame/assets/";
#endif // NDEBUG // release build

}
