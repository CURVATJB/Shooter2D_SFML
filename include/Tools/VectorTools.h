#ifndef VECTORTOOLS_H
#define VECTORTOOLS_H

#include <iostream>
#include <SFML/System/Vector2.hpp>

class VectorTools
{
public:
	static sf::Vector2f NormaliseVector(const sf::Vector2f vec)
	{
		const auto length = Length(vec);
		if (length != 0.0f)
		{
			return sf::Vector2f(vec.x / length, vec.y / length);
		}
		return vec;
	}

	static float Length(const sf::Vector2f vec)
	{
		const auto len = std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
		return len;
	}

	static void PrintVector(const sf::Vector2f vec)
	{
		std::cout << "x : " << vec.x << " // y : " << vec.y << std::endl;
	}
};
#endif //VECTORTOOLS_H