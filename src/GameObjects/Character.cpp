#include "GameObjects/Character.h"
#include "Components/LifeComponent.h"
#include "Components/ShootComponent.h"

void Character::Activate(sf::Vector2f position, sf::Vector2f offsetPos, float scale, float rotation)
{
	GameObject::Activate(position, offsetPos, scale, rotation);

	m_lifeComponent = new LifeComponent();
	AddComponent(m_lifeComponent);
}

void Character::Deactivate()
{
	GameObject::Deactivate();

	m_shootComponent = nullptr;
	m_lifeComponent = nullptr;
	m_movementComponent = nullptr;
}

void Character::SetShootComponent(ShootComponent* shootComponent)
{
	if (m_shootComponent != nullptr)
	{
		RemoveComponent(m_shootComponent);
	}

	AddComponent(shootComponent);
	m_shootComponent = shootComponent;
};
