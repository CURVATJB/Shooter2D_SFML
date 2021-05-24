#ifndef LIFECOMPONENT_H
#define LIFECOMPONENT_H

#include <cstdint>
#include "Component.h"

class LifeComponent : public Component
{
public:
	LifeComponent() = default;

	void TickComponent(int64_t deltaTime) override;
	void ModifyHealth(float modification);
	void CollisionDamage(float damageOnCollision);
	void SetMaxHealth(float max)
	{
		m_maxHealth = max;
		if(m_currentHealth > m_maxHealth)
		{
			m_currentHealth = m_maxHealth;
		}
	}

public:
	float m_maxHealth = 10.f;
	float m_currentHealth = m_maxHealth;
	float m_collisionDamageCooldown = 2.f;
	bool m_canTakeDamageOnCollision = true;

private:
	float m_timer = 0.f;

	
};

#endif //LIFECOMPONENT_H

