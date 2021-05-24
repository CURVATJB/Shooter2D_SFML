#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include "IMovementComponent.h"
#include "Managers/InputManager.h"

class PlayerMovementComponent : public IMovementComponent
{
public:

	PlayerMovementComponent();
	virtual ~PlayerMovementComponent() override = default;

	//update component
	void TickComponent(int64_t deltaTime = 0) override;

	//fired by InputManager when an input changes
	void OnInputChanged(const InputMapping input);

private:
	sf::Vector2f m_inertia = sf::Vector2f(0, 0);//conservation de la vitesse, diminue avec le temps
	float m_offsetAngle = 90.f;//on offset l'angle de rotation de notre sprite
	float m_drag = 0.001f;//resistance au déplacement
	bool m_moveTowardMouse = false;//est ce qu'on doit aller vers la souris ?
};

#endif //MOVEMENTCOMPONENT_H
