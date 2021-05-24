#ifndef BONUSSNIPER_H
#define BONUSSNIPER_H

#include "IBonus.h"
#include "Managers/TextureManager.h"

class BonusSniper : public IBonus
{
public:
	
	~BonusSniper() override = default;
	BonusSniper() = default;
	
	void Activate(sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f offsetPos = sf::Vector2f(0,0), float scale = 1.f, float rotation = 0) override
	{
		IBonus::Activate(position, offsetPos, scale, rotation);
		
		SetRenderHandler(TextureManager::GetTexturePtr(TextureManager::ETextures::Sniper), "Sniper", 3,true,sf::Vector2f(25,25),1);

	};

	void Deactivate() override
	{
		IBonus::Deactivate();
	}
	


	TypeId GetTypeId() override { return GetClassTypeId(); }
	static TypeId GetClassTypeId() { return "BonusSniper"; }


};

#endif
