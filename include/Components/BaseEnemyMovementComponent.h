#ifndef BASEENEMYMOVEMENTCOMPONENT_H
#define BASEENEMYMOVEMENTCOMPONENT_H

#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include "Components/IMovementComponent.h"

class BaseEnemyMovemementComponent : public IMovementComponent
{
public:

	BaseEnemyMovemementComponent() = default;

	virtual ~BaseEnemyMovemementComponent() override = default;

	virtual void TickComponent(int64_t deltaTime = 0) override;


	sf::Vector2f m_playerposition;
	sf::Vector2f m_inertia = sf::Vector2f(0, 0);

	float m_drag = 0.001f;
	int m_offsetAngle = 90;//on offset l'angle de rotation de notre sprite

	bool m_canMove = true;
	bool m_escape = false;
};

#endif // !BASEENEMYMOVEMENTCOMPONENT_H
