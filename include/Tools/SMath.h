#ifndef SMATH_H
#define SMATH_H

#include <SFML/System/Vector2.hpp>

constexpr float PI = 3.14159265f;

class SMath
{
public:

	template<typename T>
	static void Pow(T& value, int power)
	{
		static_assert(std::is_arithmetic<T>::value);
		T OriginValue(value);

		for (int i = 0; i < power; ++i)
		{
			value *= OriginValue;
		}
	}

	//La fonction ne retourne pas la vrai valeur de distance car la racine carré n'est pas nécéssaire tout le temps donc on gagne en performance si on ne la fait pas
	static float GetDistanceBetweenPoints(sf::Vector2f& point1, sf::Vector2f& point2)
	{
		auto x(point2.x - point1.x);
		Pow<float>(x, 2);
		auto y(point2.y - point1.y);
		Pow<float>(y, 2);
		return x + y;
	}

	static void RotatePoint(sf::Vector2f& point, const float angle)
	{
		const auto x = point.x * cosf(angle) - point.y * sinf(angle);
		const auto y = point.x * sinf(angle) + point.y * cosf(angle);
		point.x = x;
		point.y = y;
	}
};

#endif //SMATH_H