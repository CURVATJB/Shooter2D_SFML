#ifndef BONUSFIRERATE_H
#define BONUSFIRERATE_H

#include "IBonus.h"
#include "Managers/TextureManager.h"

class BonusFireRate : public IBonus
{
public:
	BonusFireRate() = default;
	~BonusFireRate() override = default;

	void Activate(sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f offsetPos = sf::Vector2f(0,0), float scale = 1.f, float rotation = 0) override
	{
		IBonus::Activate(position, offsetPos, scale, rotation);
		
		SetRenderHandler(TextureManager::GetTexturePtr(TextureManager::ETextures::FireRate), "BonusFireRate", 3,true,sf::Vector2f(25,25),1);

	}

	void Deactivate() override
	{
		IBonus::Deactivate();
	}

	TypeId GetTypeId() override { return GetClassTypeId(); }
	static TypeId GetClassTypeId() { return "BonusFireRate"; }

	float m_fireRateUpAmount = 0.5f;
};

#endif //BONUSHEAL_H
