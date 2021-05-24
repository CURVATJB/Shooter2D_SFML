#include "Components/RenderHandler.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include "GameWindow.h"
#include "Managers/FontManager.h"


RenderHandler::RenderHandler(GameObject* parentGameObject, sf::Texture* tex, std::string key, int zIndex, bool isMovable,sf::Vector2f origin,float scale) : m_owner(parentGameObject)
{
	AddSprite(tex, key, zIndex, isMovable,origin,scale);
	GameWindow::GetGameLevel()->AddObjectRendered(*this);
}

RenderHandler::RenderHandler(GameObject* parentGameObject, std::string userText, std::string key, int zIndex, sf::Vector2f pos, sf::Color color, int size) : m_owner(parentGameObject)
{
	AddText(userText, key, zIndex, pos, color, size);
	GameWindow::GetGameLevel()->AddObjectRendered(*this);
}

RenderHandler::~RenderHandler()
{
	for (auto element : m_renderedItems)
	{
		delete element;
		element = nullptr;
	}
}

void RenderHandler::Initialise(sf::Texture* tex, std::string key, int zIndex, bool isMovable,sf::Vector2f origin,float scale)
{
	AddSprite(tex, key, zIndex, isMovable,origin,scale);
	GameWindow::GetGameLevel()->AddObjectRendered(*this);
}

void RenderHandler::Initialise(std::string userText, std::string key, int zIndex, sf::Vector2f pos, sf::Color color, int size)
{
	AddText(userText, key, zIndex, pos, color, size);
	GameWindow::GetGameLevel()->AddObjectRendered(*this);
}

void RenderHandler::Reset()
{
	for (auto* container : m_renderedItems)
	{
		delete container;
	}
	m_renderedItems.clear();
	m_MovableSprites.clear();
	GameWindow::GetGameLevel()->RemoveObjectRendered(*m_owner);
}

sf::Sprite* RenderHandler::AddSprite(sf::Texture* tex, std::string key, int zIndex, bool isMovable,sf::Vector2f origin,float scale)
{
    auto* sprite = new sf::Sprite(*tex);
    auto* customSprite = new CustomContainer(std::move(key), zIndex, sprite);

	sprite->setOrigin(origin);
	sprite->setScale(sf::Vector2f(scale,scale));

	m_renderedItems.push_back(customSprite);

    // Sort using comparator function
    std::sort(m_renderedItems.begin(), m_renderedItems.end(), Comparator);

    if (isMovable)
    {
        m_MovableSprites.push_back(sprite);
    }

    return sprite;
}

sf::Text* RenderHandler::AddText(std::string userText, std::string key, int zIndex, sf::Vector2f pos, sf::Color color, int size)
{
    // Create a text
    sf::Text* text = new sf::Text(userText, *FontManager::GetFontPtr(FontManager::EnumFonts::Mandalorian));
    text->setCharacterSize(size);
    text->setFillColor(color);
    text->setPosition(pos);

    auto* customText = new CustomContainer(std::move(key), zIndex, text);

    m_renderedItems.push_back(customText);

    std::sort(m_renderedItems.begin(), m_renderedItems.end(), Comparator);

    return text;
}

void RenderHandler::RenderUpdate()
{
	//Utilisé pour le debug de collision, permet d'afficher les collisions des objets
	
	// if (m_owner->GetCollisionHandler())
	// {
	// 	auto radius = m_owner->GetCollisionHandler()->m_radius;
	// 	sf::CircleShape circle(radius);
	// 	circle.setPosition(sf::Vector2f(m_owner->m_position.x - radius,m_owner->m_position.y - radius));
	// 	circle.setFillColor(sf::Color::Green);
	// 	GameWindow::m_window->draw(circle);
	//
	// 	
	// 	
	// 	std::vector<sf::Vector2f> tmp;
	// 	m_owner->GetCollisionHandler()->GetPoints(tmp);
	//
	// 	sf::Vertex vertice[4] =
	// 	{
	// 		tmp[0],
	// 			tmp[1],
	// 			tmp[2],
	// 			tmp[3]
	// 	};
	//
	// 	GameWindow::m_window->draw(vertice, 4, sf::Quads);
	//
	// 	sf::CircleShape center(3);
	// 	center.setPosition(sf::Vector2f(m_owner->m_position.x,m_owner->m_position.y));
	// 	center.setFillColor(sf::Color::Magenta);
	// 	GameWindow::m_window->draw(center);
	// }

	for (auto* sprite : m_MovableSprites)
	{
		sprite->setRotation(m_owner->m_rotation);
		sprite->setPosition(m_owner->m_position);
	}
	
	for (auto* rendered : m_renderedItems)
	{
		GameWindow::m_window->draw(*rendered->m_drawableItem);
	}

}
