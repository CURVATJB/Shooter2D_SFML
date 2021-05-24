#include "Components/KamikazeMovementComponent.h"
#include "GameObjects/GameObject.h"


void KamikazeMovementComponent::TickComponent(int64_t deltaTime)
{
	BaseEnemyMovemementComponent::TickComponent(deltaTime);
	const auto Pos = m_owner->m_position;
	m_owner->m_position = Pos + (m_inertia * (static_cast<float>(deltaTime) * 1.f));
}
