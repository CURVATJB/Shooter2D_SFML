#ifndef CollisionHandler_H
#define CollisionHandler_H

#include <vector>
#include <SFML/System/Vector2.hpp>

class GameObject;

enum class CollisionType
{
	PlayerChannel,
	EnemyChannel,
	PlayerProjectileChannel,
	EnemyProjectileChannel,
	BonusChannel,
};

class CollisionHandler
{
public:

	CollisionHandler(GameObject* owner, const CollisionType type, float* rotation, sf::Vector2f* position, const std::vector<sf::Vector2f>& lPoints, const float radius = 0, std::vector<CollisionType> excludedCollisionType = std::vector<CollisionType>());
	~CollisionHandler() = default;

	void Initialise(GameObject* owner, CollisionType type, float* rotation, sf::Vector2f* position, const std::vector<sf::Vector2f>& lPoints, float radius = 0, std::vector<CollisionType> excludedCollisionType = std::vector<CollisionType>());

	void Reset();

	void SetPoints(const std::vector<sf::Vector2f>& lPoints);

	void GetPoints(std::vector<sf::Vector2f>& vec) const;

	float GetStartAbscisse() const;

	float GetEndAbscisse()const;

	GameObject* m_owner;
	CollisionType m_eType;
	std::vector<CollisionType> m_lExcludedCollisionType;
	sf::Vector2f* m_position;
	float m_rayon;
	float* m_rotation;

private:

	std::vector<sf::Vector2f> m_lPoints;
};

#endif //CollisionHandler_H