#include "Managers/FontManager.h"
#include <SFML/Graphics/Font.hpp>
#include "Tools/Print.h"

sf::Font* FontManager::GetFontPtr(EnumFonts f)
{
	const auto Iterator = m_mapFonts.find(f);

	// Print::PrintLog("map size : ", mapTextures.size());

	//si on a notre texture de chargé
	if (Iterator != m_mapFonts.end())
	{
		return Iterator->second;
	}

	//création d'une nouvelle texture
	auto* font = new sf::Font();
	font->loadFromFile(_GetPath(f));//on charge l'image voulue
	m_mapFonts[f] = font;//on conserve la donnée dans la map
	Print::PrintLog("create new font ptr for ", _GetPath(f));
	return font;
}

FontManager::~FontManager()
{
	for (auto pair : m_mapFonts)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

const char* FontManager::_GetPath(const EnumFonts f)
{
	switch (f)
	{
	case EnumFonts::Mandalorian:
		return "../medias/Fonts/Mandalore-K77lD.otf";
	}
	return "error font";
}
