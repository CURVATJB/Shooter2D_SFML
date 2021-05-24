#ifndef RenderHandler_H
#define RenderHandler_H

#include <string>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class GameObject;

namespace sf
{
	class RenderWindow;
}


struct CustomContainer
{

	CustomContainer(std::string key, int zIndex, sf::Drawable* drawable) : m_key(key), m_zIndex(zIndex), m_drawableItem(drawable)
	{
	}

	~CustomContainer()
	{
		if(m_drawableItem != nullptr)
		{
			delete m_drawableItem;
			m_drawableItem = nullptr;
		}
	}

	int m_zIndex = 0;//index de notre élément 
	std::string m_key;//clé pour le retrouver car les data sont dans le render handler
	sf::Drawable* m_drawableItem;//élément à rendre
};

//Un container pour associer une sprite à un index

class RenderHandler
{
public:

	RenderHandler(GameObject* parentGameObject, sf::Texture* tex, std::string key, int zIndex, bool isMovable = true,sf::Vector2f origin = sf::Vector2f(0, 0),float scale = 1);
	RenderHandler(GameObject* parentGameObject, std::string userText, std::string key, int zIndex, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Color color = sf::Color::White, int size = 30);

	~RenderHandler();
	
	void Initialise(sf::Texture* tex, std::string key, int zIndex, bool isMovable = true,sf::Vector2f origin = sf::Vector2f(0, 0),float scale = 1);
	void Initialise(std::string userText, std::string key, int zIndex, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Color color = sf::Color::White, int size = 30);
	void Reset();

	template <class T>
	T* GetRenderedItemWithKey(std::string key)
	{
		for (auto item : m_renderedItems)
		{
			if (item->m_key == key)
			{
				return dynamic_cast<T*>(item->m_drawableItem);
			}
		}

		return nullptr;
	}

	sf::Sprite* AddSprite(sf::Texture* tex, std::string key, int zIndex, bool isMovable = true,sf::Vector2f origin = sf::Vector2f(0,0),float scale = 1.f);

	sf::Text* AddText(std::string userText, std::string key, int zIndex, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Color color = sf::Color::White, int size = 30);

	//un comparateur pour sort par zIndex
	static bool Comparator(CustomContainer* a, CustomContainer* b)
	{
		return a->m_zIndex < b->m_zIndex;
	};


	void RenderUpdate();

	//le gameobject qui possède ce renderHandler
	GameObject* m_owner;

	//le vecteur des éléments à rendre
	std::vector<CustomContainer*> m_renderedItems;

	//le vecteur de sprites dont il faut updater la position
	std::vector<sf::Sprite*> m_MovableSprites;
};

#endif //RenderHandler_H
