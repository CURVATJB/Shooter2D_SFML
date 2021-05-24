#include "Managers/TextureManager.h"
#include "GameObjects/Bullet.h"
#include "Tools/Print.h"


const char* TextureManager::_GetPath(const ETextures t)
{
	switch (t)
	{
	case ETextures::Ship: return "../medias/Textures/Ship.png";
	case ETextures::Bullet: return "../medias/Textures/Bullet.png";
	case ETextures::SpaceBackground: return "../medias/Textures/spaceBG.jpg";
	case ETextures::ShipEnemy: return "../medias/Textures/Enemy.png";
	case ETextures::HealthBar: return "../medias/Textures/HealthBar.png";
	case ETextures::HealthBarBG: return "../medias/Textures/HealthBar_BG.png";
	case ETextures::Heart: return "../medias/Textures/heart.png";
	case ETextures::MultipleShot: return "../medias/Textures/multipleShot.png";
	case ETextures::FireRate: return "../medias/Textures/fireRate.png";
	case ETextures::Shotgun: return "../medias/Textures/shotgun.png";
	case ETextures::Sniper: return "../medias/Textures/sniper.png";
	case ETextures::SpeedArrow: return "../medias/Textures/speedArrow.png";
	}
	return "error texture";
}

sf::Texture* TextureManager::GetTexturePtr(ETextures t)
{
	const auto Iterator(mapTextures.find(t));

	//si on a notre texture de chargé
	if (Iterator != mapTextures.end())
	{
		return Iterator->second;
	}

	//création d'une nouvelle texture
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(_GetPath(t));//on charge l'image voulue
	mapTextures[t] = texture;//on conserve la donnée dans la map
	Print::PrintLog("create new texture ptr for ", _GetPath(t));

	return texture;
}
