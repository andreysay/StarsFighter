#pragma once
#include <SFML/System.hpp>

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
}