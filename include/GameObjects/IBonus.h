#ifndef IBonus_H
#define IBonus_H

#include "GameObject.h"
#include "StaticData.h"

class IBonus : public GameObject
{

public:

	void Activate(sf::Vector2f position, sf::Vector2f offsetPos, float scale, float rotation) override
	{
		GameObject::Activate(position, offsetPos, scale, rotation);
		
		SetCollisionHandler(CollisionType::BonusChannel, StaticData::BonusCollision, 35, std::vector<CollisionType>{CollisionType::EnemyChannel, CollisionType::EnemyProjectileChannel, CollisionType::PlayerProjectileChannel, CollisionType::BonusChannel });
	};

	void Deactivate() override
	{
		GameObject::Deactivate();
	};

	IBonus() = default;
	virtual ~IBonus() override = default;

};

#endif //IBonus_H