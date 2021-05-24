#include "GameLevel.h"

#include "GameLoop.h"
#include "GameObjects/Player.h"
#include "Tools/Print.h"
#include "Managers/CollisionManager.h"
#include "Components/RenderHandler.h"
#include "GameObjects/EnemySpawner.h"
#include "Components/CollisionHandler.h"
#include "HUD/EndScreenHUD.h"
#include "Managers/AudioManager.h"
#include "Managers/TextureManager.h"

GameLevel::GameLevel()
{
    Print::PrintLog("game level construction");
}

GameLevel::~GameLevel()
{
    for (auto* object : m_lObjectsActivate)
    {
        delete object;
        object = nullptr;
    }

    for (auto* object : m_lObjectsDeactivate)
    {
        delete object;
        object = nullptr;
    }

    m_lObjectsActivate.clear();
    m_lObjectsDeactivate.clear();
    m_lObjectsRendered.clear();
    m_lObjectsWithCollision.clear();
}

void GameLevel::SpawnGameObjects()
{
    m_player = SpawnActor<Player>(sf::Vector2f(300.f, 300.f));

    auto* background = SpawnActor<GameObject>();
    background->SetRenderHandler(TextureManager::GetTexturePtr(TextureManager::ETextures::SpaceBackground), "bg", 0, false);

    SpawnActor<EnemySpawner>();

    AudioManager::PlayMusic(AudioManager::ESounds::EpicGameMusic);
}

void GameLevel::Update(int64_t deltaTime)
{
    //une copie temporaire pour pouvoir instancier et ajouter de nouveaux objets dans l_gameObjects à l'intérieur de la loop
    auto Copy = m_lObjectsActivate;
    for (auto* gameObject : Copy)
    {
        gameObject->Tick(deltaTime);
    }

    CollisionManager::UpdateCollision(m_lObjectsWithCollision);
}

void GameLevel::Render(sf::RenderWindow* window)
{
    for (auto* object : m_lObjectsRendered)
    {
        object->GetRenderHandler()->RenderUpdate();
    }
}

void GameLevel::AddObjectWithCollision(CollisionHandler& object)
{
    m_lObjectsWithCollision.push_back(object.m_owner);
}

void GameLevel::RemoveObjectWithCollision(GameObject& object)
{
    m_lObjectsWithCollision.remove(&object);
}

void GameLevel::AddObjectRendered(RenderHandler& object)
{
    //On effectue dans cette fonction un trie par insertion ce qui permet de faire le moins de tries inutiles
    const auto ZIndez = object.m_renderedItems[0]->m_zIndex;

    const auto LastObject = m_lObjectsRendered.end();
    for (auto FirstObject = m_lObjectsRendered.begin(); FirstObject != LastObject; ++FirstObject)
    {
        if ((*FirstObject)->GetRenderHandler()->m_renderedItems[0]->m_zIndex > ZIndez)
        {
            m_lObjectsRendered.insert(FirstObject, object.m_owner);
            return;
        }
    }
    m_lObjectsRendered.push_back(object.m_owner);
}

void GameLevel::RemoveObjectRendered(GameObject& object)
{
    m_lObjectsRendered.remove(&object);
}

void GameLevel::EndGame()
{
    SpawnActor<EndScreenHUD>();
    GameLoop::GetInstance()->m_gameIsPlaying = false;
    m_player = nullptr;
}

void GameLevel::ActivateObject(GameObject& object, const bool newObject)
{
    if (newObject)
    {
        m_lObjectsActivate.push_back(&object);
    }
    else
    {
        m_lObjectsDeactivate.remove(&object);
        m_lObjectsActivate.push_back(&object);
    }
}

void GameLevel::DeactivateObject(GameObject& object)
{
    m_lObjectsActivate.remove(&object);
    m_lObjectsDeactivate.push_back(&object);
}
