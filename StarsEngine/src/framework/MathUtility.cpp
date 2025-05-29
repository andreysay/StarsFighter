/*
*  MathUtility.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "framework/MathUtility.hpp"
#include <cmath>

sf::Color SF::Math::LerpColor(const sf::Color& StartColor, const sf::Color& EndColor, float Alpha)
{
	int LerpR = std::lerp(StartColor.r, EndColor.r, Alpha);
	int LerpG = std::lerp(StartColor.g, EndColor.g, Alpha);
	int LerpB = std::lerp(StartColor.b, EndColor.b, Alpha);
	int LerpA = std::lerp(StartColor.a, EndColor.a, Alpha);
	return sf::Color(LerpR, LerpG, LerpB, LerpA);
}

sf::Vector2f SF::Math::LerpVector(const sf::Vector2f& Start, const sf::Vector2f& End, float Alpha)
{
	return sf::Vector2f(
		std::lerp(Start.x, End.x, Alpha),
		std::lerp(Start.y, End.y, Alpha)
	);
}

sf::Vector2f SF::Math::RandomUnitVector()
{
	sf::Vector2f RandomVector{RandomNumber<float>(-1, 1), RandomNumber<float>(-1, 1)};
	NormalizeVector(RandomVector); // Normalize to get a unit vector
	return RandomVector; // Return unit vector
}
