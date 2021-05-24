#ifndef STATICDATA_H
#define STATICDATA_H

#include <vector>
#include <SFML/System/Vector2.hpp>

class StaticData
{
public:
	inline static const std::vector<sf::Vector2f> ShipCollision = std::vector<sf::Vector2f>{ sf::Vector2f(0.0f, -25.0f), sf::Vector2f(50.0f, 25.0f), sf::Vector2f(0.0f, 10.0f), sf::Vector2f(-50.0f, 25.0f) };
	inline static const std::vector<sf::Vector2f> BonusCollision = std::vector<sf::Vector2f>{ sf::Vector2f(-25, -25), sf::Vector2f(-25, 25.0f), sf::Vector2f(25.0f, 25.0f), sf::Vector2f(25.0f, -25.0f) };
	inline static const std::vector<sf::Vector2f> BulletCollision = std::vector<sf::Vector2f>{ sf::Vector2f(9.0f, 0.0f), sf::Vector2f(0.0f, 4.0f), sf::Vector2f(-9.0f, 0.0f), sf::Vector2f(0.0f, -4.0f) };
	inline static const std::vector<sf::Vector2f> BulletSniperCollision = std::vector<sf::Vector2f>{ sf::Vector2f(90.0f, 0.0f), sf::Vector2f(0.0f, 40.0f), sf::Vector2f(-90.0f, 0.0f), sf::Vector2f(0.0f, -40.0f) };
};

#endif //STATICDATA_H