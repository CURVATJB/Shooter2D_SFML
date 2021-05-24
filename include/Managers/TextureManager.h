#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <map>
#include <SFML/Graphics/Texture.hpp>

class TextureManager
{
public:

	//toutes les textures
	enum class ETextures { Ship, Bullet, SpaceBackground, ShipEnemy, HealthBar, HealthBarBG,Heart,MultipleShot,FireRate,Shotgun,Sniper,SpeedArrow };

	//retourne un pointeur vers la texture
	static sf::Texture* GetTexturePtr(ETextures t);

	//une map qui associe les textures chargées en mémoire à leur nom
	inline static std::map<ETextures, sf::Texture*> mapTextures;  // NOLINT(clang-diagnostic-exit-time-destructors)

private:

	TextureManager()= default;
	
	//retourne le path associé à un nom de texture
	static const char* _GetPath(ETextures t);

};

#endif
