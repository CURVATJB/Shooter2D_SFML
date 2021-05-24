#include "Components/RunAwayMovementComponent.h"
#include "GameObjects/GameObject.h"

void RunAwayMovementComponent::TickComponent(int64_t deltaTime)
{
	BaseEnemyMovemementComponent::TickComponent(deltaTime);

	const auto Pos = m_owner->m_position;


	//Pour le comportement sp�cifique aux mouvements (peut �tre � modifier)
	if (330 < m_distance && m_distance < 350)
	{
		m_canMove = false;
	}
	else if (m_distance < 300)
	{
		m_canMove = true;
		m_escape = true;
	}
	else
	{
		m_canMove = true;
		m_escape = false;		
	}

	//Permet le mouvement de l'ennemi en fonction de son comportement
	if (m_canMove == true)
	{
		if (m_escape == false)
		{
			m_offsetAngle = 90;
			m_owner->m_position = Pos + (m_inertia * (static_cast<float>(deltaTime) * 1.f));
		}
		else
		{
			m_offsetAngle = -90;
			m_owner->m_position = Pos - (m_inertia * (static_cast<float>(deltaTime) * 1.f));
		}
		
	}

}
