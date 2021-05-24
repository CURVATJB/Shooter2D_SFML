#include "GameObjects/GameObject.h"
#include "GameWindow.h"
#include "Components/Component.h"
#include "Components/CollisionHandler.h"
#include "Components/RenderHandler.h"


void GameObject::AddComponent(Component* component)
{
    m_lComponentList.push_back(component);
    component->m_owner = this;
}

void GameObject::RemoveComponent(Component* component)
{
    m_lComponentList.remove(component);
    delete component;
    component = nullptr;
}

void GameObject::SetCollisionHandler(CollisionType type, const std::vector<sf::Vector2f>& points, float radius, std::vector<CollisionType> excludedCollisionType)
{
    if (m_collisionHandler != nullptr)
    {
        m_collisionHandler->Initialise(this, type, &m_rotation, &m_position, points, radius, std::move(excludedCollisionType));
    }
    else
    {
        m_collisionHandler = new CollisionHandler(this, type, &m_rotation, &m_position, points, radius, std::move(excludedCollisionType));
    }
}

void GameObject::SetRenderHandler(sf::Texture* tex, std::string key, int zIndex, bool isMovable, sf::Vector2f origin, float scale)
{
    if (m_renderHandler != nullptr)
    {
        m_renderHandler->Initialise(tex, key, zIndex, isMovable, origin, scale);
    }
    else
    {
        m_renderHandler = new RenderHandler(this, tex, key, zIndex, isMovable, origin, scale);
    }
}

void GameObject::SetRenderHandler(std::string userText, std::string key, int zIndex, sf::Vector2f pos, sf::Color color, int size)
{
    if (m_renderHandler != nullptr)
    {
        m_renderHandler->Initialise(userText, key, zIndex, pos, color, size);
    }
    else
    {
        m_renderHandler = new RenderHandler(this, userText, key, zIndex, pos, color, size);
    }
}

GameObject::GameObject()
{
    GameWindow::GetGameLevel()->ActivateObject(*this, true);
}

GameObject::~GameObject()
{
    for (auto* component : m_lComponentList)
    {
        delete component;
    }

    m_lComponentList.clear();

    if (m_renderHandler != nullptr)
    {
        delete m_renderHandler;
        m_renderHandler = nullptr;
    }

    if (m_collisionHandler != nullptr)
    {
        delete m_collisionHandler;
        m_collisionHandler = nullptr;
    }
}

void GameObject::Tick(int64_t deltaTime)
{
    for (Component* component : m_lComponentList)
    {
        component->TickComponent(deltaTime);
    }
}

void GameObject::Activate(const sf::Vector2f position, const sf::Vector2f offsetPos, const float scale, const float rotation)
{
    m_position = position;
    m_offsetPos = offsetPos;
    m_scale = scale;
    m_rotation = rotation;

    // Print::PrintLog("++ activate ", typeid(*this).name());
}

void GameObject::Deactivate()
{
    for (auto* component : m_lComponentList)
    {
        delete component;
    }

    m_lComponentList.clear();

    if (m_renderHandler != nullptr)
    {
        m_renderHandler->Reset();
    }
    if (m_collisionHandler != nullptr)
    {
        m_collisionHandler->Reset();
    }

    GameWindow::GetGameLevel()->DeactivateObject(*this);

    // Print::PrintLog("-- deactivate ", typeid(*this).name());
}
