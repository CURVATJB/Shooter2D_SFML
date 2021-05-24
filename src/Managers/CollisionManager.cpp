#include "Managers/CollisionManager.h"
#include "Components/CollisionHandler.h"
#include "GameObjects/GameObject.h"
#include "Managers/CollisionDispatcher.h"
#include "Tools/SMath.h"

void CollisionManager::UpdateCollision(std::list<GameObject*> abscisseTab)
{
	_SortByAbscisse(abscisseTab);

	const auto endIterator(abscisseTab.end());
	for (auto objet1 = abscisseTab.begin(); objet1 != endIterator; ++objet1)
	{
		for (auto objet2 = std::next(objet1); objet2 != endIterator; ++objet2)
		{

			//Si le point avec le plus grand X du première objet est supérieur au point avec le plus petit X du deuxième objet, une collision est possible
			if ((*objet1)->GetCollisionHandler()->GetEndAbscisse() > (*objet2)->GetCollisionHandler()->GetStartAbscisse())
			{
				_CheckCollision((*objet1)->GetCollisionHandler(), (*objet2)->GetCollisionHandler());
			}
			else
			{
				//Si la collision est impossible, comme la liste est trié en fonction du StartAbscisse, il est impossible d'avoir une collision avec le reste de la liste
				break;
			}
		}
	}
}
 
void CollisionManager::_SortByAbscisse(std::list<GameObject*>& abscisseTab)
{
	auto abscisseSort = [](GameObject* const g1, GameObject* const g2) -> bool
	{
		return (g1->GetCollisionHandler()->GetStartAbscisse()) < (g2->GetCollisionHandler()->GetStartAbscisse());
	};
	abscisseTab.sort(abscisseSort);
}

void CollisionManager::_CheckCollision(CollisionHandler* g1, CollisionHandler* g2)
{
	for (auto channel : g1->m_lExcludedCollisionType)
	{
		if (channel == g2->m_eType)
		{
			return;
		}
	}

	auto Dist(SMath::GetDistanceBetweenPoints(*g1->m_position, *g2->m_position));
	auto MaxDist(g1->m_rayon + g2->m_rayon);
	SMath::Pow(MaxDist, 2);
	
	//on compare les distances au carré et on vire sqrt
	if (Dist < MaxDist)
	{
		std::vector<sf::Vector2f> Lg1;
		g1->GetPoints(Lg1);
		std::vector<sf::Vector2f> Lg2;
		g2->GetPoints(Lg2);

		const auto SizeG1(static_cast<int>(Lg1.size()));

		for (auto i = 0; i < SizeG1; ++i)
		{
			sf::Vector2f* PointA(&Lg1[i]);
			sf::Vector2f* PointB;

			if ((i + 1) >= SizeG1)
			{
				PointB = &Lg1[0];
			}
			else
			{
				const auto Index(i + 1);
				PointB = &Lg1[Index];
			}

			const auto SizeG2(static_cast<int>(Lg2.size()));
			for (int j = 0; j < SizeG2; ++j)
			{
				sf::Vector2f* PointC(&Lg2[j]);
				sf::Vector2f* PointD;

				if ((j + 1) >= SizeG2)
				{
					PointD = &Lg2[0];
				}
				else
				{
					const auto Index(j + 1);
					PointD = &Lg2[Index];
				}

				const auto det((PointB->x - PointA->x) * (PointC->y - PointD->y) - (PointC->x - PointD->x) * (PointB->y - PointA->y));

				if (det != 0.0f)
				{
					const auto t1 = ((PointC->x - PointA->x) * (PointC->y - PointD->y) - (PointC->x - PointD->x) * (PointC->y - PointA->y)) / det;
					const auto t2 = ((PointB->x - PointA->x) * (PointC->y - PointA->y) - (PointC->x - PointA->x) * (PointB->y - PointA->y)) / det;

					if (t1 <= 1 && t1 >= 0 && t2 <= 1 && t2 >= 0)
					{
						CollisionDispatcher::DispatchOnCollision(*g1->m_owner, *g2->m_owner);
						return;
					}
				}
			}
		}
	}
}
