#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <map>

namespace sf {
	class Font;
}

class FontManager
{
public:
	//tous les sons
	enum class EnumFonts { Mandalorian };

	//retourne un pointeur vers la texture
	static sf::Font* GetFontPtr(EnumFonts f);
	~FontManager();   

public:
	//une map qui associe les textures chargées en mémoire à leur nom
	inline static std::map<EnumFonts, sf::Font*> m_mapFonts;

private:
	FontManager() = default;
	//retourne le path associé à un nom de texture
	static const char* _GetPath(EnumFonts f);

};
#endif //FONTMANAGER_H
