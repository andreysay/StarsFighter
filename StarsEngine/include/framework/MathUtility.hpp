/*
*  MathUtility.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <type_traits>

namespace SF::Math
{
	template<typename T>
	float GetVectorLength(const sf::Vector2<T>& Vector)
	{
		return std::sqrt(Vector.x * Vector.x + Vector.y * Vector.y);
	}

	template<typename T>
	void ScaleVector(sf::Vector2<T>& Vector, float Scale)
	{
		Vector.x *= Scale;
		Vector.y *= Scale;
	}

	template<typename T>
	void NormalizeVector(sf::Vector2<T>& Vector)
	{
		float Length = GetVectorLength(Vector);
		if (Length > 0.f)
		{
			ScaleVector(Vector, 1.f / Length);
		}
	}

	//! Generates a random number type T between Min and Max.
	template<typename T>
	typename std::enable_if<std::is_floating_point<T>::value, T>::type RandomNumber(T Min, T Max)
	{
		std::random_device Rd; // Obtain a random number from hardware
		std::mt19937 Gen(Rd()); // Seed the generator
		std::uniform_real_distribution<T> Distr(Min, Max); // Define the range
		return Distr(Gen);
	}

	template<typename T>
	typename std::enable_if<!std::is_floating_point<T>::value, T>::type RandomNumber(T Min, T Max)
	{
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		std::random_device Rd; // Obtain a random number from hardware
		std::mt19937 Gen(Rd()); // Seed the generator
		std::uniform_int_distribution<T> Distr(Min, Max); // Define the range
		return Distr(Gen);
	}

	sf::Color LerpColor(const sf::Color& StartColor, const sf::Color& EndColor, float Alpha);
	sf::Vector2f LerpVector(const sf::Vector2f& Start, const sf::Vector2f& End, float Alpha);
	sf::Vector2f RandomUnitVector();
}