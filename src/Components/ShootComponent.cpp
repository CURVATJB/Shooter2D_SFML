#include "Components/ShootComponent.h"
#include "GameObjects/Player.h"

void ShootComponent::TickComponent(int64_t deltaTime)
{
	//si je veux tirer
	if (m_wantToShoot)
	{
		//boucle pour tirer toutes les X secondes
		m_timer += static_cast<float>(deltaTime);
		if (m_timer >= GetFireRate() * 100000)
		{
			m_timer = 0;
			//je tire X fois avec un angle différent à chaque fois
			for (int i = 0; i < GetShootNumber(); ++i)
			{
				const auto offsetAngle = (GetShootNumber() - 1) / 2;
				ShootBullet(-90 + ((i - offsetAngle) * m_baseDispersion));
			}
		}
	}
	else
	{
		//on continue d'incrémenter le timer si on tire pas pour "charger" les balles et qu'elles partent dès qu'on clic
		if (m_timer < GetFireRate() * 100000)
		{
			m_timer += static_cast<float>(deltaTime);
		}
	}
}


