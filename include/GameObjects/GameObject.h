#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

class Component;
class RenderHandler;
class CollisionHandler;
enum class CollisionType;

using TypeId = std::string;

namespace sf {
	class Texture;
	class RenderWindow;
}

class GameObject
{

public:

	GameObject();
	
	virtual ~GameObject();

	virtual void Tick(int64_t deltaTime);

	virtual void Activate(sf::Vector2f position = sf::Vector2f(0.f, 0.f), sf::Vector2f offsetPos = sf::Vector2f(0.f, 0.f), float scale = 1.f, float rotation = 0.f);
	virtual void Deactivate();

	void AddComponent(Component* component);//ajoute un nouveau component à la liste de nos components
	void RemoveComponent(Component* component);//supprime le component

	//retourne le premier component trouvé de la class souhaitée
	template<class T>
	T* GetComponentOfClass()
	{
		for (auto component : m_lComponentList)
		{
			auto* Tmp = dynamic_cast<T*>(component);
			if (Tmp != nullptr)
			{
				return Tmp;
			}
		}
		return nullptr;
	}

	virtual TypeId GetTypeId() { return GetClassTypeId(); }
	static TypeId GetClassTypeId() { return "GameObject"; }

	CollisionHandler* GetCollisionHandler() const
	{
		return m_collisionHandler;
	}

	void SetCollisionHandler(CollisionType type, const std::vector<sf::Vector2f>& points, float radius = 0, std::vector<CollisionType> excludedCollisionType = std::vector<CollisionType>());

	RenderHandler* GetRenderHandler() const
	{
		return m_renderHandler;
	}

	void SetRenderHandler(sf::Texture* tex, std::string key, int zIndex, bool isMovable = true,sf::Vector2f origin = sf::Vector2f(0, 0),float scale = 1.f);
	void SetRenderHandler(std::string userText, std::string key, int zIndex, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Color color = sf::Color::White, int size = 30);
public:

	sf::Vector2f m_position = sf::Vector2f(0.f, 0.f);
	sf::Vector2f m_offsetPos = sf::Vector2f(0.f, 0.f);//offset de position

	float m_scale = 0.5f;
	float m_rotation = 0;

	std::list<Component*> m_lComponentList;

private:
	CollisionHandler* m_collisionHandler = nullptr;
	RenderHandler* m_renderHandler = nullptr;

};

#endif //GAMEOBJECT_H